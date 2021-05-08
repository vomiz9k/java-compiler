#pragma once

#include "base_symbol.hpp"

class Class_declaration;
class MainClass;

class MethodSymbol;
class VariableSymbol;


class ClassSymbol: public BaseSymbol {
public:
    ClassSymbol(Class_declaration* decl);
    ClassSymbol(MainClass* decl);
    ClassSymbol(std::string name);

    void append(VariableSymbol* var);

    std::vector <MethodSymbol*> methods;
    std::vector <VariableSymbol*> fields;

    int SymbolType();
};