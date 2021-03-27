#pragma once

#include <base.hpp>

class Variable_declaration;
class Method_declaration;

class Declarations: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class Empty_Declarations: public Declarations
{
    #include <friends_visitors>
public:
    Empty_Declarations();
    void accept(Visitor* visitor) override;
};

class Declarations_with_variable: public Declarations
{
    #include <friends_visitors>
    Declarations* prev_decls;
    Variable_declaration* var_decl;
public:
    Declarations_with_variable(Declarations* prev_decls, Variable_declaration* var_decl);
    void accept(Visitor* visitor) override;
};

class Declarations_with_method: public Declarations
{
    #include <friends_visitors>
    Declarations* prev_decls;
    Method_declaration* method_decl;
public:
    Declarations_with_method(Declarations* prev_decls, Method_declaration* method_decl);
    void accept(Visitor* visitor) override;
};
