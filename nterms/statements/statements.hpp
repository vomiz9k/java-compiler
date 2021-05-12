#pragma once

#include <base.hpp>
class Statement;

class Statements: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};


class EmptyStatements: public Statements
{
    #include <friends_visitors>
public:
    EmptyStatements();
    void accept(Visitor* visitor) override;
};

class NotEmptyStatements: public Statements
{
    #include <friends_visitors>
    Statements* prev_statements;
    Statement* statement;
public:
    NotEmptyStatements(Statements* prev_statements, Statement* statement);
    void accept(Visitor* visitor) override;
};

