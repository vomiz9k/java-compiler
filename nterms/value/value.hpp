#pragma once

#include <base.hpp>

class Value: public Base
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
public:
    Simple_Type* type;
};

class Number_Value: public Value
{
    #include <friends_visitors>
    int value;
public:
    Number_Value(int value);
    void accept(Visitor* visitor) override;
};

class TF_Value: public Value
{
    #include <friends_visitors>
    bool value;
public:
    TF_Value(bool value);
    void accept(Visitor* visitor) override;
};