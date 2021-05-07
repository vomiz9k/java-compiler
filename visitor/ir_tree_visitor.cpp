#include <big_include.hpp>
#include <visitor.hpp>
#include "ir_tree_visitor.hpp"


#include <irtree/tree_wrapper/ExpressionWrapper.h>
#include <irtree/nodes/expressions/ConstExpression.h>
#include <irtree/tree_wrapper/conditional_wrappers/NegateConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/AndConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/OrConditionalWrapper.h>
#include <irtree/types/BinaryOperatorType.h>
#include <irtree/generators/Temporary.h>
#include <irtree/nodes/expressions/BinopExpression.h>
#include <irtree/nodes/expressions/TempExpression.h>
#include <irtree/nodes/expressions/MemExpression.h>
#include <irtree/nodes/statements/MoveStatement.h>
#include <irtree/tree_wrapper/StatementWrapper.h>
#include <irtree/nodes/statements/LabelStatement.h>
#include <irtree/nodes/statements/SeqStatement.h>
#include <irtree/nodes/statements/JumpStatement.h>
#include <irtree/nodes/ExpressionList.h>
#include <irtree/nodes/expressions/CallExpression.h>
#include <irtree/nodes/expressions/NameExpression.h>
#include <irtree/types/LogicOperatorType.h>
#include <irtree/tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.h>



bool ir_tree_visitor::is_field(std::string& name) {
    BaseScope* scope = curr;
    while (scope->symbols.count(name) == 0 && !scope->frame_start()) {
        scope = scope->parent;
    }

    return scope->symbols.count(name);
}



void ir_tree_visitor::visit(Program* ptr) {

    ptr->main_class->accept(this);

    for (auto i : ptr->declarations) {
        i->accept(this);
    }
}

void ir_tree_visitor::visit(Main_class* ptr) {

    ptr->body->accept(this);
    //class_name
}

void ir_tree_visitor::visit(Not_empty_Class_declarations* ptr) {

    ptr->class_decl->accept(this);
    ptr->prev_class_decls->accept(this);
}

void ir_tree_visitor::visit(Empty_Class_declarations* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(Extended_Class_declaration* ptr) {

    for (auto i : ptr->decls) {
        i->accept(this);
    }

    //name, base
}

void ir_tree_visitor::visit(Not_extended_Class_declaration* ptr) {

    for (auto i : ptr->decls) {
        i->accept(this);
    }
    //name
}

void ir_tree_visitor::visit(Body* ptr) {
    for (auto i: ptr->stmts) {
        i->accept(this);
    }
    //nochildren
}

void ir_tree_visitor::visit(Empty_Statements* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(Not_empty_Statements* ptr) {

    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
}

void ir_tree_visitor::visit(If_else_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
}

void ir_tree_visitor::visit(If_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}


void ir_tree_visitor::visit(Assert_Statement* ptr) {

    ptr->check->accept(this);
}

void ir_tree_visitor::visit(Var_decl_Statement* ptr) {

    ptr->decl->accept(this);
}

void ir_tree_visitor::visit(Big_Statement* ptr) {

    ptr->body->accept(this);
}

void ir_tree_visitor::visit(While_Statement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}

void ir_tree_visitor::visit(Print_Statement* ptr) {

    ptr->to_print->accept(this);
}

void ir_tree_visitor::visit(Assignment_Statement* ptr) {

    ptr->assignment->accept(this);
}


void ir_tree_visitor::visit(Single_Lvalue* ptr) {

    //name
}

void ir_tree_visitor::visit(Arr_el_Lvalue* ptr) {


    ptr->index->accept(this);
    //name
}

void ir_tree_visitor::visit(Field_Lvalue* ptr) {

    ptr->invocation->accept(this);
}


void ir_tree_visitor::visit(Field_arr_el_Lvalue* ptr) {

    ptr->invocation->accept(this);
    ptr->index->accept(this);
}

void ir_tree_visitor::visit(Return_Statement* ptr) {

    ptr->to_return->accept(this);
}

void ir_tree_visitor::visit(Method_invocation_Statement* ptr) {

    ptr->invocation->accept(this);
}





void ir_tree_visitor::visit(Declarations_with_variable* ptr) {

    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
}

void ir_tree_visitor::visit(Declarations_with_method* ptr) {

    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
}

void ir_tree_visitor::visit(Empty_Declarations* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(Method_declaration* ptr) {


    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);
    //name
}

void ir_tree_visitor::visit(Variable_declaration* ptr) {

    ptr->type->accept(this);
    //name
}

void ir_tree_visitor::visit(Empty_Method_args* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(Single_Method_args* ptr) {

    ptr->arg->accept(this);
}

void ir_tree_visitor::visit(Many_Method_args* ptr) {

    for(auto i : ptr->args) {
        i->accept(this);
    }
}

void ir_tree_visitor::visit(Method_arg* ptr) {

    ptr->type->accept(this);
    //name
}

void ir_tree_visitor::visit(Last_Method_multiple_arg* ptr) {

    ptr->arg->accept(this);
}

void ir_tree_visitor::visit(Many_Method_multiple_arg* ptr) {

    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void ir_tree_visitor::visit(Simple_Type* ptr) {

    //name
}

void ir_tree_visitor::visit(Array_Type* ptr) {

    //name
}

void ir_tree_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
}

void ir_tree_visitor::visit(Method_invocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
}

void ir_tree_visitor::visit(Field_invocation* ptr) {

    //name
}

void ir_tree_visitor::visit(Empty_Expressions* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(Single_Expressions* ptr) {

    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(Many_Expressions* ptr) {
    for(auto i: ptr->exprs) {
        i->accept(this);
    }
}

void ir_tree_visitor::visit(Single_Multiple_expressions* ptr) {

    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(Many_Multiple_expressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(Value_Expr* ptr) {

    ptr->value->accept(this);
}

void ir_tree_visitor::visit(Id_Expr* ptr) {

    //name
}

void ir_tree_visitor::visit(Array_el_Expr* ptr) {

    ptr->array->accept(this);
    ptr->index->accept(this);
}
void ir_tree_visitor::visit(Length_Expr* ptr) {

    ptr->array->accept(this);
}

void ir_tree_visitor::visit(Field_invocation_Expr* ptr) {

    ptr->invocation->accept(this);
}

void ir_tree_visitor::visit(New_arr_Expr* ptr) {

    ptr->count->accept(this);
    //type(str)
}

void ir_tree_visitor::visit(New_single_Expr* ptr) {

    //name
}

void ir_tree_visitor::visit(This_Expr* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(Not_Expr* ptr) {

    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(Method_invocation_Expr* ptr) {

    ptr->invocation->accept(this);
}

void ir_tree_visitor::visit(Plus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Minus_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Star_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Slash_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Percent_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(And_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Or_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Smaller_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Bigger_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Not_equal_Expr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void ir_tree_visitor::visit(Brackets_Expr* ptr) {

    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(Number_Value* ptr) {

    //value(int)
}

void ir_tree_visitor::visit(TF_Value* ptr) {

    //value(bool)
}

