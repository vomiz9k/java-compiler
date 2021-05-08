#include "declaration.hpp"
#include <visitor.hpp>

 MethodDeclaration::MethodDeclaration (Type* type, std::string* name, Method_args* args, Body* body)
 : type(type), name(name), args(args), body(body)
 {

 }
                        
void  MethodDeclaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}

void MethodDeclaration::SetScope(BaseScope* value){
     scope = value;
}

 VariableDeclaration::VariableDeclaration (Type* type, std::string* name)
 : type(type), name(name)
{

}
                        
void  VariableDeclaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}



