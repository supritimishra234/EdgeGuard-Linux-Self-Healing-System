STAGE 4 – INITIAL IMPLEMENTATION AND PROTOTYPE

1. Introduction

In this stage, the main modules of EdgeGuard were implemented. C++ was used for the user space programs and C was used for the Linux kernel character device driver.

2. Development Environment

The project was developed using Ubuntu Linux on WSL2.

The main tools used were:

Windows
WSL2
Ubuntu
Visual Studio Code
GCC and G++
GNU Make
Git and GitHub
Linux kernel source

3. Test Service

A simple Test Service was created as a continuously running process. It displays its process ID and remains active using a loop.

This process is used as the target for process monitoring and recovery testing.

4. Process Monitor

The Process Monitor was implemented using C++ and Linux system calls.

It checks whether the Test Service is running. The Linux proc filesystem is also checked to identify a zombie process.

When a process failure is detected, the monitor starts the Test Service again and updates the process ID.

5. Automatic Recovery

The recovery process works as follows:

The Test Service is started.

The Process Monitor checks the service.

A controlled failure is introduced.

The monitor detects the failure.

A new process is created.

The Test Service is started again.

The monitor continues checking the new process.

6. Resource Monitor

The Resource Monitor reads basic system information from the Linux proc filesystem.

The following files are used:

/proc/meminfo

/proc/loadavg

The program displays memory usage and system load periodically.

7. Fault Injector

The Fault Injector is used to create a controlled process failure.

It takes a process ID and sends SIGTERM to the selected process.

This allows the recovery mechanism to be tested.

8. Character Device Driver

A custom Linux character device driver was implemented.

The driver creates the device:

/dev/edgeguard

The driver supports basic open, read and write operations.

It receives messages from user space and records information in the Linux kernel log.

9. Device Monitor

The Device Monitor is a C++ program used to communicate with the driver.

It opens /dev/edgeguard and sends a message such as:

PROCESS_FAILURE

The driver receives the message and sends a response back to the user space program.

10. IPC

A simple pipe based IPC program was implemented.

The parent process sends a message through the pipe and the child process receives it.

11. UDP Communication

A UDP sender and receiver were implemented.

The receiver listens on port 8080 and the sender sends a message using the local loopback address.

12. Logging

The Process Monitor maintains a basic log file.

The log file is:

logs/edgeguard.log

Important events such as monitoring start, process failure and recovery are recorded.

13. Makefile

A Makefile was created to compile the project programs.

It contains targets for the main EdgeGuard program, Process Monitor, Resource Monitor, Fault Injector, Device Monitor, IPC, UDP programs and Test Service.

14. Initial Prototype

The initial prototype contains process monitoring, automatic recovery, resource monitoring, fault injection, character driver communication, IPC, UDP communication and basic logging.

15. Limitations

The current project is a prototype.

The Test Service is a simulated service.

The resource monitoring is limited to basic memory usage and system load.

The character driver is a virtual character device and is not connected to physical hardware.

16. Conclusion

The main modules of EdgeGuard were implemented during this stage. The prototype demonstrates Linux process management, system programming, C++, networking and character device driver concepts.