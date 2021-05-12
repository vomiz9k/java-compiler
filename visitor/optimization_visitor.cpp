#include <big_include.hpp>
#include <visitor.hpp>
#include "optimization_visitor.hpp"



void optimization_visitor::visit(Program* ptr) {
    program = ptr;
    ptr->main_class->accept(this);
    ptr->class_declarations->accept(this);
}

void optimization_visitor::visit(MainClass* ptr) {

    ptr->body->accept(this);
    //class_name
}

void optimization_visitor::visit(NotEmptyClassDeclarations* ptr) {
    ptr->prev_class_decls->accept(this);
    ptr->class_decl->accept(this);
}

void optimization_visitor::visit(EmptyClassDeclarations* ptr) {
    
    //nochildren
}

void optimization_visitor::visit(ExtendedClassDeclaration* ptr) {
    program->declarations.push_back(ptr);

    curr_class = ptr;
    ptr->declarations->accept(this);
    
    //name, base
}

void optimization_visitor::visit(NotExtendedClassDeclaration* ptr) {
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

void optimization_visitor::visit(EmptyStatements* ptr) {
    in_empty = true;
    //nochildren
}

void optimization_visitor::visit(NotEmptyStatements* ptr) {
    ptr->prev_statements->accept(this);
    body->stmts.push_back(ptr->statement);
    ptr->statement->accept(this);
}

void optimization_visitor::visit(IfElseStatement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
}

void optimization_visitor::visit(IfStatement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}


void optimization_visitor::visit(AssertStatement* ptr) {

    ptr->check->accept(this);
}

void optimization_visitor::visit(VarDeclStatement* ptr) {

    ptr->decl->accept(this);
}

void optimization_visitor::visit(ScopeStatement* ptr) {

    ptr->body->accept(this);
}

void optimization_visitor::visit(WhileStatement* ptr) {

    ptr->condition->accept(this);
    ptr->do_if_true->accept(this);
}

void optimization_visitor::visit(PrintStatement* ptr) {

    ptr->to_print->accept(this);
}

void optimization_visitor::visit(AssignmentStatement* ptr) {

    ptr->assignment->accept(this);
}

void optimization_visitor::visit(ReturnStatement* ptr) {

    ptr->to_return->accept(this);
}

void optimization_visitor::visit(MethodInvocationStatement* ptr) {

    ptr->invocation->accept(this);
}



void optimization_visitor::visit(DeclarationsWithVariable* ptr) {
    ptr->prev_decls->accept(this);
    curr_class->decls.push_back(ptr->var_decl);
    ptr->var_decl->accept(this);
}

void optimization_visitor::visit(DeclarationsWithMethod* ptr) {
    ptr->prev_decls->accept(this);
    curr_class->decls.push_back(ptr->method_decl);
    ptr->method_decl->accept(this);
}

void optimization_visitor::visit(EmptyDeclarations* ptr) {
    //nochildren
}

void optimization_visitor::visit(MethodDeclaration* ptr) {

    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);
    //name
}

void optimization_visitor::visit(VariableDeclaration* ptr) {
    ptr->type->accept(this);
    //name
}

void optimization_visitor::visit(EmptyMethodArgs* ptr) {
    args = ptr;
    //nochildren
}

void optimization_visitor::visit(SingleMethodArg* ptr) {
    args = ptr;
    ptr->arg->accept(this);
}

void optimization_visitor::visit(MoreThanOneMethodArgs* ptr) {
    args = ptr;
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void optimization_visitor::visit(Method_arg* ptr) {
    args->args.push_back(ptr);
    ptr->type->accept(this);
    //name
}

void optimization_visitor::visit(LastMethodArg* ptr) {

    ptr->arg->accept(this);
}

void optimization_visitor::visit(NotLastMethodArgs* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void optimization_visitor::visit(SimpleType* ptr) {

    //name
}

void optimization_visitor::visit(ArrayType* ptr) {

    //name
}

void optimization_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
}


void optimization_visitor::visit(MethodInvocation* ptr) {

    ptr->from->accept(this);
    ptr->args->accept(this);
    //name
}

void optimization_visitor::visit(FieldInvocation* ptr) {

    //name
}

void optimization_visitor::visit(EmptyExpressions* ptr) {

    //nochildren
}

void optimization_visitor::visit(SingleExpression* ptr) {
    ptr->exprs.push_back(ptr->expr);
    ptr->expr->accept(this);
}

void optimization_visitor::visit(MoreThanOneExpression* ptr) {
    auto old_exprs = exprs;
    exprs = ptr;
    ptr->prev_exprs->accept(this);
    exprs->exprs.push_back(ptr->expr);                       
    ptr->expr->accept(this);
    exprs = old_exprs;
}

void optimization_visitor::visit(LastExpression* ptr) {
    exprs->exprs.push_back(ptr->expr);
    ptr->expr->accept(this);
}

void optimization_visitor::visit(NotLastExpressions* ptr) {

    ptr->prev_exprs->accept(this);
    exprs->exprs.push_back(ptr->expr);
    ptr->expr->accept(this);
}

void optimization_visitor::visit(ValueExpr* ptr) {

    ptr->value->accept(this);
}

void optimization_visitor::visit(IdExpr* ptr) {
    
    //name
}

void optimization_visitor::visit(ArrayElementExpr* ptr) {

    ptr->array->accept(this);
    ptr->index->accept(this);
}
void optimization_visitor::visit(LengthExpr* ptr) {

    ptr->array->accept(this);
}

void optimization_visitor::visit(FieldInvocationExpr* ptr) {

    ptr->invocation->accept(this);
}

void optimization_visitor::visit(NewArrayExpr* ptr) {

    ptr->count->accept(this);
    //type(str)
}

void optimization_visitor::visit(NewSingleExpr* ptr) {
    
    //name
}

void optimization_visitor::visit(ThisExpr* ptr) {

    //nochildren
}

void optimization_visitor::visit(NotExpr* ptr) {

    ptr->expr->accept(this);
}

void optimization_visitor::visit(MethodInvocationExpr* ptr) {
    
    ptr->invocation->accept(this);
}

void optimization_visitor::visit(PlusExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(MinusExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(MulExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(DivExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(PercentExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(AndExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(OrExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(SmallerExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(BiggerExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(EqualExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(NotEqualExpr* ptr) {

    ptr->first->accept(this);
    ptr->second->accept(this);
}

void optimization_visitor::visit(BracketsExpr* ptr) {

    ptr->expr->accept(this);
}

void optimization_visitor::visit(IntValue* ptr) {

    //value(int)
}

void optimization_visitor::visit(BoolValue* ptr) {

    //value(bool)
}