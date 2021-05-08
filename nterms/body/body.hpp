#pragma once

#include <base.hpp>
#include <vector>

class BaseScope;
class Statements;
class Statement;

class Body: public Base
{
    BaseScope* scope;
    std::vector<Statement*> stmts;
    #include <friends_visitors>
    Statements* statements;;
    
public:

    void SetScope(BaseScope* scope);
    Body(Statements* statements);
    void accept(Visitor* visitor) override;
};