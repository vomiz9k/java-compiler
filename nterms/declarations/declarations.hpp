#pragma once

#include <base.hpp>

class VariableDeclaration;
class MethodDeclaration;

class Declarations: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class EmptyDeclarations: public Declarations
{
    #include <friends_visitors>
public:
    EmptyDeclarations();
    void accept(Visitor* visitor) override;
};

class DeclarationsWithVariable: public Declarations
{
    #include <friends_visitors>
    Declarations* prev_decls;
    VariableDeclaration* var_decl;
public:
    DeclarationsWithVariable(Declarations* prev_decls, VariableDeclaration* var_decl);
    void accept(Visitor* visitor) override;
};

class DeclarationsWithMethod: public Declarations
{
    #include <friends_visitors>
    Declarations* prev_decls;
    MethodDeclaration* method_decl;
public:
    DeclarationsWithMethod(Declarations* prev_decls, MethodDeclaration* method_decl);
    void accept(Visitor* visitor) override;
};
