CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -pthread

SRC_DIR = src

TARGETS = \
	$(SRC_DIR)/edgeguard \
	$(SRC_DIR)/process_monitor \
	$(SRC_DIR)/resource_monitor \
	$(SRC_DIR)/fault_injector \
	$(SRC_DIR)/device_monitor \
	$(SRC_DIR)/ipc_demo \
	$(SRC_DIR)/udp_receiver \
	$(SRC_DIR)/udp_sender \
	$(SRC_DIR)/test_service

all: $(TARGETS)

$(SRC_DIR)/process_monitor: $(SRC_DIR)/ProcessMonitor.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/resource_monitor: $(SRC_DIR)/ResourceMonitor.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/fault_injector: $(SRC_DIR)/FaultInjector.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/device_monitor: $(SRC_DIR)/DeviceMonitor.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/ipc_demo: $(SRC_DIR)/IPC.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/udp_receiver: $(SRC_DIR)/UDPReceiver.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/udp_sender: $(SRC_DIR)/UDPSender.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/test_service: $(SRC_DIR)/TestService.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(SRC_DIR)/edgeguard: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
clean:
	rm -f $(TARGETS)