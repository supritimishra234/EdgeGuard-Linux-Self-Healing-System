STAGE 5 – TESTING AND INTEGRATION
1. Introduction
This stage focuses on testing the implemented EdgeGuard modules and checking their integration.
2. Process Monitor Test
The Test Service was started and its PID was given to the Process Monitor. The monitor continuously checked the process.
Result: Passed.
3. Self Healing Test
The Test Service was intentionally stopped using the Fault Injector. The Process Monitor detected the failure and started the service again.
Result: Passed.
4. Resource Monitor Test
The Resource Monitor was executed and displayed memory usage and system load.
Result: Passed.
5. Character Driver Test
The custom driver was loaded and /dev/edgeguard was created. The Device Monitor sent PROCESS_FAILURE to the driver and received a response.
Result: Passed.
6. IPC Test
The IPC program was executed using a parent and child process. The parent sent a message through the pipe and the child received it.
Result: Passed.
7. UDP Test
The UDP receiver was started and the sender sent a message to it.
Result: Passed.
8. Integration
The main modules were organized using the Makefile and tested individually. The main EdgeGuard program starts the Test Service, Process Monitor and Resource Monitor.
9. Improvements
Process state checking was improved to handle zombie processes. Basic logging and mutex protection were also added.
10. Conclusion
The main EdgeGuard modules were tested and the results confirmed the basic process recovery, resource monitoring, driver communication, IPC and UDP functionality.