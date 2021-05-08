#include "expression.hpp"
#include <visitor.hpp>
   

ValueExpr::ValueExpr(Value* value): value(value)
{

}

void ValueExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}



IdExpr::IdExpr(std::string* name) : name(name)
{
    is_lvalue = true;
}

void IdExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}



ArrayElementExpr::ArrayElementExpr(Expr* array, Expr* index)
    :array(array), index(index)
{
    is_lvalue = true;
}

void ArrayElementExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}



LengthExpr::LengthExpr(Expr* array)
    :array(array)
{

}
void LengthExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}



FieldInvocationExpr::FieldInvocationExpr(FieldInvocation* invocation)
    :invocation(invocation)
{
    is_lvalue = true;
}
void FieldInvocationExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

NewArrayExpr::NewArrayExpr(std::string* name, Expr* count)
    :name(name), count(count)
{
    
}

void NewArrayExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

NewSingleExpr::NewSingleExpr(std::string* name) : name(name)
{

}

void NewSingleExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}


NotExpr::NotExpr(Expr* expr): expr(expr)
{

}

void NotExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}


ThisExpr::ThisExpr()
{

}
void ThisExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}


MethodInvocationExpr::MethodInvocationExpr(MethodInvocation* invocation)
    :invocation(invocation)
{

}
void MethodInvocationExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}



PlusExpr::PlusExpr(Expr* first, Expr* second)
    : first(first), second(second)
{

}

void PlusExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}


MinusExpr::MinusExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void MinusExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

MulExpr::MulExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void MulExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

DivExpr::DivExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void DivExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

PercentExpr::PercentExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void PercentExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

AndExpr::AndExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void AndExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

OrExpr::OrExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void OrExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

SmallerExpr::SmallerExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void SmallerExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

BiggerExpr::BiggerExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void BiggerExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

EqualExpr::EqualExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void EqualExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}

NotEqualExpr::NotEqualExpr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void NotEqualExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}



BracketsExpr::BracketsExpr(Expr* expr): expr(expr)
{
    
}
void BracketsExpr::accept(Visitor* visitor)
{
    visitor->visit(this);
}


