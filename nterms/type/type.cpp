#include "type.hpp"
#include <visitor.hpp>


SimpleType::SimpleType(std::string* namee)
{
    name = namee;
    is_array = false;
}

void SimpleType::accept(Visitor* visitor)
{
    visitor->visit(this);
}


ArrayType::ArrayType(std::string* namee)
{
    name = namee;
    is_array = true;
}
    
void ArrayType::accept(Visitor* visitor)
{
    visitor->visit(this);
}
