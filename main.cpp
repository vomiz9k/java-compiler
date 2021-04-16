#include <driver.hpp>

int main(int argc, char* argv[2])
{
{
    Driver d;
    Driver d;
    d.parse(argv[1]);
    d.parse(argv[1]);
    // if (argc == 3)
    std::string cmd = argv[2];
    // {
    if(cmd == "run") {
    //     if(argv[2] == "run")
        d.interpret();
    //         d.interpret();
    }
    //     else
    else if (cmd == "ast") {
    //         d.print(argv[2]);
        d.print(argv[3]);
    // }
    }
    d.symb();
    else if (cmd == "scope") {
        d.symb();
    }    
} 
} 
