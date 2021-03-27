#pragma once

#include <base.hpp>
#include <vector>

class Main_class;
class Class_declarations;

class Program: public Base
{
    #include <friends_visitors>

    std::vector<Class_declaration*> declarations;

    Main_class* main_class;
    Class_declarations* class_declarations;
    

public:
    Program(Main_class* main_class, Class_declarations* class_declarations);
    void accept(Visitor* visitor) override;

    void optimize() {
        optimization_visitor v;
        accept(&v);
    }
};
