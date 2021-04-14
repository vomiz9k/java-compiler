#pragma once

#include "base_symbol.hpp"
#include <big_include.hpp>

class VariableSymbol: public BaseSymbol {
public:
    Type* type;
    VariableSymbol(Method_arg* arg);
    VariableSymbol(Variable_declaration* decl);

    int SymbolType();
};
