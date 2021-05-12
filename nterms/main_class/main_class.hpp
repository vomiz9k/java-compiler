#pragma once

#include <string>
#include <base.hpp>

class BaseScope;

class Body;

class MainClass: public Base
{
    #include <friends_visitors>
    BaseScope* scope;    
    std::string* name;
    Body* body;
    
public:
    void SetScope(BaseScope* scope);
    MainClass(std::string* class_name, Body* body);
    void accept(Visitor* visitor) override;
};