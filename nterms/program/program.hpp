#pragma once

#include <base.hpp>

class Main_class;
class Class_declarations;

class Program: public Base
{
    #include <friends_visitors>

    Main_class* main_class;
    Class_declarations* class_declarations;

public:
    Program(Main_class* main_class, Class_declarations* class_declarations);
    void accept(Visitor* visitor) override;
};
