#include "type.hpp"


Simple_Type::Simple_Type(std::string* namee)
{
    name = namee;
}

void Simple_Type::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Array_Type::Array_Type(std::string* namee)
{
    name = namee;
}
    
void Array_Type::accept(Visitor* visitor)
{
    visitor->visit(this);
}
