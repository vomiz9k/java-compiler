#include "assignment.hpp"


Assignment::Assignment(Expr *lValue, Expr *rvalue) : lvalue(lValue), rvalue(rvalue)
{

}

void Assignment::accept(Visitor* visitor)
{
    visitor->visit(this);
}