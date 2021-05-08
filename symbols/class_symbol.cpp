#include <big_include.hpp>
#include "class_symbol.hpp"

ClassSymbol::ClassSymbol(Class_declaration* decl) {
    name = *decl->name;
}

ClassSymbol::ClassSymbol(MainClass* decl) {
    name = *decl->name;
}

ClassSymbol::ClassSymbol(std::string namee) {
    name = namee;
}

int ClassSymbol::SymbolType() {
    return SYMBOL_CLASS;
}
