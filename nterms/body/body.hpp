#pragma once

#include <base.hpp>
#include <vector>

class Statements;

class Body: public Base
{
    std::vector<Statement*> stmts;
    #include <friends_visitors>
    Statements* statements;;
    
public:
    Body(Statements* statements);
    void accept(Visitor* visitor) override;
};