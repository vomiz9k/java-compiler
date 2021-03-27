#pragma once

#include <string>
#include <base.hpp>

class Statements;

class Main_class: public Base
{
    #include <friends_visitors>
    
    std::string* class_name;
    Statements* statements;
    
public:
    Main_class(std::string* class_name, Statements* statements);
    void accept(Visitor* visitor) override;
};