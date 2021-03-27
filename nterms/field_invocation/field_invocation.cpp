#include "field_invocation.hpp"

Field_invocation::Field_invocation(std::string* name)
    :name(name)
{

}

void Field_invocation::accept(Visitor* visitor)
{
    visitor->visit(this);
}