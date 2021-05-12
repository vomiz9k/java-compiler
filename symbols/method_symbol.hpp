#pragma once

#include "base_symbol.hpp"
#include <vector>


class VariableSymbol;
class MethodDeclaration;
class Type;

class MethodSymbol: public BaseSymbol {
public:
    MethodSymbol(MethodDeclaration* decl);
    std::vector <VariableSymbol*> arguments;
    Type* type;

    int SymbolType();
};