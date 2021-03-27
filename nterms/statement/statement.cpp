#include "statement.hpp"






If_else_Statement::If_else_Statement(Expr* condition, Statement* do_if_true, Statement* do_else)
    : condition(condition), do_if_true(do_if_true), do_else(do_else)
{

}

void If_else_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}

If_Statement::If_Statement(Expr* condition, Statement* do_if_true)
    : condition(condition), do_if_true(do_if_true)
{

}

void If_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}




Assert_Statement::Assert_Statement(Expr* check)
    :check(check)
{

}

void Assert_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}



Var_decl_Statement::Var_decl_Statement(Variable_declaration* decl)
    :decl(decl)
{

}

void Var_decl_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Big_Statement::Big_Statement(Body* body) : body(body)
{

}

void Big_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


While_Statement::While_Statement(Expr* condition, Statement* do_if_true)
    :condition(condition), do_if_true(do_if_true)
{

}

void While_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Print_Statement::Print_Statement(Expr* to_print)
    :to_print(to_print)
{

}

void Print_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Assignment_Statement::Assignment_Statement(Assignment* assignment)
    :assignment(assignment)
{

}

void Assignment_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Return_Statement::Return_Statement(Expr* to_return)
    :to_return(to_return)
{

}

void Return_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}

Method_invocation_Statement::Method_invocation_Statement(Method_invocation* invocation)
    :invocation(invocation)
{

}

void Method_invocation_Statement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


