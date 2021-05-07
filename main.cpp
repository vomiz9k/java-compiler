#include <driver.hpp>

int main(int argc, char* argv[])
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
        try {
            d.parse(argv[2]);
            d.symb();
        } catch(const std::string& e) {
            std::cout << e << '\n';
        }
    }
    else if (cmd == "errors") {
        Driver::error_test();
    }    
}
