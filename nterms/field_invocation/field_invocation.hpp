#pragma once

#include <base.hpp>
#include <string>


class Type;

class FieldInvocation: public Base
{
    #include <friends_visitors>
    std::string* name;
    Type* type;    
public:
    FieldInvocation(std::string* name);
    void accept(Visitor* visitor) override;
};