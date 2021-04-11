#pragma once

#include "base_symbol.hpp"

class VariableSymbol;
class Method_declaration;

class MethodSymbol: public BaseSymbol {
public:
    MethodSymbol(Method_declaration* decl);
    std::vector <VariableSymbol*> arguments;
    std::string type;
};