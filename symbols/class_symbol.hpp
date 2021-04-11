#pragma once

#include "base_symbol.hpp"

#include <big_include.hpp>


class ClassSymbol: public BaseSymbol {
public:
    ClassSymbol(Class_declaration* decl);
    ClassSymbol(Main_class* decl);
    std::vector <BaseSymbol*> declarations;
};