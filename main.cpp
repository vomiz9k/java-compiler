#include <driver.hpp>

int main(int argc, char** argv)
{
    Driver d;
    d.parse(argv[1]);
    if (argc == 3)
    {
        if(argv[2] == "run")
            d.interpret();
        else
            d.print(argv[2]);
    }
    
} 
