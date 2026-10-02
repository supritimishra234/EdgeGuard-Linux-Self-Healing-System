#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string>

pid_t testServicePid = -1;
pid_t processMonitorPid = -1;
pid_t resourceMonitorPid = -1;

void stopAllProcesses(int signalNumber)
{
    (void)signalNumber;

    std::cout << "\nStopping EdgeGuard..." << std::endl;

    if (testServicePid > 0)
    {
        kill(testServicePid, SIGTERM);
    }

    if (processMonitorPid > 0)
    {
        kill(processMonitorPid, SIGTERM);
    }

    if (resourceMonitorPid > 0)
    {
        kill(resourceMonitorPid, SIGTERM);
    }

    std::cout << "EdgeGuard stopped." << std::endl;

    _exit(0);
}

pid_t startTestService()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Failed to start TestService."
                  << std::endl;
        return -1;
    }

    if (pid == 0)
    {
        execl(
            "./test_service",
            "./test_service",
            (char *)nullptr
        );

        _exit(1);
    }

    return pid;
}

pid_t startProcessMonitor(pid_t targetPid)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Failed to start ProcessMonitor."
                  << std::endl;
        return -1;
    }

    if (pid == 0)
    {
        std::string pidString =
            std::to_string(targetPid);

        execl(
            "./process_monitor",
            "./process_monitor",
            pidString.c_str(),
            (char *)nullptr
        );

        _exit(1);
    }

    return pid;
}

pid_t startResourceMonitor()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "Failed to start ResourceMonitor."
                  << std::endl;
        return -1;
    }

    if (pid == 0)
    {
        execl(
            "./resource_monitor",
            "./resource_monitor",
            (char *)nullptr
        );

        _exit(1);
    }

    return pid;
}

int main()
{
    signal(SIGINT, stopAllProcesses);

    std::cout << "===================================="
              << std::endl;

    std::cout << "        EDGEGUARD SYSTEM"
              << std::endl;

    std::cout << "===================================="
              << std::endl;

    std::cout << "Starting EdgeGuard components..."
              << std::endl;

    /*
        Enter the src directory because
        the component executables are stored there.
    */
    if (chdir("src") != 0)
    {
        std::cerr << "Failed to enter src directory."
                  << std::endl;

        return 1;
    }

    /*
        Start TestService.
    */
    testServicePid = startTestService();

    if (testServicePid < 0)
    {
        return 1;
    }

    std::cout << "TestService started. PID: "
              << testServicePid
              << std::endl;

    sleep(1);

    /*
        Start ProcessMonitor.
    */
    processMonitorPid =
        startProcessMonitor(testServicePid);

    if (processMonitorPid < 0)
    {
        kill(testServicePid, SIGTERM);
        return 1;
    }

    std::cout << "ProcessMonitor started."
              << std::endl;

    /*
        Start ResourceMonitor.
    */
    resourceMonitorPid =
        startResourceMonitor();

    if (resourceMonitorPid < 0)
    {
        kill(testServicePid, SIGTERM);
        kill(processMonitorPid, SIGTERM);
        return 1;
    }

    std::cout << "ResourceMonitor started."
              << std::endl;

    std::cout << "\n===================================="
              << std::endl;

    std::cout << "EdgeGuard is now running."
              << std::endl;

    std::cout << "Kernel Driver: /dev/edgeguard"
              << std::endl;

    std::cout << "Press Ctrl+C to stop EdgeGuard."
              << std::endl;

    std::cout << "===================================="
              << std::endl;

    /*
        Keep EdgeGuard running.
    */
    while (true)
    {
        sleep(5);
    }

    return 0;
}