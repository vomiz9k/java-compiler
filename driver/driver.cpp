#include <driver.hpp>

Driver::Driver() : lexer(*this), bison(lexer, *this) {}

int Driver::parse(const std::string& filename)
{
    std::ifstream in(filename);
    lexer.yyrestart(in);
    int res = bison();
    return res;
}