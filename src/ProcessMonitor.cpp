#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>
#include <fcntl.h>
#include <cstring>

std::mutex logMutex;

/*
    Writes EdgeGuard events to the log file.
*/
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

/*
    Checks whether a process is still running.
*/
bool isProcessRunning(pid_t pid)
{
    return kill(pid, 0) == 0;
}

/*
    Sends an event from the EdgeGuard
    user-space application to the
    custom Linux character driver.
*/
void sendDriverEvent(const std::string& message)
{
    int fd = open("/dev/edgeguard", O_WRONLY);

    if (fd < 0)
    {
        std::cerr << "Could not open EdgeGuard driver."
                  << std::endl;

        writeLog("Could not open EdgeGuard driver.");
        return;
    }

    ssize_t bytesWritten = write(
        fd,
        message.c_str(),
        message.length()
    );

    if (bytesWritten < 0)
    {
        std::cerr << "Failed to send event to driver."
                  << std::endl;

        writeLog("Failed to send event to driver.");
    }
    else
    {
        std::cout << "Driver event sent: "
                  << message << std::endl;

        writeLog("Driver event sent: " + message);
    }

    close(fd);
}

/*
    Restarts the TestService process.
*/
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

    /*
        Child process
    */
    if (childPid == 0)
    {
        execl(
            "./test_service",
            "./test_service",
            (char *)nullptr
        );

        /*
            execl() only returns if it fails.
        */
        std::cerr << "Failed to start TestService."
                  << std::endl;

        _exit(1);
    }

    /*
        Parent process
    */
    std::cout << "TestService restarted. New PID: "
              << childPid << std::endl;

    writeLog(
        "TestService restarted. New PID: "
        + std::to_string(childPid)
    );

    return childPid;
}

/*
    Main monitoring function.
*/
void monitorProcess(pid_t pid)
{
    std::cout << "Monitoring process PID: "
              << pid << std::endl;

    writeLog("EdgeGuard monitoring started.");

    while (true)
    {
        /*
            Check whether the process is running.
        */
        if (isProcessRunning(pid))
        {
            std::cout << "Process is running."
                      << std::endl;

            writeLog("Process is running.");
        }

        /*
            Process has failed.
        */
        else
        {
            std::cout << "Process failure detected."
                      << std::endl;

            writeLog("Process failure detected.");

            /*
                Inform the custom kernel driver.
            */
            sendDriverEvent("PROCESS_FAILURE");

            /*
                Attempt automatic recovery.
            */
            pid_t newPid = restartProcess();

            if (newPid == -1)
            {
                std::cout << "Recovery failed."
                          << std::endl;

                writeLog("Recovery failed.");

                break;
            }

            /*
                Update the PID because the
                restarted process has a new PID.
            */
            pid = newPid;

            /*
                Inform the driver that
                recovery was successful.
            */
            sendDriverEvent("PROCESS_RECOVERED");
        }

        
        sleep(2);
    }
}


int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        std::cout
            << "Usage: ./process_monitor <PID>"
            << std::endl;

        return 1;
    }

   
    pid_t pid = std::stoi(argv[1]);

   
    
    std::thread monitorThread(
        monitorProcess,
        pid
    );

    
    monitorThread.join();

    return 0;
}