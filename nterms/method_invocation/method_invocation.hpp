#pragma once

#include <base.hpp>
#include <string>

class Expr;
class Expressions;
class Type;

class MethodInvocation: public Base
{
    #include <friends_visitors>
    Type* type;
    Expr* from;
    std::string* name;
    Expressions* args;
    
public:
    MethodInvocation(Expr* from, std::string* name, Expressions* args);
    void accept(Visitor* visitor) override;
};