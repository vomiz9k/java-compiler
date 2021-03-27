#include "assignment.hpp"


Assignment::Assignment(Lvalue* lvalue, Expr* rvalue)
    :lvalue(lvalue), rvalue(rvalue)
{

}

void Assignment::accept(Visitor* visitor)
{
    visitor->visit(this);
}