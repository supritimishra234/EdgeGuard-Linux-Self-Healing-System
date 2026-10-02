#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>

std::mutex logMutex;

void writeLog(const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    std::ofstream logFile("../logs/edgeguard.log", std::ios::app);

    if (logFile.is_open())
    {
        logFile << message << std::endl;
        logFile.close();
    }
}

bool isProcessRunning(pid_t pid)
{
    if (kill(pid, 0) != 0)
    {
        return false;
    }

    std::string statusPath = "/proc/" +
                             std::to_string(pid) +
                             "/status";

    std::ifstream statusFile(statusPath);

    if (!statusFile.is_open())
    {
        return false;
    }

    std::string line;

    while (std::getline(statusFile, line))
    {
        if (line.rfind("State:", 0) == 0)
        {
            char state = '\0';

            if (sscanf(line.c_str(), "State:\t%c", &state) == 1)
            {
                if (state == 'Z')
                {
                    return false;
                }
            }

            break;
        }
    }

    return true;
}

pid_t restartProcess()
{
    pid_t childPid = fork();

    if (childPid < 0)
    {
        std::cerr << "Failed to create child process."
                  << std::endl;

        writeLog("Failed to create child process.");

        return -1;
    }

    if (childPid == 0)
    {
        execl("./test_service",
              "./test_service",
              (char *)nullptr);

        std::cerr << "Failed to start TestService."
                  << std::endl;

        _exit(1);
    }

    std::cout << "TestService restarted. New PID: "
              << childPid << std::endl;

    writeLog("TestService restarted successfully.");

    return childPid;
}

void monitorProcess(pid_t pid)
{
    std::cout << "Monitoring process PID: "
              << pid << std::endl;

    writeLog("EdgeGuard monitoring started.");

    while (true)
    {
        if (isProcessRunning(pid))
        {
            std::cout << "Process is running."
                      << std::endl;

            writeLog("Process is running.");
        }
        else
        {
            std::cout << "Process failure detected."
                      << std::endl;

            writeLog("Process failure detected.");

            waitpid(pid, nullptr, WNOHANG);

            pid_t newPid = restartProcess();

            if (newPid == -1)
            {
                writeLog("Recovery failed.");
                break;
            }

            pid = newPid;
        }

        sleep(2);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./process_monitor <PID>"
                  << std::endl;

        return 1;
    }

    pid_t pid = std::stoi(argv[1]);

    std::thread monitorThread(monitorProcess, pid);

    monitorThread.join();

    return 0;
}