#include "body.hpp"


Body::Body(Statements* statements)
    : statements(statements)
{

}

void Body::accept(Visitor* visitor)
{
    visitor->visit(this);
}