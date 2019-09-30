#include <iostream>
#include <unistd.h>

int main()
{
    while(true)
    {
    std::cout<<"do this\n";
    sleep(1);
    std::cout<<"then this\n";
    sleep(1);
    std::cout<<"now this\n";
    }
}