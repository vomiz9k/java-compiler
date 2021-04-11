#include "declaration.hpp"


 Method_declaration::Method_declaration (Type* type, std::string* name, Method_args* args, Body* body)
 : type(type), name(name), args(args), body(body)
 {

 }
                        
void  Method_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}

void Method_declaration::SetScope(BaseScope* value){
     scope = value;
}

 Variable_declaration::Variable_declaration (Type* type, std::string* name)
 : type(type), name(name)
{

}
                        
void  Variable_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}



