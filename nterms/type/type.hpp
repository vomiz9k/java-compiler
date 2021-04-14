#pragma once

#include <base.hpp>
#include <string>


class Type: public Base
{
    #include <friends_visitors>
    
public:
    std::string* name;
    virtual void accept(Visitor* visitor) = 0;
    bool is_array;
};

class Simple_Type: public Type
{
    #include <friends_visitors>

public:
    Simple_Type(std::string* name);
    void accept(Visitor* visitor) override;
};

class Array_Type: public Type
{
    #include <friends_visitors>
public:
    Array_Type(std::string* name);
    void accept(Visitor* visitor) override;
};