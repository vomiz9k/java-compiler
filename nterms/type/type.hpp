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

class SimpleType: public Type
{
    #include <friends_visitors>

public:
    SimpleType(std::string* name);
    void accept(Visitor* visitor) override;
};

class ArrayType: public Type
{
    #include <friends_visitors>
public:
    ArrayType(std::string* name);
    void accept(Visitor* visitor) override;
};