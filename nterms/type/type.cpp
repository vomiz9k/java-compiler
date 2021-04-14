#include "type.hpp"


Simple_Type::Simple_Type(std::string* namee)
{
    name = namee;
    is_array = false;
}

void Simple_Type::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Array_Type::Array_Type(std::string* namee)
{
    name = namee;
    is_array = true;
}
    
void Array_Type::accept(Visitor* visitor)
{
    visitor->visit(this);
}
