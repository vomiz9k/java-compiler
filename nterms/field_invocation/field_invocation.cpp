#include "field_invocation.hpp"
#include <visitor.hpp>

FieldInvocation::FieldInvocation(std::string* name)
    :name(name)
{

}

void FieldInvocation::accept(Visitor* visitor)
{
    visitor->visit(this);
}