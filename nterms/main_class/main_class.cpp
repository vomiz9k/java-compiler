#include "main_class.hpp"
#include <base_scope.hpp>
Main_class::Main_class(std::string* class_name, Body* body)
    :name(class_name), body(body)
{

}

void Main_class::accept(Visitor* visitor)
{
    visitor->visit(this);
}

void Main_class::SetScope(BaseScope* value){
     scope = value;
}