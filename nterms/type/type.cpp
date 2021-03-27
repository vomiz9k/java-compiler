#include "type.hpp"


Simple_Type::Simple_Type(std::string* name) : name(name)
{

}

void Simple_Type::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Array_Type::Array_Type(std::string* name) : name(name)
{

}
    
void Array_Type::accept(Visitor* visitor)
{
    visitor->visit(this);
}
