#include "class_declaration.hpp"


Extended_Class_declaration::Extended_Class_declaration(std::string* name, std::string* base, Declarations* declarations)
    : name(name), base(base), declarations(declarations)
{
        
}

void Extended_Class_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Not_extended_Class_declaration::Not_extended_Class_declaration(std::string* name, Declarations* declarations)
    : name(name), declarations(declarations)
{

}

void Not_extended_Class_declaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}