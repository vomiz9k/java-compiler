#include "variable_declaration.hpp"


 Variable_declaration::Variable_declaration (Type* type, std::string* name)
 : type(type), name(name)
{

}
                        
void  Variable_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}

