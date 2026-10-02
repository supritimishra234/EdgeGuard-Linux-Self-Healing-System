EDGEGUARD – SELF-HEALING LINUX EDGE SYSTEM

PROJECT OVERVIEW
EdgeGuard is a Linux based self-healing system developed using C++ and Linux system programming. It monitors a process, detects failure and automatically restarts it.

KEY FEATURES
Process Monitoring
Automatic Process Recovery
Resource Monitoring
Fault Injection
Custom Linux Character Device Driver
User Space and Kernel Space Communication
IPC using Pipes
UDP Communication
Event Logging

TECHNOLOGIES
C, C++, Linux, Ubuntu, WSL2, GCC, G++, GNU Make, Git, GitHub

PROJECT STRUCTURE
src       User space programs
driver    Character device driver
include   Header files
tests     Testing files
docs      Project documentation
logs      Runtime logs
Makefile  Build configuration

MAIN DEVICE:
/dev/edgeguard

BUILD:
make

RUN:
./src/edgeguard

DOCUMENTATION:
Detailed project documentation is available in the docs folder.

PROJECT STATUS:
Linux based prototype demonstrating process recovery, system programming, networking and character device driver concepts.