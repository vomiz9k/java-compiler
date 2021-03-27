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

class Empty_Expressions: public Expressions
{
    #include <friends_visitors>
public:

    Empty_Expressions();
    void accept(Visitor* visitor) override;
};

class Single_Expressions: public Expressions
{
    #include <friends_visitors>
    Expr* expr;
 public:

    Single_Expressions(Expr* expr);
    void accept(Visitor* visitor) override;    
};


class Multiple_expressions;

class Many_Expressions: public Expressions
{
    #include <friends_visitors>
    Expr* expr;
    Multiple_expressions* prev_exprs;
public:
    Many_Expressions(Multiple_expressions* prev_exprs, Expr* expr);
    void accept(Visitor* visitor) override;    
};

class Multiple_expressions: public Base //other rule
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
};

class Single_Multiple_expressions: public Multiple_expressions
{
    #include <friends_visitors>
    Expr* expr;
public:
    Single_Multiple_expressions(Expr* expr);
    void accept(Visitor* visitor) override;  
};

class Many_Multiple_expressions: public Multiple_expressions
{
    #include <friends_visitors>
    Multiple_expressions* prev_exprs;
    Expr* expr;
public:
    Many_Multiple_expressions(Multiple_expressions* prev_exprs, Expr* expr);
    void accept(Visitor* visitor) override;  
};

