#include <driver.hpp>

Driver::Driver() : lexer(*this), bison(lexer, *this) {}
Driver::~Driver() {
    if (program != nullptr) {
        delete_visitor v;
        v.visit(program);
    }
}

void Driver::print(const std::string& filename) {
    gv_visitor v(filename);
    v.visit(program);
}

void Driver::interpret() {
    interpreter_visitor v;
    v.visit(program);
}

void Driver::symb() {
    symbol_table_visitor v;
    v.visit(program);
    v.dump();
}

void Driver::ir(const std::string& dir) {
    symbol_table_visitor v;
    v.visit(program);
    ir_tree_visitor ir;
    ir.visit(program);


    for (auto& i: ir.method_trees) {
        IRT::PrintVisitor pv(dir + "/ir_before_optimization_" + i.first + ".txt");
        i.second->Accept(&pv);
    }

    for (auto& i: ir.method_trees) {
        IRT::DoubleCallEliminateVisitor dcev;
        i.second->Accept(&dcev);
        i.second = dcev.GetTree();

        IRT::EseqEliminateVisitor eev;
        i.second->Accept(&eev);

        IRT::PrintVisitor pv(dir + "/ir_after_optimization_" + i.first + ".txt");
        i.second->Accept(&pv);
    }
}

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
}

void Driver::test_no_error(const std::string& filename) {
    try {
        Driver d;
        d.parse("tests/type_errors/" + filename);
        d.symb();
    } catch (const std::string& exc) {
        wrong_error(exc, filename);
    }
}

void Driver::test_error_type(const std::string& filename, const std::string& got, const std::string& expected) {
    try {
        Driver d;
        d.parse("tests/type_errors/" + filename);
        d.symb();
    } catch (const std::string& exc) {
        if (exc != "syntax error: got " + got + ", " + expected + " expected")
            wrong_error(exc, filename);
        return;
    }
    error_uncatched(filename);
}

void Driver::test_error_undeclared(const std::string& filename, const std::string& var) {
    try {
        Driver d;
        d.parse("tests/type_errors/" + filename);
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