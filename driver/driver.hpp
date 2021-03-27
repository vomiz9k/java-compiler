 #pragma once
#ifndef DRIVER_INCLUDED
#define DRIVER_INCLUDED
#include <string>
#include <map>
#include <fstream>


#include <bison.hpp>
#include <lexer.hpp>
#include <visitor.hpp>



class Driver {
 public:
    Driver();

    ~Driver() {
        delete_visitor v;
        v.visit(program);
    }

    void print(const std::string& filename) {
        gv_visitor v(filename);
        v.visit(program);
    }

    std::map<std::string, int> variables;

    int parse(const std::string& filename);

    friend class Lexer;
    Program* program;
    Lexer lexer;
    yy::parser bison;
};
#endif
