#include "main_class.hpp"

Main_class::Main_class(std::string* class_name, Statements* statements)
    :class_name(class_name), statements(statements)
{

}

void Main_class::accept(Visitor* visitor)
{
    visitor->visit(this);
}