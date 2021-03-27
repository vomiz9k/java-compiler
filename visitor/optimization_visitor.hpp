#pragma once
#include "visitor.hpp"

class Expressions;

class optimization_visitor: public Visitor
{
    Program* program;
    Method_args* args;
    Declarations* decls;
    Class_declaration* curr_class;
    Body* body;
    Expressions* exprs;
    bool in_statements = false;
    bool in_empty = false;
public:

   #include "visitor_header_body"
};