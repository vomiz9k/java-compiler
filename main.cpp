#include <driver.hpp>

int main(int argc, char** argv)
{
    Driver d;
    

    // if (argc == 3)
    // {
    //     if(argv[2] == "run")
    //         d.interpret();
    //     else
    //         d.print(argv[2]);
    // }
    //d.print("gv.gv");
    try {
        d.parse(argv[1]);
        d.symb();
    } catch (const char* e) {
        std::cout << e << '\n';
    } catch (const std::string& e) {
        std::cout << e << '\n';
    }
} 
