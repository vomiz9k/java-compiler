 #pragma once
#ifndef DRIVER_INCLUDED
#define DRIVER_INCLUDED
#include <string>
#include <map>
#include <fstream>


#include <bison.hpp>
#include <lexer.hpp>
#include <visitor.hpp>

#include <irtree/visitors/PrintVisitor.h>

class Driver {
 public:
    Driver();

    ~Driver() {
        if (program != nullptr) {
            delete_visitor v;
            v.visit(program);
        }
    }

    void print(const std::string& filename) {
        gv_visitor v(filename);
        v.visit(program);
    }

    void interpret() {
        interpreter_visitor v;
        v.visit(program);
    }

    void symb() {
        symbol_table_visitor v;
        v.visit(program);
        v.dump();
    }

    void ir() {
        symbol_table_visitor v;
        v.visit(program);
        ir_tree_visitor ir;
        ir.visit(program);


        for (auto& i: ir.method_trees) {
            IRT::PrintVisitor p("ir_" + i.first + ".txt");
            i.second->Accept(&p);
        }
    }

    static void error_test();
    static void test_no_error(const std::string& filename);
    static void test_error_type(const std::string& filename, const std::string& got, const std::string& expected);
    static void test_error_undeclared(const std::string& filename, const std::string& var);
    static void error_uncatched(const std::string& filename);
    static void wrong_error(const std::string& exc, const std::string& filename);

    std::map<std::string, int> variables;

    int parse(const std::string& filename);

    friend class Lexer;
    Program* program;
    Lexer lexer;
    yy::parser bison;
};
#endif
