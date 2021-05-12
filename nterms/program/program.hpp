#pragma once

#include <base.hpp>
#include <vector>
#include <base_scope.hpp>
#include <visitor.hpp>

class MainClass;
class Class_declarations;

class Program: public Base
{
    #include <friends_visitors>
    BaseScope* scope;
    std::vector<Class_declaration*> declarations;

    MainClass* main_class;
    Class_declarations* class_declarations;
    

public:

    Program(MainClass* main_class, Class_declarations* class_declarations);
    void accept(Visitor* visitor) override;

    void SetScope(BaseScope* scope);

    void optimize() {
        optimization_visitor v;
        accept(&v);
    }
};
