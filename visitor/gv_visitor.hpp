#pragma once
#include "visitor.hpp"
#include <fstream>

class gv_visitor: public Visitor //works only on optimized visitor
{
    std::ofstream out;
    void box(const void* ptr, const std::string& name);
    void arrow(const void* first, const void* second);
    void arrow(const void* first, const void* second, const std::string& text);
public:
    gv_visitor(const std::string&);

    #include "visitor_header_body"
};