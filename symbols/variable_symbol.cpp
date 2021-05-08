#include "variable_symbol.hpp"
#include <big_include.hpp>

VariableSymbol::VariableSymbol(Method_arg* arg) {
    name = *arg->name;
    type = arg->type;
}

VariableSymbol::VariableSymbol(VariableDeclaration* decl) {
    name = *decl->name;
    type = decl->type;
}

int VariableSymbol::SymbolType() {
    return SYMBOL_VARIABLE;
}