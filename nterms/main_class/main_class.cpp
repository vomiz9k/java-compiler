#include "main_class.hpp"

Main_class::Main_class(std::string* class_name, Body* body)
    :class_name(class_name), body(body)
{

}

void Main_class::accept(Visitor* visitor)
{
    visitor->visit(this);
}