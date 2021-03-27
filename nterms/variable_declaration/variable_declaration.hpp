#pragma once

#include <string>
#include <base.hpp>

class Type;
class Method_args;
class Statements;

class Variable_declaration: public Base
{
    #include <friends_visitors>
    Type* type;
    std::string* name;

public:
    Variable_declaration (Type* type, std::string* name);      
    void accept(Visitor* visitor) override;
};