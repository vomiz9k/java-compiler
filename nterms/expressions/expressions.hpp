#pragma once

#include <base.hpp>
#include <vector>

class Expr;

class Expressions: public Base
{
    std::vector<Expr*> exprs;
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
};

class EmptyExpressions: public Expressions
{
    #include <friends_visitors>
public:

    EmptyExpressions();
    void accept(Visitor* visitor) override;
};

class SingleExpression: public Expressions
{
    #include <friends_visitors>
    Expr* expr;
 public:

    SingleExpression(Expr* expr);
    void accept(Visitor* visitor) override;    
};


class Multiple_expressions;

class MoreThanOneExpression: public Expressions
{
    #include <friends_visitors>
    Expr* expr;
    Multiple_expressions* prev_exprs;
public:
    MoreThanOneExpression(Multiple_expressions* prev_exprs, Expr* expr);
    void accept(Visitor* visitor) override;    
};

class Multiple_expressions: public Base //other rule
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
};

class LastExpression: public Multiple_expressions
{
    #include <friends_visitors>
    Expr* expr;
public:
    LastExpression(Expr* expr);
    void accept(Visitor* visitor) override;  
};

class NotLastExpressions: public Multiple_expressions
{
    #include <friends_visitors>
    Multiple_expressions* prev_exprs;
    Expr* expr;
public:
    NotLastExpressions(Multiple_expressions* prev_exprs, Expr* expr);
    void accept(Visitor* visitor) override;  
};

