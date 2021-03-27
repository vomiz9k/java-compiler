#pragma once

#include <base.hpp>
#include <string>


class Type: public Base
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class Simple_Type: public Type
{
    #include <friends_visitors>
    std::string* name;
public:
    Simple_Type(std::string* name);
    void accept(Visitor* visitor) override;
};

class Array_Type: public Type
{
    #include <friends_visitors>
    std::string* name;
public:
    Array_Type(std::string* name);
    void accept(Visitor* visitor) override;
};