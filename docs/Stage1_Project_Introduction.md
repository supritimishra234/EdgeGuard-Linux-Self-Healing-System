STAGE 1 – PROJECT INTRODUCTION

Project Title

EdgeGuard – Self-Healing Linux Edge System

1. Introduction

EdgeGuard is a Linux based self-healing system developed as an individual project. The main purpose of the project is to monitor a running process, detect process failure and automatically restart the failed process.

The project combines Linux system programming, C++, networking and Linux device driver concepts. A custom Linux character device driver is also used to demonstrate communication between user space and kernel space.

2. Problem Statement

In a Linux based edge system, an important service may stop because of an unexpected failure. Manual checking and restarting of the service can take time.

EdgeGuard provides a simple mechanism to monitor a test service continuously. If the monitored process stops, the system detects the failure and starts the service again.

3. Objectives

The main objectives are:

1. Monitor a running process.
2. Detect process failure.
3. Restart the failed process automatically.
4. Monitor basic system resources.
5. Provide controlled fault injection.
6. Implement a custom Linux character device driver.
7. Demonstrate user space and kernel space communication.
8. Demonstrate IPC using pipes.
9. Demonstrate basic UDP communication.
10. Maintain basic event logs.

4. Scope

The project is developed as a Linux based prototype. It focuses on process monitoring, recovery, resource monitoring, fault injection and device driver communication.

The project is mainly intended for learning and demonstration of Linux, C++, system programming and device driver concepts.

5. Expected Outcome

The expected outcome is a working Linux prototype which can detect a process failure and restart the process. The project also demonstrates communication between a user space program and the custom character device driver.

6. Application

The basic idea can be related to Linux based edge systems where services need to be monitored and recovered automatically.

7. Conclusion

Stage 1 defines the project idea, problem, objectives, scope and expected outcome. The next stage focuses on project requirements and development planning.