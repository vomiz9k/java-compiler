#pragma once

#include <string>
#include <base.hpp>

class Body;

class Main_class: public Base
{
    #include <friends_visitors>
    
    std::string* class_name;
    Body* body;
    
public:
    Main_class(std::string* class_name, Body* body);
    void accept(Visitor* visitor) override;
};