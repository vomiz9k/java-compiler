#pragma once

#include <string>
#include <base.hpp>

class BaseScope;

class Body;

class Main_class: public Base
{
    #include <friends_visitors>
    BaseScope* scope;    
    std::string* name;
    Body* body;
    
public:
    void SetScope(BaseScope* scope);
    Main_class(std::string* class_name, Body* body);
    void accept(Visitor* visitor) override;
};