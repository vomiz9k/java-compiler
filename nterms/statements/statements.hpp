#pragma once

#include <base.hpp>
class Statement;

class Statements: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};


class Empty_Statements: public Statements
{
    #include <friends_visitors>
public:
    Empty_Statements();
    void accept(Visitor* visitor) override;
};

class Not_empty_Statements: public Statements
{
    #include <friends_visitors>
    Statements* prev_statements;
    Statement* statement;
public:
    Not_empty_Statements(Statements* prev_statements, Statement* statement);
    void accept(Visitor* visitor) override;
};

