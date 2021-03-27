#include "method_declaration.hpp"


 Method_declaration::Method_declaration (Type* type, std::string* name, Method_args* args, Statements* statements)
 : type(type), name(name), args(args), statements(statements)
 {

 }
                        
void  Method_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}

