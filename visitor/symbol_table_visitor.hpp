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

    size_t tabs = 0;
    void dump(BaseScope* now) {
        for(auto i: now->symbols) {
            for(int i = 0; i < tabs; ++i) {
                std::cout << '\t';
            }
            std::cout << i.first << ' ';
        }
        std::cout << '\n';
        ++tabs;
        for (auto i: now->children) {
            dump(i);
        }
        --tabs;
    }
};