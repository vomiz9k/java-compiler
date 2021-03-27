#pragma once

#include <base.hpp>
#include <string>

class Expr;
class Expressions;

class Method_invocation: public Base
{
    #include <friends_visitors>
    Expr* from;
    std::string* name;
    Expressions* args;
    
public:
    Method_invocation(Expr* from, std::string* name, Expressions* args);
    void accept(Visitor* visitor) override;
};