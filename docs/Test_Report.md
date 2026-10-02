EDGEGUARD TEST REPORT

1. Process Monitor

Test: Start Test Service and monitor its PID.

Expected Result: Process should be detected as running.

Result: Passed.

2. Process Recovery

Test: Stop the monitored process.

Expected Result: Process Monitor should detect failure and restart the service.

Result: Passed.

3. Resource Monitor

Test: Run Resource Monitor.

Expected Result: Memory usage and system load should be displayed.

Result: Passed.

4. Character Device Driver

Test: Open /dev/edgeguard and send PROCESS_FAILURE.

Expected Result: Driver should receive the message.

Result: Passed.

5. IPC

Test: Send a message from parent process to child process using pipe.

Expected Result: Child should receive the message.

Result: Passed.

6. UDP

Test: Send a message from UDP sender to UDP receiver.

Expected Result: Receiver should display the message.

Result: Passed.

7. Build Test

Test: Build the project using Makefile.

Expected Result: Required programs should compile successfully.

Result: Passed.

8. Overall Result

The main EdgeGuard modules were implemented and tested individually. The testing helped identify and fix issues related to process failure detection and recovery.