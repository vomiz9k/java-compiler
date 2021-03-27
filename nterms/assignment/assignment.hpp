#pragma once

#include <base.hpp>

class Expr;
class Lvalue;

class Assignment: public Base
{
    #include <friends_visitors>
    Lvalue* lvalue;
    Expr* rvalue;
    
public:
    Assignment(Lvalue* lvalue, Expr* rvalue);
    void accept(Visitor* visitor) override;
};