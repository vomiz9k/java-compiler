#pragma once

#include <base.hpp>
#include <string>

class Declarations;

class Class_declaration: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class Extended_Class_declaration: public Class_declaration
{
    #include <friends_visitors>
    std::string* name;
    std::string* base;
    Declarations* declarations;
public:
    Extended_Class_declaration(std::string* name, std::string* base, Declarations* declarations);
    void accept(Visitor* visitor) override;
};

class Not_extended_Class_declaration: public Class_declaration
{
    #include <friends_visitors>
    std::string* name;
    Declarations* declarations;
public:
    Not_extended_Class_declaration(std::string* name, Declarations* declarations);
    void accept(Visitor* visitor) override;
};