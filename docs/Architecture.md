EDGEGUARD SYSTEM ARCHITECTURE

1. Main Components

EdgeGuard Controller

Test Service

Process Monitor

Resource Monitor

Fault Injector

Device Monitor

Custom Character Device Driver

IPC Module

UDP Sender

UDP Receiver

2. Process Monitoring

The Test Service runs continuously.

The Process Monitor checks the service.

If the service stops, the monitor detects the failure and starts it again.

3. Resource Monitoring

The Resource Monitor reads information from the Linux proc filesystem.

It reads memory information from /proc/meminfo and system load from /proc/loadavg.

4. Driver Communication

The Device Monitor opens /dev/edgeguard.

It writes an event message to the device.

The custom character driver receives the message in kernel space.

5. IPC

The IPC module demonstrates communication between a parent and child process using a pipe.

6. Network Communication

The UDP sender sends a message to the UDP receiver using the local loopback address.

7. Overall Design

The project separates process monitoring, resource monitoring, fault injection and device communication into different modules.

This makes each part easier to test and understand.