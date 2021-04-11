#include "class_declaration.hpp"
#include <base_scope.hpp>

 void Class_declaration::SetScope(BaseScope* value){
     scope = value;
 }

Extended_Class_declaration::Extended_Class_declaration(std::string* namee, std::string* base, Declarations* declarations)
    :  base(base), declarations(declarations)
{
    name = namee;
}

void Extended_Class_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Not_extended_Class_declaration::Not_extended_Class_declaration(std::string* namee, Declarations* declarations)
    :  declarations(declarations)
{
    name = namee;
}

void Not_extended_Class_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}