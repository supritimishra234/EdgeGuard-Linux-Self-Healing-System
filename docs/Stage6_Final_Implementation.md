STAGE 6 – FINAL IMPLEMENTATION AND PRESENTATION
1. Introduction
The final stage contains the completed EdgeGuard system and its final demonstration.
2. Final System
The final system contains the Test Service, Process Monitor, Resource Monitor, Fault Injector, Device Monitor, custom character device driver, IPC module, UDP communication and logging.
3. Final Working Flow
The Test Service runs as the monitored process.
The Process Monitor continuously checks the service.
When a failure occurs, the Process Monitor detects it and restarts the service.
The new process is monitored again.
The Device Monitor demonstrates communication with the custom character device driver.
4. Final Testing
The main modules are tested individually and the required components are checked together.
5. Limitations
The project is a prototype and uses a simulated service.
The custom driver is a virtual character driver and does not control physical hardware.
6. Future Improvements
The system can be extended to monitor multiple services.
More system resources can be monitored.
A physical device driver can be added in the future.
A graphical monitoring interface can also be developed.
7. Conclusion
EdgeGuard demonstrates Linux system programming, C++, process management, networking and Linux character device driver concepts in one project.