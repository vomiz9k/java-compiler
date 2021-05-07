#pragma once

#include <visitor.hpp>


class Base
{
    #include <friends_visitors>

public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Base() = default;
};