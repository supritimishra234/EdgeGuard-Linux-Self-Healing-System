PRODUCT REQUIREMENTS DOCUMENT

Project Name

EdgeGuard – Self-Healing Linux Edge System

1. Purpose

The purpose of EdgeGuard is to provide a simple Linux based system for detecting process failures and automatically recovering the failed process.

2. Target User

The project is intended as a prototype for Linux based edge systems where continuous service monitoring is required.

3. Main Features

Process monitoring

Automatic process recovery

Resource monitoring

Fault injection

Character device communication

IPC

UDP communication

Event logging

4. Functional Requirements

The system should monitor a running process.

The system should detect process failure.

The system should restart the failed process.

The system should display basic resource information.

The system should allow controlled fault injection.

The system should communicate with the custom character driver.

5. Non Functional Requirements

The system should run on Linux.

The programs should be simple to build and test.

The system should maintain basic logs.

The source code should be maintained using Git.

6. Expected Result

The system should demonstrate basic self-healing behaviour and Linux user space to kernel space communication.