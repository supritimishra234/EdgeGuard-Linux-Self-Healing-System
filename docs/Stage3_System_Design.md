STAGE 3 – SYSTEM DESIGN AND ARCHITECTURE


1. Introduction

This stage describes the design of the EdgeGuard system. The system is divided into different modules so that each module has a specific responsibility.

The main parts of the system are the EdgeGuard controller, Process Monitor, Resource Monitor, Fault Injector, Device Monitor, Test Service and the custom Linux character device driver.

The user-space programs are developed mainly using C++ and the device driver is developed as a Linux kernel module using C.


2. Overall Architecture

The basic architecture of EdgeGuard is:

                    EDGEGUARD CONTROLLER
                              |
             +----------------+----------------+
             |                |                |
             v                v                v
      Process Monitor   Resource Monitor   Fault Injector
             |                |
             |                |
             +--------+-------+
                      |
                      v
                Recovery
                 Mechanism
                      |
                      v
                 Test Service

                      |
                      |
              Device Monitor
                      |
                      v
                /dev/edgeguard
                      |
                      v
           Custom Character Driver
                      |
                      v
                 Linux Kernel


3. Component Responsibilities


EdgeGuard Controller

The main controller is responsible for starting the major EdgeGuard components. It starts the test service, process monitor and resource monitor.


Test Service

The Test Service is a simple long-running Linux process. It is used as the target process for monitoring and failure recovery.


Process Monitor

The Process Monitor checks whether the Test Service is running.

When a process failure is detected, it starts the Test Service again using Linux process management functions.

The Process Monitor also sends failure and recovery information to the custom device driver.


Resource Monitor

The Resource Monitor reads basic system information from the Linux proc filesystem.

It checks memory usage and system load and displays the information periodically.


Fault Injector

The Fault Injector is used to intentionally stop a selected process.

It is mainly used during testing to check whether the Process Monitor can detect the failure and recover the process.


Device Monitor

The Device Monitor is a user-space program that communicates with the custom character device.

It opens the device file /dev/edgeguard and sends an event to the kernel driver.


Custom Character Device Driver

The custom driver is implemented as a Linux kernel module.

It creates the device file /dev/edgeguard and provides an interface for user-space programs to communicate with the kernel.

The driver receives messages from user space and records the events using kernel logging.


IPC Module

The IPC module demonstrates communication between a parent process and a child process using a Linux pipe.


UDP Module

The UDP sender and receiver demonstrate basic network communication using UDP sockets.


4. User Space and Kernel Space

EdgeGuard contains both user-space and kernel-space components.

User-space components include the EdgeGuard controller, Process Monitor, Resource Monitor, Fault Injector, Device Monitor, IPC program, UDP programs and Test Service.

The custom character device driver runs in kernel space.

Communication between user space and the driver takes place through the device file /dev/edgeguard.


5. Process Recovery Flow

The normal recovery sequence is:

1. The Test Service starts running.

2. The Process Monitor continuously checks the process.

3. A controlled failure is introduced during testing.

4. The Process Monitor detects that the process is no longer running.

5. A failure event is recorded.

6. The failure event can be sent to the custom device driver.

7. The recovery mechanism creates a new process.

8. The Test Service is started again.

9. The new process receives a new process ID.

10. The Process Monitor continues monitoring the new process.


6. Character Driver Communication Flow

The communication between the user-space program and the driver is:

User Space

Device Monitor or Process Monitor

        |

        | open and write

        v

/dev/edgeguard

        |

        v

Custom Character Device Driver

        |

        v

Linux Kernel


The driver can then record the received event using kernel logging.


7. Data Structures Used

The project uses basic data structures suitable for the implemented modules.

The Process Monitor uses the Linux pid_t type to store process IDs.

Character arrays and strings are used for communication messages.

The device driver uses Linux character device structures required for character device registration.

File streams are used for writing application logs.


8. Important Linux System Calls and Functions

The project uses several Linux system programming functions.

fork()

Used to create a new process.

exec or execl()

Used to replace the child process with the Test Service program.

kill()

Used for process checking and controlled process termination.

sleep()

Used to provide periodic monitoring intervals.

pipe()

Used in the IPC demonstration.

open()

Used to open the /dev/edgeguard device.

read()

Used for reading from the character device.

write()

Used to send information to the character device.

close()

Used to close the opened device or file.


9. Sequence of Process Recovery

The sequence of the main recovery operation is:

User or Fault Injector

        |

        | Process failure

        v

Test Service

        |

        | Failure

        v

Process Monitor

        |

        | Detect failure

        v

Recovery Mechanism

        |

        | fork()

        v

New Process

        |

        | execl()

        v

Test Service Restarted

        |

        v

Process Monitor continues monitoring


10. State Machine

The main process states used by EdgeGuard can be represented as:

STARTING

     |

     v

RUNNING

     |

     | Failure detected

     v

FAILED

     |

     | Recovery started

     v

RESTARTING

     |

     | Successful restart

     v

RUNNING


If recovery cannot be completed, the system records a recovery failure.


11. Development Environment

The project was developed using Windows with WSL2 and Ubuntu.

The source code was written and managed using Visual Studio Code.

GCC and G++ were used to compile the C++ programs.

GNU Make was used to automate compilation.

Git was used for version control and GitHub was used for project submission.

The custom Linux driver was built using the WSL Linux kernel source.


12. Git and Version Control

The project uses Git for maintaining the source code and tracking changes.

The repository contains the source code, driver code, Makefiles and documentation.

Generated build files such as object files and kernel module build files are excluded using the .gitignore file.


13. Design Summary

The EdgeGuard design separates the project into small modules.

The Process Monitor handles process failure detection and recovery.

The Resource Monitor provides basic system information.

The Fault Injector provides controlled failures for testing.

The Device Monitor provides user-space communication with the custom character driver.

The character driver provides the connection between the user-space application and the Linux kernel.

This modular structure makes the project easier to test and understand.