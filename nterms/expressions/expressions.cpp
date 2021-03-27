#include "expressions.hpp"



Empty_Expressions::Empty_Expressions()
{

}

void Empty_Expressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}

Single_Expressions::Single_Expressions(Expr* expr)
    :expr(expr)
{

}
void Single_Expressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Many_Expressions::Many_Expressions(Multiple_expressions* prev_exprs, Expr* expr)
    :expr(expr), prev_exprs(prev_exprs)
{
    
}

void Many_Expressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Single_Multiple_expressions::Single_Multiple_expressions(Expr* expr)
    :expr(expr)
{

}

void Single_Multiple_expressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Many_Multiple_expressions::Many_Multiple_expressions(Multiple_expressions* prev_exprs, Expr* expr)
    :prev_exprs(prev_exprs), expr(expr)
{

}
 
void Many_Multiple_expressions::accept(Visitor* visitor)
{
    visitor->visit(this);
}


