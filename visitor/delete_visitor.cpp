#include <big_include.hpp>
#include <visitor.hpp>
#include "delete_visitor.hpp"

void delete_visitor::visit(Program* ptr) {

    ptr->main_class->accept(this);
    ptr->class_declarations->accept(this);
    delete ptr;
}

void delete_visitor::visit(MainClass* ptr) {

    ptr->body->accept(this);
    
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(NotEmptyClassDeclarations* ptr) {
    
    ptr->class_decl->accept(this);
    ptr->prev_class_decls->accept(this);
    delete ptr;
}

void delete_visitor::visit(EmptyClassDeclarations* ptr) {
    
    //nochildren
    delete ptr;
}

void delete_visitor::visit(ExtendedClassDeclaration* ptr) {

    ptr->declarations->accept(this);
    
    //name, base
    delete ptr->name;
    delete ptr->base;
    delete ptr;
}

void delete_visitor::visit(NotExtendedClassDeclaration* ptr) {

    ptr->declarations->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Body* ptr) {
    
    ptr->statements->accept(this);
    delete ptr;
}


void delete_visitor::visit(EmptyStatements* ptr) {
    
    //nochildren
    delete ptr;
}

void delete_visitor::visit(NotEmptyStatements* ptr) {

    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
    delete ptr;
}

void delete_visitor::visit(IfElseStatement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
    delete ptr;
}

void delete_visitor::visit(IfStatement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    delete ptr;
}


void delete_visitor::visit(AssertStatement* ptr) {

    ptr->check->accept(this);
    delete ptr;
}

void delete_visitor::visit(VarDeclStatement* ptr) {

    ptr->decl->accept(this);
    delete ptr;
}

void delete_visitor::visit(ScopeStatement* ptr) {

    ptr->body->accept(this);
    delete ptr;
}

void delete_visitor::visit(WhileStatement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    delete ptr;
}

void delete_visitor::visit(PrintStatement* ptr) {

    ptr->to_print->accept(this);
    delete ptr;
}

void delete_visitor::visit(AssignmentStatement* ptr) {

    ptr->assignment->accept(this);
    delete ptr;
}

void delete_visitor::visit(ReturnStatement* ptr) {

    ptr->to_return->accept(this);
    delete ptr;
}

void delete_visitor::visit(MethodInvocationStatement* ptr) {

    ptr->invocation->accept(this);
    delete ptr;
}





void delete_visitor::visit(DeclarationsWithVariable* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
    delete ptr;
}

void delete_visitor::visit(DeclarationsWithMethod* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
    delete ptr;
}

void delete_visitor::visit(EmptyDeclarations* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(MethodDeclaration* ptr) {


    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(VariableDeclaration* ptr) {

    ptr->type->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(EmptyMethodArgs* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(SingleMethodArg* ptr) {

    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(MoreThanOneMethodArgs* ptr) {

    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(Method_arg* ptr) {

    ptr->type->accept(this);
    delete ptr;
}

void delete_visitor::visit(LastMethodArg* ptr) {

    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(NotLastMethodArgs* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
    delete ptr;
}

void delete_visitor::visit(SimpleType* ptr) {

    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(ArrayType* ptr) {

    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
    delete ptr;
}


void delete_visitor::visit(MethodInvocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(FieldInvocation* ptr) {

    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(EmptyExpressions* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(SingleExpression* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(MoreThanOneExpression* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(LastExpression* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(NotLastExpressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(ValueExpr* ptr) {

    ptr->value->accept(this);
    delete ptr;
}

void delete_visitor::visit(IdExpr* ptr) {
    
    //name
    delete ptr;
}

void delete_visitor::visit(ArrayElementExpr* ptr) {

    ptr->array->accept(this);
    ptr->index->accept(this);
    delete ptr;
}
void delete_visitor::visit(LengthExpr* ptr) {

    ptr->array->accept(this);
    delete ptr;
}

void delete_visitor::visit(FieldInvocationExpr* ptr) {

    ptr->invocation->accept(this);
    delete ptr;
}

void delete_visitor::visit(NewArrayExpr* ptr) {


    ptr->count->accept(this);
    //type
    delete ptr->type;
    delete ptr;
}

void delete_visitor::visit(NewSingleExpr* ptr) {
    
    //name
    delete ptr->name;
    delete ptr;
}

void delete_visitor::visit(ThisExpr* ptr) {

    //nochildren
    delete ptr;
}

void delete_visitor::visit(NotExpr* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(MethodInvocationExpr* ptr) {
    
    ptr->invocation->accept(this);
    delete ptr;
}

void delete_visitor::visit(PlusExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(MinusExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(MulExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(DivExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(PercentExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(AndExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(OrExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(SmallerExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(BiggerExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(EqualExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(NotEqualExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
    delete ptr;
}

void delete_visitor::visit(BracketsExpr* ptr) {

    ptr->expr->accept(this);
    delete ptr;
}

void delete_visitor::visit(IntValue* ptr) {

    //value(int)
    delete ptr;
}

void delete_visitor::visit(BoolValue* ptr) {

    //value(bool)
    delete ptr;
}