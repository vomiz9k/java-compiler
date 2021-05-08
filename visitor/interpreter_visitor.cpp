#include <big_include.hpp>
#include <visitor.hpp>
#include "interpreter_visitor.hpp"

void interpreter_visitor::visit(Program* ptr) {

    ptr->main_class->accept(this);
    //ptr->class_declarations->accept(this);
}

void interpreter_visitor::visit(MainClass* ptr) {

    ptr->body->accept(this);
    //class_name
}


void interpreter_visitor::visit(Body* ptr) {
    for (auto i: ptr->stmts) {
        i->accept(this);
    }
    //nochildren
}

void interpreter_visitor::visit(IfElseStatement* ptr) {

    ptr->condition->accept(this);
    if(result)
        ptr->do_if_true->accept(this);
    else
        ptr->do_else->accept(this);
}

void interpreter_visitor::visit(IfStatement* ptr) {
    ptr->condition->accept(this);
    if (result)
        ptr->do_if_true->accept(this);
}


void interpreter_visitor::visit(AssertStatement* ptr) {
    ptr->check->accept(this);
    if (!result)
        throw "ASSERTATION";
}

void interpreter_visitor::visit(VarDeclStatement* ptr) {
    ptr->decl->accept(this);
}

void interpreter_visitor::visit(ScopeStatement* ptr) {
    ptr->body->accept(this);
}

void interpreter_visitor::visit(WhileStatement* ptr) {
    ptr->condition->accept(this);
    while(result) {
        ptr->do_if_true->accept(this);
        ptr->condition->accept(this);
    }
}

void interpreter_visitor::visit(PrintStatement* ptr) {

    ptr->to_print->accept(this);
    std::cout << "print: " << result << '\n';
}

void interpreter_visitor::visit(FieldInvocation* ptr) {
    
}

void interpreter_visitor::visit(AssignmentStatement* ptr) {
    ptr->assignment->accept(this);
}



void interpreter_visitor::visit(VariableDeclaration* ptr) {
    ptr->type->accept(this);
    if(!is_array)
        var[*ptr->name];
    else
        array[*ptr->name];
    
    //name
}


void interpreter_visitor::visit(SimpleType* ptr) {
    if (*ptr->name != "int" && *ptr->name != "bool")   
        throw "ploxo";
    is_array = false;
    //name
}

void interpreter_visitor::visit(ArrayType* ptr) {
    if (*ptr->name != "int" && *ptr->name != "bool")   
        throw "ploxo";
    is_array = true;
    //name
}

void interpreter_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    if (lvalue == nullptr)
        throw std::string("bad lvalue");
    auto val_ptr = lvalue;
    ptr->rvalue->accept(this);
    *val_ptr = result;
}


void interpreter_visitor::visit(ValueExpr* ptr) {
    ptr->value->accept(this);
}

void interpreter_visitor::visit(IdExpr* ptr) {
    result = var[*ptr->name];
}

void interpreter_visitor::visit(NewArrayExpr* ptr) {

}


void interpreter_visitor::visit(NotExpr* ptr) {

    ptr->expr->accept(this);
    result = !result;
}


void interpreter_visitor::visit(PlusExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first + result);
}

void interpreter_visitor::visit(MinusExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first - result);
}

void interpreter_visitor::visit(MulExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first * result);
}

void interpreter_visitor::visit(DivExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first / result);
}

void interpreter_visitor::visit(PercentExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first % result);
}

void interpreter_visitor::visit(AndExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first && result);
}

void interpreter_visitor::visit(OrExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first || result);
}

void interpreter_visitor::visit(SmallerExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first < result);
}

void interpreter_visitor::visit(BiggerExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first > result);
}

void interpreter_visitor::visit(EqualExpr* ptr) {

    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first == result);
}

void interpreter_visitor::visit(NotEqualExpr* ptr) {
    ptr->first->accept(this);
    auto first = result;
    ptr->second->accept(this);
    result = (first != result);
}

void interpreter_visitor::visit(BracketsExpr* ptr) {

    ptr->expr->accept(this);
}

void interpreter_visitor::visit(IntValue* ptr) {
    result = ptr->value;
    //value(int)
}

void interpreter_visitor::visit(BoolValue* ptr) {
    result = ptr->value;
    //value(bool)
}