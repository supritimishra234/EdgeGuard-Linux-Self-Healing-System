#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cerrno>

bool isProcessRunning(pid_t pid)
{
    return kill(pid, 0) == 0;
}

pid_t restartProcess()
{
    pid_t childPid = fork();

    if (childPid < 0)
    {
        std::cerr << "Failed to create child process." << std::endl;
        return -1;
    }

    if (childPid == 0)
    {
        execl("./test_service", "./test_service", (char *)nullptr);

        std::cerr << "Failed to start TestService." << std::endl;
        _exit(1);
    }

    std::cout << "TestService restarted. New PID: "
              << childPid << std::endl;

    return childPid;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./process_monitor <PID>" << std::endl;
        return 1;
    }

    pid_t pid = std::stoi(argv[1]);

    std::cout << "Monitoring process PID: "
              << pid << std::endl;

    while (true)
    {
        if (isProcessRunning(pid))
        {
            std::cout << "Process is running." << std::endl;
        }
        else
        {
            std::cout << "Process failure detected." << std::endl;

            pid_t newPid = restartProcess();

            if (newPid == -1)
            {
                std::cout << "Recovery failed." << std::endl;
                break;
            }

            pid = newPid;
        }

        sleep(2);
    }

    return 0;
}