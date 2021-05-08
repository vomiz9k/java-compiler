#include "declarations.hpp"
#include <visitor.hpp>
EmptyDeclarations::EmptyDeclarations()
{

}
void EmptyDeclarations::accept(Visitor* visitor)
{
    visitor->visit(this);
}


DeclarationsWithVariable::DeclarationsWithVariable(Declarations* prev_decls, VariableDeclaration* var_decl)
: prev_decls(prev_decls), var_decl(var_decl)
{

}

void DeclarationsWithVariable::accept(Visitor* visitor)
{
    visitor->visit(this);
}


DeclarationsWithMethod::DeclarationsWithMethod(Declarations* prev_decls, MethodDeclaration* method_decl)
    :prev_decls(prev_decls), method_decl(method_decl)
{

}

void DeclarationsWithMethod::accept(Visitor* visitor)
{
    visitor->visit(this);
}
