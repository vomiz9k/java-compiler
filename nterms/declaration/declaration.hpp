#pragma once

#include <string>
#include <base.hpp>



class Declaration : public Base 
{
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

