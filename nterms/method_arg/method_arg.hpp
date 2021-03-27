#pragma once

#include <string>
#include <base.hpp>

class Type;

class Method_arg: public Base
{        
    #include <friends_visitors>
    Type* type;
    std::string* name;
public:
    Method_arg(Type* type, std::string* name);
    void accept(Visitor* visitor) override;
};
