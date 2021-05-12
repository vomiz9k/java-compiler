#include "value.hpp"

#include <visitor.hpp>



IntValue::IntValue(int value): value(value)
{
    type = new SimpleType(new std::string("int"));
}
void IntValue::accept(Visitor* visitor)
{
    visitor->visit(this);
}


BoolValue::BoolValue(bool value): value(value)
{
    type = new SimpleType(new std::string("bool"));
}
void BoolValue::accept(Visitor* visitor)
{
    visitor->visit(this);
}