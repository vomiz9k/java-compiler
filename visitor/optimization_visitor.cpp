#include <big_include.hpp>
#include <visitor.hpp>
#include "optimization_visitor.hpp"



void optimization_visitor::visit(Program* ptr) {
    program = ptr;
    ptr->main_class->accept(this);
    ptr->class_declarations->accept(this);
}

void optimization_visitor::visit(Main_class* ptr) {

    ptr->body->accept(this);
    //class_name
}

void optimization_visitor::visit(Not_empty_Class_declarations* ptr) {
    
    ptr->prev_class_decls->accept(this);
    ptr->class_decl->accept(this);
}

void optimization_visitor::visit(Empty_Class_declarations* ptr) {
    
    //nochildren
}

void optimization_visitor::visit(Extended_Class_declaration* ptr) {
    program->declarations.push_back(ptr);

    curr_class = ptr;
    ptr->declarations->accept(this);
    
    //name, base
}

void optimization_visitor::visit(Not_extended_Class_declaration* ptr) {
    curr_class = ptr;
    program->declarations.push_back(ptr);
    ptr->declarations->accept(this);
    //name
}

void optimization_visitor::visit(Body* ptr) {
    auto tmp = body;
    body = ptr;
    ptr->statements->accept(this);
    body = tmp;
    //nochildren
}

void optimization_visitor::visit(Empty_Statements* ptr) {
    in_empty = true;
    //nochildren
}

void optimization_visitor::visit(Not_empty_Statements* ptr) {
    ptr->prev_statements->accept(this);
    body->stmts.push_back(ptr->statement);
    ptr->statement->accept(this);
}

void optimization_visitor::visit(If_else_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
}

void optimization_visitor::visit(If_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}


void optimization_visitor::visit(Assert_Statement* ptr) {

    ptr->check->accept(this);
}

void optimization_visitor::visit(Var_decl_Statement* ptr) {

    ptr->decl->accept(this);
}

void optimization_visitor::visit(Big_Statement* ptr) {

    ptr->body->accept(this);
}

void optimization_visitor::visit(While_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}

void optimization_visitor::visit(Print_Statement* ptr) {

    ptr->to_print->accept(this);
}

void optimization_visitor::visit(Assignment_Statement* ptr) {

    ptr->assignment->accept(this);
}

void optimization_visitor::visit(Return_Statement* ptr) {

    ptr->to_return->accept(this);
}

void optimization_visitor::visit(Method_invocation_Statement* ptr) {

    ptr->invocation->accept(this);
}





void optimization_visitor::visit(Declarations_with_variable* ptr) {
    ptr->prev_decls->accept(this);
    curr_class->decls.push_back(ptr->var_decl);
    ptr->var_decl->accept(this);
}

void optimization_visitor::visit(Declarations_with_method* ptr) {
    
    ptr->prev_decls->accept(this);
    curr_class->decls.push_back(ptr->method_decl);
    ptr->method_decl->accept(this);
}

void optimization_visitor::visit(Empty_Declarations* ptr) {

    //nochildren
}

void optimization_visitor::visit(Method_declaration* ptr) {


    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);
    //name
}

void optimization_visitor::visit(Variable_declaration* ptr) {

    ptr->type->accept(this);
    //name
}

void optimization_visitor::visit(Empty_Method_args* ptr) {
    args = ptr;
    //nochildren
}

void optimization_visitor::visit(Single_Method_args* ptr) {
    args = ptr;
    ptr->arg->accept(this);
}

void optimization_visitor::visit(Many_Method_args* ptr) {
    args = ptr;
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void optimization_visitor::visit(Method_arg* ptr) {
    args->args.push_back(ptr);
    ptr->type->accept(this);
    //name
}

void optimization_visitor::visit(Last_Method_multiple_arg* ptr) {

    ptr->arg->accept(this);
}

void optimization_visitor::visit(Many_Method_multiple_arg* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void optimization_visitor::visit(Simple_Type* ptr) {

    //name
}

void optimization_visitor::visit(Array_Type* ptr) {

    //name
}

void optimization_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
}

void optimization_visitor::visit(Method_invocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
}

void optimization_visitor::visit(Field_invocation* ptr) {

    //name
}

void optimization_visitor::visit(Empty_Expressions* ptr) {

    //nochildren
}

void optimization_visitor::visit(Single_Expressions* ptr) {
    ptr->exprs.push_back(ptr->expr);
    ptr->expr->accept(this);
}

void optimization_visitor::visit(Many_Expressions* ptr) {
    auto old_exprs = exprs;
    exprs = ptr;
    ptr->prev_exprs->accept(this);
    exprs->exprs.push_back(ptr->expr);                       
    ptr->expr->accept(this);
    exprs = old_exprs;
}

void optimization_visitor::visit(Single_Multiple_expressions* ptr) {
    exprs->exprs.push_back(ptr->expr);
    ptr->expr->accept(this);
}

void optimization_visitor::visit(Many_Multiple_expressions* ptr) {

    ptr->prev_exprs->accept(this);
    exprs->exprs.push_back(ptr->expr);
    ptr->expr->accept(this);
}

void optimization_visitor::visit(Value_Expr* ptr) {

    ptr->value->accept(this);
}

void optimization_visitor::visit(Id_Expr* ptr) {
    
    //name
}

void optimization_visitor::visit(Array_el_Expr* ptr) {

    ptr->array->accept(this);
    ptr->index->accept(this);
}
void optimization_visitor::visit(Length_Expr* ptr) {

    ptr->array->accept(this);
}

void optimization_visitor::visit(Field_invocation_Expr* ptr) {

    ptr->invocation->accept(this);
}

void optimization_visitor::visit(New_arr_Expr* ptr) {

    ptr->count->accept(this);
    //type(str)
}

void optimization_visitor::visit(New_single_Expr* ptr) {
    
    //name
}

void optimization_visitor::visit(This_Expr* ptr) {

    //nochildren
}

void optimization_visitor::visit(Not_Expr* ptr) {

    ptr->expr->accept(this);
}

void optimization_visitor::visit(Method_invocation_Expr* ptr) {
    
    ptr->invocation->accept(this);
}

void optimization_visitor::visit(Plus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Minus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Star_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Slash_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Percent_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(And_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Or_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Smaller_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Bigger_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Not_equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(Brackets_Expr* ptr) {

    ptr->expr->accept(this);
}

void optimization_visitor::visit(Number_Value* ptr) {

    //value(int)
}

void optimization_visitor::visit(TF_Value* ptr) {

    //value(bool)
}