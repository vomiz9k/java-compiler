#pragma once

#include "base_symbol.hpp"
class Type;
class Method_arg;
class VariableDeclaration;

class VariableSymbol: public BaseSymbol {
public:
    Type* type;
    size_t size = 0;
    VariableSymbol(Method_arg* arg);
    VariableSymbol(VariableDeclaration* decl);

    int SymbolType();
};
