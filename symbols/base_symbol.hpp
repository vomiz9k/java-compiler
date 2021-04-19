#pragma once

#include <string>

enum SYMBOL_TYPE {
    SYMBOL_CLASS,
    SYMBOL_METHOD,
    SYMBOL_VARIABLE
};

class BaseSymbol {
public:
    std::string name;
    virtual int SymbolType() = 0;

};

#include "class_symbol.hpp"
#include "method_symbol.hpp"
#include "variable_symbol.hpp"