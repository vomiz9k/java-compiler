#pragma once

#include <base.hpp>
#include <string>

class Expr;
class VariableDeclaration;
class Statements;
class Assignment;
class MethodInvocation;


class Statement: public Base
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
};

class IfElseStatement: public Statement
{
    #include <friends_visitors>
    Expr* condition;
    Statement* do_if_true;
    Statement* do_else;
public:

    IfElseStatement(Expr* condition, Statement* do_if_true, Statement* do_else);
    void accept(Visitor* visitor) override;
};

class IfStatement: public Statement
{
    #include <friends_visitors>
    Expr* condition;
    Statement* do_if_true;

public:
    IfStatement(Expr* condition, Statement* do_if_true);
    void accept(Visitor* visitor) override;
};

class AssertStatement: public Statement
{
    #include <friends_visitors>
    Expr* check;

public:
    AssertStatement(Expr* check);
    void accept(Visitor* visitor) override;
};

class VarDeclStatement: public Statement
{
    #include <friends_visitors>
    VariableDeclaration* decl;

public:
    VarDeclStatement(VariableDeclaration* decl);
    void accept(Visitor* visitor) override;  
};

class Body;
class ScopeStatement: public Statement
{
    #include <friends_visitors>
    Body* body;
    
public:
    ScopeStatement(Body* body);
    void accept(Visitor* visitor) override;
};

class WhileStatement: public Statement
{
    #include <friends_visitors>
    Expr* condition;
    Statement* do_if_true;

public:
    WhileStatement(Expr* condition, Statement* do_if_true);
    void accept(Visitor* visitor) override;
};

class PrintStatement: public Statement
{
    #include <friends_visitors>
    Expr* to_print;

public:
    PrintStatement(Expr* to_print);
    void accept(Visitor* visitor) override;
};

class AssignmentStatement: public Statement
{
    #include <friends_visitors>
    Assignment* assignment;

public:
    AssignmentStatement(Assignment* assignment);
    void accept(Visitor* visitor) override;
};

class ReturnStatement: public Statement
{
    #include <friends_visitors>
    Expr* to_return;

public:
    ReturnStatement(Expr* to_return);
    void accept(Visitor* visitor) override;
};

class MethodInvocationStatement: public Statement
{
    #include <friends_visitors>
    MethodInvocation* invocation;
public:
    MethodInvocationStatement(MethodInvocation* invocation);
    void accept(Visitor* visitor) override;
};


