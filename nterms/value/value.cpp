#include "value.hpp"




Number_Value::Number_Value(int value): value(value)
{

}
void Number_Value::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


TF_Value::TF_Value(bool value): value(value)
{

}
void TF_Value::accept(Visitor* visitor) 
{
    visitor->visit(this);
}