#pragma once
#include "visitor.hpp"
#include <base_scope.hpp>
#include <iostream>


class MethodSymbol;
class ClassSymbol;
class Simple_Type;
class Type;

class symbol_table_visitor: public Visitor
{
    Simple_Type* int_simple;
    Simple_Type* bool_simple;
    ClassSymbol* curr_class;
    MethodSymbol* curr_method;

public:
    symbol_table_visitor();

    ~symbol_table_visitor();

    #include "visitor_header_body"

    BaseScope* curr;

    void dump() {
        dump(curr);
    }

    void dump(BaseScope* now) {
        for(auto i: now->symbols) {
            std::cout << i.first << ' ';
        }
        std::cout << '\n';
        for (auto i: now->children) {
            dump(i);
        }
    }

    BaseSymbol* Find(const std::string& name) {
        BaseScope* scope = curr;
        while (scope != nullptr && scope->symbols.count(name) == 0)
            scope = scope->parent;
        
        return scope == nullptr ? nullptr : scope->symbols[name];
    }

    BaseSymbol* Find(std::string* name) {
        return Find(*name);
    }



    void assert_declared(std::string* name, int type);

    void assert_not_declared_in_this_scope(std::string* name);

    void assert_type(std::string* checking, const std::string& needed);

    void assert_type(std::string* checking, const std::string& first, const std::string& second);

    void assert_array(Type* type);
};