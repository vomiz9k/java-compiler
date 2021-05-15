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

#include <irtree/visitors/DoubleCallEliminateVisitor.h>
#include <irtree/visitors/EseqEliminateVisitor.h>
class Driver {
 public:
    Driver();
    ~Driver();

    int parse(const std::string& filename);

    void print(const std::string& filename);

    void interpret(); //LEGACY I GUESS

    void symb(); //also prints scope tree in cout

    void ir(const std::string& dir);

    static void error_test();


    friend class Lexer;
    void set_program(Program* p) {
        program = p;
    }

private:
    static void test_no_error(const std::string& filename);
    static void test_error_type(const std::string& filename, const std::string& got, const std::string& expected);
    static void test_error_undeclared(const std::string& filename, const std::string& var);
    static void error_uncatched(const std::string& filename);
    static void wrong_error(const std::string& exc, const std::string& filename);

    Program* program;
    Lexer lexer;
    yy::parser bison;
};
#endif
