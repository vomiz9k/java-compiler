#include "expressions.hpp"
#include <visitor.hpp>


EmptyExpressions::EmptyExpressions()
{

}

void EmptyExpressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}

SingleExpression::SingleExpression(Expr* expr)
    :expr(expr)
{

}
void SingleExpression::accept(Visitor* visitor)
{
    visitor->visit(this);
}


MoreThanOneExpression::MoreThanOneExpression(Multiple_expressions* prev_exprs, Expr* expr)
    :expr(expr), prev_exprs(prev_exprs)
{
    
}

void MoreThanOneExpression::accept(Visitor* visitor)
{
    visitor->visit(this);
}


LastExpression::LastExpression(Expr* expr)
    :expr(expr)
{

}

void LastExpression::accept(Visitor* visitor)
{
    visitor->visit(this);
}


NotLastExpressions::NotLastExpressions(Multiple_expressions* prev_exprs, Expr* expr)
    :prev_exprs(prev_exprs), expr(expr)
{

}
 
void NotLastExpressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}


