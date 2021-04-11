#pragma once
#include "visitor.hpp"
#include <base_scope.hpp>
#include <iostream>

class symbol_table_visitor: public Visitor
{
public:
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
};