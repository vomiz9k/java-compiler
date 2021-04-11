#include "method_symbol.hpp"
#include <big_include.hpp>

MethodSymbol::MethodSymbol(Method_declaration* decl) {
    name = *decl->name;
    type = *decl->type->name;
    // for (auto* arg: decl->args->args) {
    //     arguments.push_back(new VariableSymbol(arg));
    // }
}

