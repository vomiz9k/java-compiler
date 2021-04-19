#include <driver.hpp>

int main(int argc, char* argv[2])
{
    Driver d;
    std::string cmd = argv[1];
    if(cmd == "run") {
        d.parse(argv[2]);
        d.interpret();
    }
    else if (cmd == "ast") {
        d.parse(argv[2]);
        d.print(argv[3]);
    }
    else if (cmd == "scope") {
        d.parse(argv[2]);
        d.symb();
    }
    else if (cmd == "errors") {
        Driver::error_test();
    }    
}
