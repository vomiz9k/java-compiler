#include <driver.hpp>

int main(int argc, char** argv)
{
    Driver d;
    d.parse(argv[1]);
    if (argc == 3)
        d.print(argv[2]);
    d.interpret();
} 
