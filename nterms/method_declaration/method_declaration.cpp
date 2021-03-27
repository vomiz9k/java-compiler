#include "method_declaration.hpp"


 Method_declaration::Method_declaration (Type* type, std::string* name, Method_args* args, Body* body)
 : type(type), name(name), args(args), body(body)
 {

 }
                        
void  Method_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}

