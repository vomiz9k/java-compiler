#include <driver.hpp>

Driver::Driver() : lexer(*this), bison(lexer, *this) {}

int Driver::parse(const std::string& filename)
{
    std::ifstream in(filename);
    lexer.yyrestart(in);
    int res = bison();
    program->optimize();
    return res;
}

void Driver::error_test() {
    test_error_undeclared("error_declared_in_upper_scope", "a");
    test_error_undeclared("error_declared_later", "a");
    test_error_undeclared("error_undeclared_class", "Undeclared");
    test_error_undeclared("error_undeclared_var", "a");
    test_error_type("error_type_1", "int", "Declared");
    test_error_type("error_type_2", "int", "bool");
    test_error_type("error_type_3", "Declared", "int");
    test_error_type("error_type_4", "int", "bool");
    test_no_error("good_example_1");
    test_no_error("good_example_2");
    //test_no_error("good_example_3");
    //test_no_error("good_example_4");
}

void Driver::test_no_error(const std::string& filename) {
    Driver d;
    d.parse("tests/type_errors/" + filename);
    try {
        d.symb();
    } catch (const std::string& exc) {
        wrong_error(exc, filename);
    }
}

void Driver::test_error_type(const std::string& filename, const std::string& got, const std::string& expected) {
    Driver d;
    d.parse("tests/type_errors/" + filename);
    try {
        d.symb();
    } catch (const std::string& exc) {
        if (exc != "syntax error: got " + got + ", " + expected + " expected")
            wrong_error(exc, filename);
        return;
    }
    error_uncatched(filename);
}

void Driver::test_error_undeclared(const std::string& filename, const std::string& var) {
    Driver d;
    d.parse("tests/type_errors/" + filename);
    try {
        d.symb();
    } catch (const std::string& exc) {
        if (exc != "syntax error: " + var + " not declared")
            wrong_error(exc, filename);
        return;
    }
    error_uncatched(filename);
}


void Driver::error_uncatched(const std::string& filename) {
    std::cout << "uncatched error in " + filename + '\n';
}

void Driver::wrong_error(const std::string& exc, const std::string& filename) {
    std::cout << "wrong error in " + filename + ": " + exc + '\n';
}