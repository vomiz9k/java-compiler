#include <big_include.hpp>
#include "class_symbol.hpp"

ClassSymbol::ClassSymbol(Class_declaration* decl) {
    name = *decl->name;
}

ClassSymbol::ClassSymbol(Main_class* decl) {
    name = *decl->name;
}