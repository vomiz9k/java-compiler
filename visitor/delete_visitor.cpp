#include <big_include.hpp>
#include <visitor.hpp>
#include "delete_visitor.hpp"

void delete_visitor::visit(Program* ptr) {

    ptr->main_class->accept(this);
    ptr->class_declarations->accept(this);
    delete ptr;
}

void delete_visitor::visit(Main_class* ptr) {

    ptr->body->accept(this);
    
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Not_empty_Class_declarations* ptr) {
    
    ptr->class_decl->accept(this);
    ptr->prev_class_decls->accept(this);
    delete ptr;
}

void delete_visitor::visit(Empty_Class_declarations* ptr) {
    
    //nochildren
    delete ptr;
}

void delete_visitor::visit(Extended_Class_declaration* ptr) {

    ptr->declarations->accept(this);
    
    //name, base
    delete ptr->name;
    delete ptr->base;
    delete ptr;
}

void delete_visitor::visit(Not_extended_Class_declaration* ptr) {

    ptr->declarations->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Body* ptr) {
    
    ptr->statements->accept(this);
    delete ptr;
}


void delete_visitor::visit(Empty_Statements* ptr) {
    
    //nochildren
    delete ptr;
}

void delete_visitor::visit(Not_empty_Statements* ptr) {

    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
    delete ptr;
}

void delete_visitor::visit(If_else_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
    delete ptr;
}

void delete_visitor::visit(If_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    delete ptr;
}


void delete_visitor::visit(Assert_Statement* ptr) {

    ptr->check->accept(this);
    delete ptr;
}

void delete_visitor::visit(Var_decl_Statement* ptr) {

    ptr->decl->accept(this);
    delete ptr;
}

void delete_visitor::visit(Big_Statement* ptr) {

    ptr->body->accept(this);
    delete ptr;
}

void delete_visitor::visit(While_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    delete ptr;
}

void delete_visitor::visit(Print_Statement* ptr) {

    ptr->to_print->accept(this);
    delete ptr;
}

void delete_visitor::visit(Assignment_Statement* ptr) {

    ptr->assignment->accept(this);
    delete ptr;
}

void delete_visitor::visit(Return_Statement* ptr) {

    ptr->to_return->accept(this);
    delete ptr;
}

void delete_visitor::visit(Method_invocation_Statement* ptr) {

    ptr->invocation->accept(this);
    delete ptr;
}





void delete_visitor::visit(Declarations_with_variable* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
    delete ptr;
}

void delete_visitor::visit(Declarations_with_method* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
    delete ptr;
}

void delete_visitor::visit(Empty_Declarations* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(Method_declaration* ptr) {


    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Variable_declaration* ptr) {

    ptr->type->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Empty_Method_args* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(Single_Method_args* ptr) {

    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(Many_Method_args* ptr) {

    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(Method_arg* ptr) {

    ptr->type->accept(this);
    delete ptr;
}

void delete_visitor::visit(Last_Method_multiple_arg* ptr) {

    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(Many_Method_multiple_arg* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(Simple_Type* ptr) {

    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Array_Type* ptr) {

    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
    delete ptr;
}

void delete_visitor::visit(Single_Lvalue* ptr) {

    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Arr_el_Lvalue* ptr) {


    ptr->index->accept(this);
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Field_Lvalue* ptr) {
    
    ptr->invocation->accept(this);
    delete ptr;
}


void delete_visitor::visit(Field_arr_el_Lvalue* ptr) {

    ptr->invocation->accept(this);
    ptr->index->accept(this);
}


void delete_visitor::visit(Method_invocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Field_invocation* ptr) {

    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Empty_Expressions* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(Single_Expressions* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(Many_Expressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(Single_Multiple_expressions* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(Many_Multiple_expressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(Value_Expr* ptr) {

    ptr->value->accept(this);
    delete ptr;
}

void delete_visitor::visit(Id_Expr* ptr) {
    
    //name
    delete ptr;
}

void delete_visitor::visit(Array_el_Expr* ptr) {

    ptr->array->accept(this);
    ptr->index->accept(this);
    delete ptr;
}
void delete_visitor::visit(Length_Expr* ptr) {

    ptr->array->accept(this);
    delete ptr;
}

void delete_visitor::visit(Field_invocation_Expr* ptr) {

    ptr->invocation->accept(this);
    delete ptr;
}

void delete_visitor::visit(New_arr_Expr* ptr) {


    ptr->count->accept(this);
    //type
    delete ptr->type;
    delete ptr;
}

void delete_visitor::visit(New_single_Expr* ptr) {
    
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(This_Expr* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(Not_Expr* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(Method_invocation_Expr* ptr) {
    
    ptr->invocation->accept(this);
    delete ptr;
}

void delete_visitor::visit(Plus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Minus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Star_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Slash_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Percent_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(And_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Or_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Smaller_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Bigger_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Not_equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(Brackets_Expr* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(Number_Value* ptr) {

    //value(int)
    delete ptr;
}

void delete_visitor::visit(TF_Value* ptr) {

    //value(bool)
    delete ptr;
}