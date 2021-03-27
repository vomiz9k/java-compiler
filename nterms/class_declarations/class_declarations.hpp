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

class Empty_Class_declarations: public Class_declarations
{
    #include <friends_visitors>
public:
    Empty_Class_declarations();
    void accept(Visitor* visitor);
};

class Not_empty_Class_declarations: public Class_declarations
{
    #include <friends_visitors>
    Class_declarations* prev_class_decls;
    Class_declaration* class_decl;
public:
    Not_empty_Class_declarations(Class_declarations* prev_class_decls, Class_declaration* class_decl);
    void accept(Visitor* visitor);
};