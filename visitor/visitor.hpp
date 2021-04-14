#pragma once

//#include <big_include.hpp>
#include <iostream>

class Base;

class Program;
class Main_class;

class Body;
class Empty_Statements;
class Not_empty_Statements;

class Statement;
class If_else_Statement;
class If_Statement;
class Assert_Statement;
class Var_decl_Statement;
class Big_Statement;
class While_Statement;
class Print_Statement;
class Assignment_Statement;
class Return_Statement;
class Method_invocation_Statement;


class Not_empty_Class_declarations;
class Empty_Class_declarations;


class Class_declaration;
class Extended_Class_declaration;
class Not_extended_Class_declaration;


class Declarations;
class Declarations_with_variable;
class Declarations_with_method;
class Empty_Declarations;

class Method_declaration;
class Variable_declaration;

class Method_args;
class Empty_Method_args;
class Single_Method_args;
class Many_Method_args;
class Method_arg;
class Last_Method_multiple_arg;
class Many_Method_multiple_arg;

class Simple_Type;
class Array_Type;

class Assignment;

class Single_Lvalue;
class Arr_el_Lvalue;
class Field_Lvalue;
class Field_arr_el_Lvalue;

class Method_invocation;
class Field_invocation;

class Empty_Expressions;
class Single_Expressions;
class Many_Expressions;
class Single_Multiple_expressions;
class Many_Multiple_expressions;

class Value_Expr;
class Id_Expr;
class Array_el_Expr;
class Length_Expr;


class New_arr_Expr;
class New_single_Expr;
class Field_invocation_Expr;
class This_Expr;
class Not_Expr;
class Method_invocation_Expr;
class Plus_Expr;
class Minus_Expr;
class Star_Expr;
class Slash_Expr;
class Percent_Expr;
class And_Expr;
class Or_Expr;
class Smaller_Expr;
class Bigger_Expr;
class Equal_Expr;
class Not_equal_Expr;
class Brackets_Expr;

class Number_Value;
class TF_Value;

class Visitor
{   
    
public:
    virtual void visit(Program*) = 0; //program
    virtual void visit(Main_class*) = 0;

    virtual void visit(Not_empty_Class_declarations*) = 0;
    virtual void visit(Empty_Class_declarations*) = 0;   
    
    virtual void visit(Body*) = 0;
    virtual void visit(Empty_Statements*) = 0;
    virtual void visit(Not_empty_Statements*) = 0;

    virtual void visit(If_else_Statement*) = 0;
    virtual void visit(If_Statement*) = 0;
    virtual void visit(Assert_Statement*) = 0;
    virtual void visit(Var_decl_Statement*) = 0;
    virtual void visit(Big_Statement*) = 0;
    virtual void visit(While_Statement*) = 0;
    virtual void visit(Print_Statement*) = 0;
    virtual void visit(Assignment_Statement*) = 0;
    virtual void visit(Return_Statement*) = 0;
    virtual void visit(Method_invocation_Statement*) = 0;


    virtual void visit(Extended_Class_declaration*) = 0;
    virtual void visit(Not_extended_Class_declaration*) = 0;
    

    virtual void visit(Declarations_with_variable*) = 0;
    virtual void visit(Declarations_with_method*) = 0;
    virtual void visit(Empty_Declarations*) = 0;

    virtual void visit(Method_declaration*) = 0;
    virtual void visit(Variable_declaration*) = 0;
    
    virtual void visit(Empty_Method_args*) = 0;
    virtual void visit(Single_Method_args*) = 0;
    virtual void visit(Many_Method_args*) = 0;
    virtual void visit(Method_arg*) = 0;
    virtual void visit(Last_Method_multiple_arg*) = 0;
    virtual void visit(Many_Method_multiple_arg*) = 0;

    virtual void visit(Simple_Type*) = 0;
    virtual void visit(Array_Type*) = 0;

    virtual void visit(Assignment*) = 0;

    virtual void visit(Single_Lvalue*) = 0;
    virtual void visit(Arr_el_Lvalue*) = 0;
    virtual void visit(Field_Lvalue*) = 0;
    virtual void visit(Field_arr_el_Lvalue*) = 0;

    virtual void visit(Method_invocation*) = 0;
    virtual void visit(Field_invocation*) = 0;

    virtual void visit(Empty_Expressions*) = 0;
    virtual void visit(Single_Expressions*) = 0;
    virtual void visit(Many_Expressions*) = 0;
    virtual void visit(Single_Multiple_expressions*) = 0;
    virtual void visit(Many_Multiple_expressions*) = 0;

    virtual void visit(Value_Expr*) = 0;
    virtual void visit(Id_Expr*) = 0;
    virtual void visit(Array_el_Expr*) = 0;
    virtual void visit(Length_Expr*) = 0;

    virtual void visit(Field_invocation_Expr*) = 0;

    virtual void visit(New_arr_Expr*) = 0;
    virtual void visit(New_single_Expr*) = 0;
    virtual void visit(This_Expr*) = 0;

    virtual void visit(Not_Expr*) = 0;
    virtual void visit(Method_invocation_Expr*) = 0;
    virtual void visit(Plus_Expr*) = 0;
    virtual void visit(Minus_Expr*) = 0;
    virtual void visit(Star_Expr*) = 0;
    virtual void visit(Slash_Expr*) = 0;
    virtual void visit(Percent_Expr*) = 0;
    virtual void visit(And_Expr*) = 0;
    virtual void visit(Or_Expr*) = 0;
    virtual void visit(Smaller_Expr*) = 0;
    virtual void visit(Bigger_Expr*) = 0;
    virtual void visit(Equal_Expr*) = 0;
    virtual void visit(Not_equal_Expr*) = 0;
    virtual void visit(Brackets_Expr*) = 0;

    virtual void visit(Number_Value*) = 0;
    virtual void visit(TF_Value*) = 0;
};

#include "template_visitor.hpp" //template for other visitors

#include "delete_visitor.hpp"
#include "gv_visitor.hpp"
#include "optimization_visitor.hpp"
#include "interpreter_visitor.hpp"
#include "symbol_table_visitor.hpp"
#include "syntax_check_visitor.hpp"











