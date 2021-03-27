#include <big_include.hpp>
#include <visitor.hpp>
#include "interpreter_visitor.hpp"

void interpreter_visitor::visit(Program* ptr) {

    ptr->main_class->accept(this);
    //ptr->class_declarations->accept(this);
}

void interpreter_visitor::visit(Main_class* ptr) {

    ptr->body->accept(this);
    //class_name
}


void interpreter_visitor::visit(Body* ptr) {
    for (auto i: ptr->stmts) {
        i->accept(this);
    }
    //nochildren
}

void interpreter_visitor::visit(If_else_Statement* ptr) {

    ptr->condition->accept(this);
    if(result)
        ptr->do_if_true->accept(this);
    else
        ptr->do_else->accept(this);
}

void interpreter_visitor::visit(If_Statement* ptr) {
    ptr->condition->accept(this);
    if (result)
        ptr->do_if_true->accept(this);
}


void interpreter_visitor::visit(Assert_Statement* ptr) {
    ptr->check->accept(this);
    if (!result)
        throw "ASSERTATION";
}

void interpreter_visitor::visit(Var_decl_Statement* ptr) {
    ptr->decl->accept(this);
}

void interpreter_visitor::visit(Big_Statement* ptr) {
    ptr->body->accept(this);
}

void interpreter_visitor::visit(While_Statement* ptr) {
    ptr->condition->accept(this);
    while(result) {
        ptr->do_if_true->accept(this);
        ptr->condition->accept(this);
    }
}

void interpreter_visitor::visit(Print_Statement* ptr) {

    ptr->to_print->accept(this);
    std::cout << "print: " << result << '\n';
}

void interpreter_visitor::visit(Field_invocation* ptr) {
    
}

void interpreter_visitor::visit(Assignment_Statement* ptr) {
    ptr->assignment->accept(this);
}



void interpreter_visitor::visit(Variable_declaration* ptr) {
    ptr->type->accept(this);
    if(!is_array)
        var[*ptr->name];
    else
        array[*ptr->name];
    
    //name
}


void interpreter_visitor::visit(Simple_Type* ptr) {
    if (*ptr->name != "int" && *ptr->name != "bool")   
        throw "ploxo";
    is_array = false;
    //name
}

void interpreter_visitor::visit(Array_Type* ptr) {
    if (*ptr->name != "int" && *ptr->name != "bool")   
        throw "ploxo";
    is_array = true;
    //name
}

void interpreter_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    if (lvalue == nullptr)
        throw "bad lvalue";
    auto val_ptr = lvalue;
    ptr->rvalue->accept(this);
    *val_ptr = result;
}

void interpreter_visitor::visit(Single_Lvalue* ptr) {
    if(var.count(*ptr->name) == 0)
        throw "unknown variable";
    
    lvalue = &var[*ptr->name];
}

void interpreter_visitor::visit(Arr_el_Lvalue* ptr) {
    //TODO
}

void interpreter_visitor::visit(Field_Lvalue* ptr) {
    //TODO
}

void interpreter_visitor::visit(Field_arr_el_Lvalue* ptr) {
    //TODO
}


void interpreter_visitor::visit(Value_Expr* ptr) {
    ptr->value->accept(this);
}

void interpreter_visitor::visit(Id_Expr* ptr) {
    result = var[*ptr->name];
}

void interpreter_visitor::visit(New_arr_Expr* ptr) {

}


void interpreter_visitor::visit(Not_Expr* ptr) {

    ptr->expr->accept(this);
    result = !result;
}


void interpreter_visitor::visit(Plus_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first + result);
}

void interpreter_visitor::visit(Minus_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first - result);
}

void interpreter_visitor::visit(Star_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first * result);
}

void interpreter_visitor::visit(Slash_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first / result);
}

void interpreter_visitor::visit(Percent_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first % result);
}

void interpreter_visitor::visit(And_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first && result);
}

void interpreter_visitor::visit(Or_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first || result);
}

void interpreter_visitor::visit(Smaller_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first < result);
}

void interpreter_visitor::visit(Bigger_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first > result);
}

void interpreter_visitor::visit(Equal_Expr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first == result);
}

void interpreter_visitor::visit(Not_equal_Expr* ptr) {
    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first != result);
}

void interpreter_visitor::visit(Brackets_Expr* ptr) {

    ptr->expr->accept(this);
}

void interpreter_visitor::visit(Number_Value* ptr) {
    result = ptr->value;
    //value(int)
}

void interpreter_visitor::visit(TF_Value* ptr) {
    result = ptr->value;
    //value(bool)
}