#include "value.hpp"
#include <big_include.hpp>



Number_Value::Number_Value(int value): value(value)
{
    type = new Simple_Type(new std::string("int"));
}
void Number_Value::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


TF_Value::TF_Value(bool value): value(value)
{
    type = new Simple_Type(new std::string("bool"));
}
void TF_Value::accept(Visitor* visitor) 
{
    visitor->visit(this);
}