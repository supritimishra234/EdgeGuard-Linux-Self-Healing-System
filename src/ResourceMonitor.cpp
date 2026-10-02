#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

double getMemoryUsage()
{
    std::ifstream memFile("/proc/meminfo");

    if (!memFile.is_open())
    {
        return -1;
    }

    std::string line;

    long totalMemory = 0;
    long availableMemory = 0;

    while (std::getline(memFile, line))
    {
        std::stringstream ss(line);

        std::string name;
        long value;
        std::string unit;

        ss >> name >> value >> unit;

        if (name == "MemTotal:")
        {
            totalMemory = value;
        }

        if (name == "MemAvailable:")
        {
            availableMemory = value;
        }
    }

    if (totalMemory == 0)
    {
        return -1;
    }

    double usedMemory =
        totalMemory - availableMemory;

    return (usedMemory / totalMemory) * 100.0;
}

double getLoadAverage()
{
    std::ifstream loadFile("/proc/loadavg");

    if (!loadFile.is_open())
    {
        return -1;
    }

    double load;

    loadFile >> load;

    return load;
}

int main()
{
    std::cout << "EdgeGuard Resource Monitor started."
              << std::endl;

    while (true)
    {
        double memoryUsage = getMemoryUsage();
        double loadAverage = getLoadAverage();

        std::cout
            << "Memory Usage: "
            << memoryUsage
            << "%"
            << std::endl;

        std::cout
            << "System Load: "
            << loadAverage
            << std::endl;

        if (memoryUsage > 90)
        {
            std::cout
                << "WARNING: High memory usage detected."
                << std::endl;
        }

        sleep(3);
    }

    return 0;
}