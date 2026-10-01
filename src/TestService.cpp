#include <iostream>
#include <unistd.h>

int main()
{
    std::cout << "Test service started. PID: " << getpid() << std::endl;

    while (true)
    {
        sleep(2);
    }

    return 0;
}