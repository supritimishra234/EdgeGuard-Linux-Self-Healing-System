STAGE 5 – TESTING, INTEGRATION AND IMPROVEMENT

1. Introduction

This stage focuses on testing the implemented EdgeGuard modules and checking whether the different components work correctly.

2. Process Monitoring Test

The Test Service was started and its process ID was given to the Process Monitor.

The Process Monitor continuously checked the process.

Result:

Process monitoring worked correctly.

3. Self Healing Test

The Test Service was intentionally stopped using the Fault Injector.

The Process Monitor detected the process failure and started the service again.

Result:

Automatic process recovery worked correctly.

4. Resource Monitoring Test

The Resource Monitor was executed and system memory usage and system load were displayed.

Result:

Basic resource monitoring worked correctly.

5. Character Driver Test

The custom driver was loaded and the device /dev/edgeguard was created.

The Device Monitor opened the device and sent a PROCESS_FAILURE message.

The driver received the message and the response was read by the Device Monitor.

Result:

User space and kernel space communication worked correctly.

6. IPC Test

The IPC program was executed using a parent and child process.

The parent sent a message through the pipe and the child received it.

Result:

Pipe based IPC worked correctly.

7. UDP Test

The UDP receiver was started first and the UDP sender was then executed.

The receiver received the message from the sender.

Result:

Basic UDP communication worked correctly.

8. Integration

The different modules were organized under the EdgeGuard project and built using the Makefile.

The main controller can start the Test Service, Process Monitor and Resource Monitor.

9. Improvements

During development, process state checking was improved to handle zombie processes correctly.

Basic logging and mutex protection were also added to the Process Monitor.

10. Conclusion

Testing was performed on the main modules of EdgeGuard. The tests helped verify process recovery, resource monitoring, driver communication, IPC and UDP communication.