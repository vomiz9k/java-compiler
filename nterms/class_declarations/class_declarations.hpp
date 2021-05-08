#pragma once

#include <string>
#include <base.hpp>

class Class_declaration;

class Class_declarations: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class EmptyClassDeclarations: public Class_declarations
{
    #include <friends_visitors>
public:
    EmptyClassDeclarations();
    void accept(Visitor* visitor);
};

class NotEmptyClassDeclarations: public Class_declarations
{
    #include <friends_visitors>
    Class_declarations* prev_class_decls;
    Class_declaration* class_decl;
public:
    NotEmptyClassDeclarations(Class_declarations* prev_class_decls, Class_declaration* class_decl);
    void accept(Visitor* visitor);
};