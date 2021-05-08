#pragma once

#include <string>
#include <base.hpp>

class Type;
class Method_args;
class Statements;
class BaseScope;
class Body;

class Declaration : public Base 
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class MethodDeclaration: public Declaration
{
    #include <friends_visitors>
    BaseScope* scope;
    Type* type;
    std::string* name;
    Method_args* args;
    Body* body;
public:

    MethodDeclaration (Type* type,
                       std::string* name,
                       Method_args* args,
                       Body* body);
                        
    void accept(Visitor* visitor) override;

    void SetScope(BaseScope* scope);
};

class Type;
class Method_args;
class Statements;

class VariableDeclaration: public Declaration {
    
    #include <friends_visitors>
    Type* type;
    std::string* name;

public:
    VariableDeclaration (Type* type, std::string* name);
    void accept(Visitor* visitor) override;
};