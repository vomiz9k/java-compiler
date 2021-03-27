#include "assignment.hpp"


Assignment::Assignment(Expr* lvalue, Expr* rvalue)
    :lvalue(lvalue), rvalue(rvalue)
{

}

void Assignment::accept(Visitor* visitor)
{
    visitor->visit(this);
}