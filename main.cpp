#include <driver.hpp>

int main(int argc, char* argv[2])
{
    Driver d;
    d.parse(argv[1]);
    std::string cmd = argv[2];
    if(cmd == "run") {
        d.interpret();
    }
    else if (cmd == "ast") {
        d.print(argv[3]);
    }
    else if (cmd == "scope") {
        d.symb();
    }    
} 
