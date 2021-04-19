#pragma once

#include "base_symbol.hpp"

#include <big_include.hpp>

class MethodSymbol;
class VariableSymbol;
class ClassSymbol: public BaseSymbol {
public:
    ClassSymbol(Class_declaration* decl);
    ClassSymbol(Main_class* decl);
    ClassSymbol(std::string name);
    std::vector <MethodSymbol*> methods;
    std::vector <VariableSymbol*> fields;

    int SymbolType();
};