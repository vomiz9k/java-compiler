#include "variable_declaration.hpp"
#include <visitor.hpp>

VariableDeclaration::VariableDeclaration (Type* type, std::string* name)
        : type(type), name(name)
{

}

void  VariableDeclaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}

