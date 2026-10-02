STAGE 2 – PROJECT REQUIREMENTS AND DEVELOPMENT PLAN

1. Functional Requirements

The main functional requirements of EdgeGuard are:

1. The system should monitor a running test process.

2. The system should identify when the monitored process stops working.

3. The system should restart the failed process.

4. The system should display the monitoring status.

5. The system should record important events in a log file.

6. The system should provide basic system resource information.

7. The system should allow controlled process failure for testing.

8. The system should communicate with the custom character device driver.

9. The system should demonstrate UDP communication.

10. The system should demonstrate inter-process communication using Linux pipes.


2. Non-Functional Requirements

1. The system should run in a Linux environment.

2. C++ should be used for the main user-space programs.

3. The device driver should be implemented as a Linux kernel module.

4. The system should be simple enough to test and demonstrate.

5. The recovery process should happen automatically after a detected failure.

6. The project should use Git for source code management.

7. The system should provide useful logs for debugging and testing.


3. Hardware and Software Requirements

Hardware requirements:

A computer or laptop capable of running WSL2 and Ubuntu.

Software requirements:

Windows with WSL2

Ubuntu Linux

Visual Studio Code

GCC and G++

GNU Make

Git

Linux kernel source required for building the custom driver


4. Major Modules

Process Monitor

Responsible for checking whether the monitored process is running and starting it again after failure.


Resource Monitor

Displays basic memory usage and system load information using the Linux proc filesystem.


Fault Injector

Used to intentionally stop a selected process so that the failure detection and recovery mechanism can be tested.


Device Monitor

Communicates with the custom Linux character device through /dev/edgeguard.


Custom Character Driver

A Linux kernel module that creates the virtual character device /dev/edgeguard and receives messages from user space.


IPC Module

Demonstrates communication between processes using a Linux pipe.


UDP Module

Contains a UDP sender and receiver to demonstrate basic network communication.


Test Service

A simple long-running process used as the target for monitoring and failure recovery.


5. Development Plan

Phase 1

Project idea, problem identification and project scope.


Phase 2

Linux, C++ and Git development environment setup.


Phase 3

Implementation of process monitoring and automatic recovery.


Phase 4

Implementation of resource monitoring, logging and fault injection.


Phase 5

Implementation of IPC and UDP communication.


Phase 6

Development and testing of the custom Linux character device driver.


Phase 7

Integration and testing of the major modules.


Phase 8

Documentation, GitHub submission and final demonstration.


6. Deliverables

The expected project deliverables are:

Source code

Linux device driver source code

Makefiles

Project README

Stage wise documentation

Architecture documentation

UML diagrams

Testing documentation

GitHub repository

Final project demonstration