#include "program.hpp"

Program::Program(Main_class* main_class, Class_declarations* class_declarations)
    : main_class(main_class), class_declarations(class_declarations)
{

}

void Program::SetScope(BaseScope* value) {
    scope = value;
}

void Program::accept(Visitor* visitor)
{
    visitor->visit(this);
}