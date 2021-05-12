#pragma once

#include <base.hpp>
#include "../type/type.hpp"

class Value: public Base
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;
public:
    SimpleType* type;
};

class IntValue: public Value
{
    #include <friends_visitors>
    int value;
public:
    IntValue(int value);
    void accept(Visitor* visitor) override;
};

class BoolValue: public Value
{
    #include <friends_visitors>
    bool value;
public:
    BoolValue(bool value);
    void accept(Visitor* visitor) override;
};