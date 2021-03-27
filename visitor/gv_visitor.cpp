#include <big_include.hpp>
#include <visitor.hpp>
#include "gv_visitor.hpp"

#include <fstream>
#include <string>
#include <sstream>

const std::string Endl = ";\n";

void gv_visitor::box(const void* ptr, const std::string& name) {

    out << "\"box" << (unsigned long long)ptr << "\" [label=\"" << name << "\"];\n";
}

void gv_visitor::arrow(const void* first, const void* second) {
    out << "\"box" << (unsigned long long)first << "\" -> \"box" << (unsigned long long)second << "\";\n";
}

void gv_visitor::arrow(const void* first, const void* second, const std::string& text) {
    out << "\"box" << (unsigned long long)first << "\" -> \"box" << (unsigned long long)second << "\"[label=\"" << text << "\"];\n";
}

gv_visitor::gv_visitor(const std::string& filename) : out(filename) {

}

void gv_visitor::visit(Program* ptr) {
    out << "digraph Program {\n";

    box(ptr, "Program");

    
    ptr->main_class->accept(this);
arrow(ptr, ptr->main_class);

    ptr->class_declarations->accept(this);
    arrow(ptr, ptr->class_declarations);
    out << "}";
}

void gv_visitor::visit(Main_class* ptr) {
    box(ptr, "Main_class: " + *ptr->class_name);
    arrow(ptr, ptr->statements);
    ptr->statements->accept(this);
    //class_name
}

void gv_visitor::visit(Not_empty_Class_declarations* ptr) {
    box(ptr, "Not_empty_Class_declarations");
    arrow(ptr, ptr->class_decl);
    ptr->class_decl->accept(this);

    arrow(ptr, ptr->prev_class_decls);
    ptr->prev_class_decls->accept(this);
}

void gv_visitor::visit(Empty_Class_declarations* ptr) {
    box(ptr, "Empty_Class_Declarations");
    //nochildren
}

void gv_visitor::visit(Extended_Class_declaration* ptr) {
    box(ptr, "Class Declaration: " + *ptr->name + ". Extended by " + *ptr->base);
    arrow(ptr, ptr->declarations);
    ptr->declarations->accept(this);
    
    //name, base
}

void gv_visitor::visit(Not_extended_Class_declaration* ptr) {
    box(ptr, "Class Decalration: " + *ptr->name);
    arrow(ptr, ptr->declarations);
    ptr->declarations->accept(this);
    //name
}

void gv_visitor::visit(Empty_Statements* ptr) {
    box(ptr, "Empty");
    //nochildren
}

void gv_visitor::visit(Not_empty_Statements* ptr) {
    box(ptr, "Not empty statements");
    arrow(ptr, ptr->prev_statements);
    ptr->prev_statements->accept(this);
    arrow(ptr, ptr->statement);
    ptr->statement->accept(this);
}

void gv_visitor::visit(If_else_Statement* ptr) {
    box(ptr, "if else statement");
    arrow(ptr, ptr->condition, "condition");
    ptr->condition->accept(this);
    arrow(ptr, ptr->do_if_true, "true");
    ptr->do_if_true->accept(this);
    arrow(ptr, ptr->do_else, "else");
    ptr->do_else->accept(this);
}

void gv_visitor::visit(If_Statement* ptr) {
    box(ptr, "if statement");
    arrow(ptr, ptr->condition, "condition");
    ptr->condition->accept(this);
    arrow(ptr, ptr->do_if_true, "true");
    ptr->do_if_true->accept(this);
}


void gv_visitor::visit(Assert_Statement* ptr) {
    box(ptr, "assert");
    arrow(ptr, ptr->check);
    ptr->check->accept(this);
}

void gv_visitor::visit(Var_decl_Statement* ptr) {
    box(ptr, "Var decl stmt");
    arrow(ptr, ptr->decl);
    ptr->decl->accept(this);
}

void gv_visitor::visit(Big_Statement* ptr) {
    box(ptr, "new scope");
    arrow(ptr, ptr->statements);
    ptr->statements->accept(this);
}

void gv_visitor::visit(While_Statement* ptr) {
    box(ptr, "while");
    arrow(ptr, ptr->condition, "condition");
    ptr->condition->accept(this);
    arrow(ptr, ptr->do_if_true, "true");
    ptr->do_if_true->accept(this);
}

void gv_visitor::visit(Print_Statement* ptr) {
    box(ptr, "print");
    arrow(ptr, ptr->to_print);
    ptr->to_print->accept(this);
}

void gv_visitor::visit(Assignment_Statement* ptr) {
    box(ptr, "assignment stmt");
    arrow(ptr, ptr->assignment);
    ptr->assignment->accept(this);
}

void gv_visitor::visit(Return_Statement* ptr) {
    box(ptr, "return");
    arrow(ptr, ptr->to_return);
    ptr->to_return->accept(this);
}

void gv_visitor::visit(Method_invocation_Statement* ptr) {
    box(ptr, "method invoce stmt");
    arrow(ptr, ptr->invocation);
    ptr->invocation->accept(this);
}





void gv_visitor::visit(Declarations_with_variable* ptr) {
    box(ptr, "decl with variable");
    arrow(ptr, ptr->prev_decls, "decls");
    ptr->prev_decls->accept(this);
    arrow(ptr, ptr->var_decl, "var decl");
    ptr->var_decl->accept(this);
}

void gv_visitor::visit(Declarations_with_method* ptr) {
    box(ptr, "decl with method");
    arrow(ptr, ptr->prev_decls, "decls");
    ptr->prev_decls->accept(this);
    arrow(ptr, ptr->method_decl, "method decl");
    ptr->method_decl->accept(this);
}

void gv_visitor::visit(Empty_Declarations* ptr) {
    box(ptr, "empty");
    //nochildren
}

void gv_visitor::visit(Method_declaration* ptr) {
    box(ptr, "method decl: " + *ptr->name);
    arrow(ptr, ptr->type, "type");
    ptr->type->accept(this);
    arrow(ptr, ptr->args, "args");
    ptr->args->accept(this);
    arrow(ptr, ptr->statements, "body");
    ptr->statements->accept(this);
    //name
}

void gv_visitor::visit(Variable_declaration* ptr) {
    box(ptr, "var decl: " + *ptr->name);
    arrow(ptr, ptr->type, "type");
    ptr->type->accept(this);
    //name
}

void gv_visitor::visit(Empty_Method_args* ptr) {
    box(ptr, "empty");
    //nochildren
}

void gv_visitor::visit(Single_Method_args* ptr) {
    box(ptr, "single arg");
    arrow(ptr, ptr->arg);
    ptr->arg->accept(this);
}

void gv_visitor::visit(Many_Method_args* ptr) {
    box(ptr, "mnogo args");
    arrow(ptr, ptr->prev_args, "prev");
    ptr->prev_args->accept(this);
    arrow(ptr, ptr->arg, "last");
    ptr->arg->accept(this);
}

void gv_visitor::visit(Method_arg* ptr) {
    box(ptr, "arg");
    arrow(ptr, ptr->type, "type");
    ptr->type->accept(this);
}

void gv_visitor::visit(Last_Method_multiple_arg* ptr) {
    box(ptr, "first");
    arrow(ptr, ptr->arg);
    ptr->arg->accept(this);
}

void gv_visitor::visit(Many_Method_multiple_arg* ptr) {
    box(ptr, "mnogo args2");
    arrow(ptr, ptr->prev_args, "prev");
    ptr->prev_args->accept(this);
    arrow(ptr, ptr->arg, "last");
    ptr->arg->accept(this);
}

void gv_visitor::visit(Simple_Type* ptr) {
    box(ptr, "simple type: " + *ptr->name);
    //name
}

void gv_visitor::visit(Array_Type* ptr) {
    box(ptr, "array type: " + *ptr->name);
    //name
}

void gv_visitor::visit(Assignment* ptr) {
    box(ptr, "assignment");
    arrow(ptr, ptr->lvalue, "left");
    ptr->lvalue->accept(this);
    arrow(ptr, ptr->rvalue, "right");
    ptr->rvalue->accept(this);
}

void gv_visitor::visit(Method_invocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
}

void gv_visitor::visit(Field_invocation* ptr) {
    box(ptr, "field invoce: " + *ptr->name);
    //name
}

void gv_visitor::visit(Empty_Expressions* ptr) {
    box(ptr, "empty");
    //nochildren
}

void gv_visitor::visit(Single_Expressions* ptr) {
    box(ptr, "single expr");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(Many_Expressions* ptr) {
    box(ptr, "mnogo expr");
    arrow(ptr, ptr->prev_exprs, "prev");
    ptr->prev_exprs->accept(this);
    arrow(ptr, ptr->expr, "last");
    ptr->expr->accept(this);
}

void gv_visitor::visit(Single_Multiple_expressions* ptr) {
    box(ptr, "single expr 2");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(Many_Multiple_expressions* ptr) {
    box(ptr, "mnogo expr2");
    arrow(ptr, ptr->prev_exprs, "prev");
    ptr->prev_exprs->accept(this);
    arrow(ptr, ptr->expr, "last");
    ptr->expr->accept(this);
}

void gv_visitor::visit(Value_Expr* ptr) {
    box(ptr, "Value expr");
    arrow(ptr, ptr->value);
    ptr->value->accept(this);
}

void gv_visitor::visit(Id_Expr* ptr) {
    box(ptr, "id expr: " + *ptr->name);
    //name
}

void gv_visitor::visit(Array_el_Expr* ptr) {
    box(ptr, "array el expr");
    arrow(ptr, ptr->array, "arr");
    ptr->array->accept(this);
    arrow(ptr, ptr->index, "index");
    ptr->index->accept(this);
}
void gv_visitor::visit(Length_Expr* ptr) {
    box(ptr, "Length of");
    arrow(ptr, ptr->array);
    ptr->array->accept(this);
}

void gv_visitor::visit(Field_invocation_Expr* ptr) {
    box(ptr, "field invoce expr");
    arrow(ptr, ptr->invocation);
    ptr->invocation->accept(this);
}

void gv_visitor::visit(New_arr_Expr* ptr) {
    box(ptr, "new " + *ptr->type + " []");
    arrow(ptr, ptr->count, "count");
    ptr->count->accept(this);
    //type(str)
}

void gv_visitor::visit(New_single_Expr* ptr) {
    box(ptr, "new " + *ptr->name + " ()");
    //name
}

void gv_visitor::visit(This_Expr* ptr) {
    box(ptr, "this");
    //nochildren
}

void gv_visitor::visit(Not_Expr* ptr) {
    box(ptr, "Not(!)");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(Method_invocation_Expr* ptr) {
    box(ptr, "method invoce expr");
    arrow(ptr, ptr->invocation);
    ptr->invocation->accept(this);
}

void gv_visitor::visit(Plus_Expr* ptr) {
    box(ptr, "plus");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Minus_Expr* ptr) {
    box(ptr, "minus");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Star_Expr* ptr) {
    box(ptr, "star");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Slash_Expr* ptr) {
    box(ptr, "slash");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Percent_Expr* ptr) {
    box(ptr, "percent");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(And_Expr* ptr) {
    box(ptr, "and");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Or_Expr* ptr) {
    box(ptr, "or");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Smaller_Expr* ptr) {
    box(ptr, "<");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Bigger_Expr* ptr) {
    box(ptr, ">");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Equal_Expr* ptr) {
    box(ptr, "==");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Not_equal_Expr* ptr) {
    box(ptr, "!=");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(Brackets_Expr* ptr) {
    box(ptr, "into brackets");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(Number_Value* ptr) {
    std::stringstream stream;
    stream << "int: " << ptr->value;
    box(ptr, stream.str());
    //value(int)
}

void gv_visitor::visit(TF_Value* ptr) {
    std::stringstream stream;
    stream << "bool: " << ptr->value;
    box(ptr, stream.str());
    //value(bool)
}