#include "body.hpp"
#include <visitor.hpp>

Body::Body(Statements* statements)
    : statements(statements)
{

}

void Body::SetScope(BaseScope* value){
     scope = value;
}

void Body::accept(Visitor* visitor)
{
    visitor->visit(this);
}