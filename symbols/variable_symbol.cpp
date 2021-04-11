#include "variable_symbol.hpp"
#include <big_include.hpp>

VariableSymbol::VariableSymbol(Method_arg* arg) {
    name = *arg->name;
    type = *arg->type->name;
}

VariableSymbol::VariableSymbol(Variable_declaration* decl) {
    name = *decl->name;
    type = *decl->type->name;
}