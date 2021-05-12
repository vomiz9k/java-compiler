#pragma once

#include <base.hpp>

class Expr;

class Assignment: public Base
{
    #include <friends_visitors>
    Expr* lvalue;
    Expr* rvalue;

    
public:
    Assignment(Expr* lvalue, Expr* rvalue);

    void accept(Visitor* visitor) override;
};