#include "declarations.hpp"

Empty_Declarations::Empty_Declarations()
{

}
void Empty_Declarations::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Declarations_with_variable::Declarations_with_variable(Declarations* prev_decls, Variable_declaration* var_decl)
: prev_decls(prev_decls), var_decl(var_decl)
{

}

void Declarations_with_variable::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Declarations_with_method::Declarations_with_method(Declarations* prev_decls, Method_declaration* method_decl)
    :prev_decls(prev_decls), method_decl(method_decl)
{

}

void Declarations_with_method::accept(Visitor* visitor)
{
    visitor->visit(this);
}
