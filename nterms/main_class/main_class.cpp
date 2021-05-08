#include "main_class.hpp"
#include <base_scope.hpp>
#include <visitor.hpp>

MainClass::MainClass(std::string* class_name, Body* body)
    :name(class_name), body(body)
{

}

void MainClass::accept(Visitor* visitor)
{
    visitor->visit(this);
}

void MainClass::SetScope(BaseScope* value){
     scope = value;
}