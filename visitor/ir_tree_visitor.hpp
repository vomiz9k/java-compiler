#pragma once

#include "visitor.hpp"



class ir_tree_visitor: public Visitor
{
    BaseScope* curr;
public:
    #include "visitor_header_body"

    bool is_field(std::string& name);
};