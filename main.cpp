#include <driver.hpp>

int main(int argc, char** argv)
{
    Driver d;
    d.parse(argv[1]);
    d.print(argv[2]);
} 
