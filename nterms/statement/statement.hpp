#pragma once

#include <base.hpp>
#include <string>

class Expr;
class Variable_declaration;
class Statements;
class Assignment;
class Method_invocation;


class Statement: public Base
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
};

class If_else_Statement: public Statement
{
    #include <friends_visitors>
    Expr* condition;
    Statement* do_if_true;
    Statement* do_else;
public:

    If_else_Statement(Expr* condition, Statement* do_if_true, Statement* do_else);
    void accept(Visitor* visitor) override;
};

class If_Statement: public Statement
{
    #include <friends_visitors>
    Expr* condition;
    Statement* do_if_true;

public:
    If_Statement(Expr* condition, Statement* do_if_true);
    void accept(Visitor* visitor) override;
};

class Assert_Statement: public Statement
{
    #include <friends_visitors>
    Expr* check;

public:
    Assert_Statement(Expr* check);
    void accept(Visitor* visitor) override;
};

class Var_decl_Statement: public Statement
{
    #include <friends_visitors>
    Variable_declaration* decl;

public:
    Var_decl_Statement(Variable_declaration* decl);
    void accept(Visitor* visitor) override;  
};

class Big_Statement: public Statement
{
    #include <friends_visitors>
    Statements* statements;
    
public:
    Big_Statement(Statements* statements);
    void accept(Visitor* visitor) override;
};

class While_Statement: public Statement
{
    #include <friends_visitors>
    Expr* condition;
    Statement* do_if_true;

public:
    While_Statement(Expr* condition, Statement* do_if_true);
    void accept(Visitor* visitor) override;
};

class Print_Statement: public Statement
{
    #include <friends_visitors>
    Expr* to_print;

public:
    Print_Statement(Expr* to_print);
    void accept(Visitor* visitor) override;
};

class Assignment_Statement: public Statement
{
    #include <friends_visitors>
    Assignment* assignment;

public:
    Assignment_Statement(Assignment* assignment);
    void accept(Visitor* visitor) override;
};

class Return_Statement: public Statement
{
    #include <friends_visitors>
    Expr* to_return;

public:
    Return_Statement(Expr* to_return);
    void accept(Visitor* visitor) override;
};

class Method_invocation_Statement: public Statement
{
    #include <friends_visitors>
    Method_invocation* invocation;
public:
    Method_invocation_Statement(Method_invocation* invocation);
    void accept(Visitor* visitor) override;
};


