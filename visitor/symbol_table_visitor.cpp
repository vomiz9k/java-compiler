#include <big_include.hpp>
#include <visitor.hpp>
#include "symbol_table_visitor.hpp"
#include <base_scope.hpp>
#include <base_symbol.hpp>

void symbol_table_visitor::visit(Program* ptr) {
    curr = new BaseScope();
    ptr->SetScope(curr);
    ptr->main_class->accept(this);

    for (auto i : ptr->declarations) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(Main_class* ptr) {
    auto old = curr;
    old->symbols[*ptr->name] = new ClassSymbol(ptr);
    curr = new BaseScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);
    
    ptr->body->accept(this);

    curr = old;
    //class_name
}


//unused
void symbol_table_visitor::visit(Not_empty_Class_declarations* ptr) {
    
    // ptr->class_decl->accept(this);
    // ptr->prev_class_decls->accept(this);
    
}

//unused
void symbol_table_visitor::visit(Empty_Class_declarations* ptr) {
    
    //nochildren
}

void symbol_table_visitor::visit(Extended_Class_declaration* ptr) {
    auto old = curr;
    old->symbols[*ptr->name] = new ClassSymbol(ptr);
    curr = new BaseScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);

    for(auto i : ptr->decls) {
        i->accept(this);
    }
    
    curr = old;
    //name, base
}

void symbol_table_visitor::visit(Not_extended_Class_declaration* ptr) {
    auto old = curr;
    old->symbols[*ptr->name] = new ClassSymbol(ptr);
    curr = new BaseScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);

    for(auto i : ptr->decls) {
        i->accept(this);
    }

    curr = old;
    //name
}

void symbol_table_visitor::visit(Body* ptr) {
    auto old = curr;
    curr = new BaseScope();
    old->children.push_back(curr);
    curr->parent = old;
    for (auto i: ptr->stmts) {
        i->accept(this);
    }
    curr = old;
    //nochildren
}


//unused
void symbol_table_visitor::visit(Empty_Statements* ptr) {
    
    //nochildren
}

//unused
void symbol_table_visitor::visit(Not_empty_Statements* ptr) {

    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
}

void symbol_table_visitor::visit(If_else_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
}

void symbol_table_visitor::visit(If_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}


void symbol_table_visitor::visit(Assert_Statement* ptr) {

    ptr->check->accept(this);
}

void symbol_table_visitor::visit(Var_decl_Statement* ptr) {

    ptr->decl->accept(this);
}

void symbol_table_visitor::visit(Big_Statement* ptr) {

    ptr->body->accept(this);
}

void symbol_table_visitor::visit(While_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}

void symbol_table_visitor::visit(Print_Statement* ptr) {

    ptr->to_print->accept(this);
}

void symbol_table_visitor::visit(Assignment_Statement* ptr) {

    ptr->assignment->accept(this);
}


void symbol_table_visitor::visit(Single_Lvalue* ptr) {

    //name
}

void symbol_table_visitor::visit(Arr_el_Lvalue* ptr) {


    ptr->index->accept(this);
    //name
}

void symbol_table_visitor::visit(Field_Lvalue* ptr) {
    
    ptr->invocation->accept(this);
}


void symbol_table_visitor::visit(Field_arr_el_Lvalue* ptr) {

    ptr->invocation->accept(this);
    ptr->index->accept(this);
}

void symbol_table_visitor::visit(Return_Statement* ptr) {

    ptr->to_return->accept(this);
}

void symbol_table_visitor::visit(Method_invocation_Statement* ptr) {

    ptr->invocation->accept(this);
}





//unused
void symbol_table_visitor::visit(Declarations_with_variable* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
}

//unused
void symbol_table_visitor::visit(Declarations_with_method* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
}

//unused
void symbol_table_visitor::visit(Empty_Declarations* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(Method_declaration* ptr) {
    curr->symbols[*ptr->name] = new MethodSymbol(ptr);
    auto old = curr;
    curr = new BaseScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);

    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);

    old = curr;
    //name
}

void symbol_table_visitor::visit(Variable_declaration* ptr) {
    curr->symbols[*ptr->name] = new VariableSymbol(ptr);
    ptr->type->accept(this);
    //name
}

void symbol_table_visitor::visit(Empty_Method_args* ptr) {

    //nochildren
}


void symbol_table_visitor::visit(Single_Method_args* ptr) {

    ptr->arg->accept(this);
}

void symbol_table_visitor::visit(Many_Method_args* ptr) {
    for(auto i : ptr->args) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(Method_arg* ptr) {
    curr->symbols[*ptr->name] = new VariableSymbol(ptr);
    ptr->type->accept(this);
    //name
}


//unused
void symbol_table_visitor::visit(Last_Method_multiple_arg* ptr) {

    ptr->arg->accept(this);
}


//unused
void symbol_table_visitor::visit(Many_Method_multiple_arg* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void symbol_table_visitor::visit(Simple_Type* ptr) {

    //name
}

void symbol_table_visitor::visit(Array_Type* ptr) {

    //name
}

void symbol_table_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
}

void symbol_table_visitor::visit(Method_invocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
}

void symbol_table_visitor::visit(Field_invocation* ptr) {

    //name
}

void symbol_table_visitor::visit(Empty_Expressions* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(Single_Expressions* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Many_Expressions* ptr) {
    for(auto i: ptr->exprs) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(Single_Multiple_expressions* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Many_Multiple_expressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Value_Expr* ptr) {

    ptr->value->accept(this);
}

void symbol_table_visitor::visit(Id_Expr* ptr) {
    
    //name
}

void symbol_table_visitor::visit(Array_el_Expr* ptr) {

    ptr->array->accept(this);
    ptr->index->accept(this);
}
void symbol_table_visitor::visit(Length_Expr* ptr) {

    ptr->array->accept(this);
}

void symbol_table_visitor::visit(Field_invocation_Expr* ptr) {

    ptr->invocation->accept(this);
}

void symbol_table_visitor::visit(New_arr_Expr* ptr) {

    ptr->count->accept(this);
    //type(str)
}

void symbol_table_visitor::visit(New_single_Expr* ptr) {
    
    //name
}

void symbol_table_visitor::visit(This_Expr* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(Not_Expr* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Method_invocation_Expr* ptr) {
    
    ptr->invocation->accept(this);
}

void symbol_table_visitor::visit(Plus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Minus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Star_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Slash_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Percent_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(And_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Or_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Smaller_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Bigger_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Not_equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void symbol_table_visitor::visit(Brackets_Expr* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Number_Value* ptr) {

    //value(int)
}

void symbol_table_visitor::visit(TF_Value* ptr) {

    //value(bool)
}