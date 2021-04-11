#pragma once

#include <string>
#include <base.hpp>

class Type;
class Method_args;
class Statements;
class BaseScope;

class Declaration : public Base 
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class Method_declaration: public Declaration
{
    #include <friends_visitors>
    BaseScope* scope;
    Type* type;
    std::string* name;
    Method_args* args;
    Body* body;
public:

    Method_declaration (Type* type,
                        std::string* name,
                        Method_args* args,
                        Body* body);
                        
    void accept(Visitor* visitor) override;

    void SetScope(BaseScope* scope);
};

class Type;
class Method_args;
class Statements;

class Variable_declaration: public Declaration {
    
    #include <friends_visitors>
    Type* type;
    std::string* name;

public:
    Variable_declaration (Type* type, std::string* name);      
    void accept(Visitor* visitor) override;
};