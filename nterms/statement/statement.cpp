#include "statement.hpp"
#include <visitor.hpp>





IfElseStatement::IfElseStatement(Expr* condition, Statement* do_if_true, Statement* do_else)
    : condition(condition), do_if_true(do_if_true), do_else(do_else)
{

}

void IfElseStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}

IfStatement::IfStatement(Expr* condition, Statement* do_if_true)
    : condition(condition), do_if_true(do_if_true)
{

}

void IfStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}




AssertStatement::AssertStatement(Expr* check)
    :check(check)
{

}

void AssertStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}



VarDeclStatement::VarDeclStatement(VariableDeclaration* decl)
    :decl(decl)
{

}

void VarDeclStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


ScopeStatement::ScopeStatement(Body* body) : body(body)
{

}

void ScopeStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


WhileStatement::WhileStatement(Expr* condition, Statement* do_if_true)
    :condition(condition), do_if_true(do_if_true)
{

}

void WhileStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


PrintStatement::PrintStatement(Expr* to_print)
    :to_print(to_print)
{

}

void PrintStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


AssignmentStatement::AssignmentStatement(Assignment* assignment)
    :assignment(assignment)
{

}

void AssignmentStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


ReturnStatement::ReturnStatement(Expr* to_return)
    :to_return(to_return)
{

}

void ReturnStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}

MethodInvocationStatement::MethodInvocationStatement(MethodInvocation* invocation)
    :invocation(invocation)
{

}

void MethodInvocationStatement::accept(Visitor* visitor)
{
    visitor->visit(this);
}


