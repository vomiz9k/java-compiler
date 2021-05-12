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
    arrow(ptr, ptr->main_class);
    ptr->main_class->accept(this);
    for (auto i : ptr->declarations) {
        arrow(ptr, i);
        i->accept(this);
    }
    
    
    out << "}";
}

void gv_visitor::visit(MainClass* ptr) {
    box(ptr, "MainClass: " + *ptr->name);
    arrow(ptr, ptr->body);
    ptr->body->accept(this);
    //class_name
}

void gv_visitor::visit(NotEmptyClassDeclarations* ptr) {
    box(ptr, "NotEmptyClassDeclarations");
   
    arrow(ptr, ptr->prev_class_decls);
    ptr->prev_class_decls->accept(this);
     
    arrow(ptr, ptr->class_decl);
    ptr->class_decl->accept(this);
}

void gv_visitor::visit(EmptyClassDeclarations* ptr) {
    box(ptr, "Empty_Class_Declarations");
    //nochildren
}

void gv_visitor::visit(ExtendedClassDeclaration* ptr) {
    box(ptr, "Class Declaration: " + *ptr->name + ". Extended by " + *ptr->base);

    for(auto i : ptr->decls) {
        arrow(ptr, i);
        i->accept(this);
    }
    
    //name, base
}

void gv_visitor::visit(NotExtendedClassDeclaration* ptr) {
    box(ptr, "Class Decalration: " + *ptr->name);

    for(auto i : ptr->decls) {
        arrow(ptr, i);
        i->accept(this);
    }
    //name
}

void gv_visitor::visit(Body* ptr) {
    box(ptr, "body");
    for (auto i : ptr->stmts) {
        arrow(ptr, i);
        i->accept(this);
    }
    //nochildren
}

void gv_visitor::visit(EmptyStatements* ptr) {
    box(ptr, "Empty");
    //nochildren
}

void gv_visitor::visit(NotEmptyStatements* ptr) {
    box(ptr, "Not empty statements");
    arrow(ptr, ptr->prev_statements);
    ptr->prev_statements->accept(this);
    arrow(ptr, ptr->statement);
    ptr->statement->accept(this);
}

void gv_visitor::visit(IfElseStatement* ptr) {
    box(ptr, "if else statement");
    arrow(ptr, ptr->condition, "condition");
    ptr->condition->accept(this);
    arrow(ptr, ptr->do_if_true, "true");
    ptr->do_if_true->accept(this);
    arrow(ptr, ptr->do_else, "else");
    ptr->do_else->accept(this);
}

void gv_visitor::visit(IfStatement* ptr) {
    box(ptr, "if statement");
    arrow(ptr, ptr->condition, "condition");
    ptr->condition->accept(this);
    arrow(ptr, ptr->do_if_true, "true");
    ptr->do_if_true->accept(this);
}


void gv_visitor::visit(AssertStatement* ptr) {
    box(ptr, "assert");
    arrow(ptr, ptr->check);
    ptr->check->accept(this);
}

void gv_visitor::visit(VarDeclStatement* ptr) {
    box(ptr, "Var decl stmt");
    arrow(ptr, ptr->decl);
    ptr->decl->accept(this);
}

void gv_visitor::visit(ScopeStatement* ptr) {
    box(ptr, "new scope");
    arrow(ptr, ptr->body);
    ptr->body->accept(this);
}

void gv_visitor::visit(WhileStatement* ptr) {
    box(ptr, "while");
    arrow(ptr, ptr->condition, "condition");
    ptr->condition->accept(this);
    arrow(ptr, ptr->do_if_true, "true");
    ptr->do_if_true->accept(this);
}

void gv_visitor::visit(PrintStatement* ptr) {
    box(ptr, "print");
    arrow(ptr, ptr->to_print);
    ptr->to_print->accept(this);
}

void gv_visitor::visit(AssignmentStatement* ptr) {
    box(ptr, "assignment stmt");
    arrow(ptr, ptr->assignment);
    ptr->assignment->accept(this);
}

void gv_visitor::visit(ReturnStatement* ptr) {
    box(ptr, "return");
    arrow(ptr, ptr->to_return);
    ptr->to_return->accept(this);
}

void gv_visitor::visit(MethodInvocationStatement* ptr) {
    box(ptr, "method invoce stmt");
    arrow(ptr, ptr->invocation);
    ptr->invocation->accept(this);
}





void gv_visitor::visit(DeclarationsWithVariable* ptr) {
    box(ptr, "decl with variable");
    arrow(ptr, ptr->prev_decls, "decls");
    ptr->prev_decls->accept(this);
    arrow(ptr, ptr->var_decl, "var decl");
    ptr->var_decl->accept(this);
}

void gv_visitor::visit(DeclarationsWithMethod* ptr) {
    box(ptr, "decl with method");
    arrow(ptr, ptr->prev_decls, "decls");
    ptr->prev_decls->accept(this);
    arrow(ptr, ptr->method_decl, "method decl");
    ptr->method_decl->accept(this);
}

void gv_visitor::visit(EmptyDeclarations* ptr) {
    box(ptr, "empty");
    //nochildren
}

void gv_visitor::visit(MethodDeclaration* ptr) {
    box(ptr, "method decl: " + *ptr->name);
    arrow(ptr, ptr->type, "type");
    ptr->type->accept(this);
    arrow(ptr, ptr->args, "args");
    ptr->args->accept(this);
    arrow(ptr, ptr->body, "body");
    ptr->body->accept(this);
    //name
}

void gv_visitor::visit(VariableDeclaration* ptr) {
    box(ptr, "var decl: " + *ptr->name);
    arrow(ptr, ptr->type, "type");
    ptr->type->accept(this);
    //name
}

void gv_visitor::visit(EmptyMethodArgs* ptr) {
    box(ptr, "empty");
    //nochildren
}

void gv_visitor::visit(SingleMethodArg* ptr) {
    box(ptr, "single arg");
    arrow(ptr, ptr->arg);
    ptr->arg->accept(this);
}

void gv_visitor::visit(MoreThanOneMethodArgs* ptr) {
    box(ptr, "mnogo args");
    for(auto i : ptr->args) {
        arrow(ptr, i);
        i->accept(this);
    }
}

void gv_visitor::visit(Method_arg* ptr) {
    box(ptr, "arg: " + *ptr->name);
    arrow(ptr, ptr->type, "type");
    ptr->type->accept(this);
}

void gv_visitor::visit(LastMethodArg* ptr) {
    box(ptr, "first");
    arrow(ptr, ptr->arg);
    ptr->arg->accept(this);
}

void gv_visitor::visit(NotLastMethodArgs* ptr) {
    box(ptr, "mnogo args2");
    arrow(ptr, ptr->prev_args, "prev");
    ptr->prev_args->accept(this);
    arrow(ptr, ptr->arg, "mid");
    ptr->arg->accept(this);
}

void gv_visitor::visit(SimpleType* ptr) {
    box(ptr, "simple type: " + *ptr->name);
    //name
}

void gv_visitor::visit(ArrayType* ptr) {
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



void gv_visitor::visit(MethodInvocation* ptr) {
    box(ptr, "method invocation: " + *ptr->name);
    arrow(ptr, ptr->from, "caller");
    ptr->from->accept(this);
    arrow(ptr, ptr->args, "args");
    ptr->args->accept(this);
    //name
}

void gv_visitor::visit(FieldInvocation* ptr) {
    box(ptr, "field invoce: " + *ptr->name);
    //name
}

void gv_visitor::visit(EmptyExpressions* ptr) {
    box(ptr, "empty");
    //nochildren
}

void gv_visitor::visit(SingleExpression* ptr) {
    box(ptr, "single expr");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(MoreThanOneExpression* ptr) {
    box(ptr, "mnogo expr");
    for(auto i: ptr->exprs) {
        arrow(ptr, i);
        i->accept(this);
    }
}

void gv_visitor::visit(LastExpression* ptr) {
    box(ptr, "single expr 2");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(NotLastExpressions* ptr) {
    box(ptr, "mnogo expr2");
    arrow(ptr, ptr->prev_exprs, "prev");
    ptr->prev_exprs->accept(this);
    arrow(ptr, ptr->expr, "last");
    ptr->expr->accept(this);
}

void gv_visitor::visit(ValueExpr* ptr) {
    box(ptr, "Value expr");
    arrow(ptr, ptr->value);
    ptr->value->accept(this);
}

void gv_visitor::visit(IdExpr* ptr) {
    box(ptr, "id expr: " + *ptr->name);
    //name
}

void gv_visitor::visit(ArrayElementExpr* ptr) {
    box(ptr, "array el expr");
    arrow(ptr, ptr->array, "arr");
    ptr->array->accept(this);
    arrow(ptr, ptr->index, "index");
    ptr->index->accept(this);
}
void gv_visitor::visit(LengthExpr* ptr) {
    box(ptr, "Length of");
    arrow(ptr, ptr->array);
    ptr->array->accept(this);
}

void gv_visitor::visit(FieldInvocationExpr* ptr) {
    box(ptr, "field invoce expr");
    arrow(ptr, ptr->invocation);
    ptr->invocation->accept(this);
}

void gv_visitor::visit(NewArrayExpr* ptr) {
    box(ptr, "new " + *ptr->name + " []");
    arrow(ptr, ptr->count, "count");
    ptr->count->accept(this);
    //type(str)
}

void gv_visitor::visit(NewSingleExpr* ptr) {
    box(ptr, "new " + *ptr->name + " ()");
    //name
}

void gv_visitor::visit(ThisExpr* ptr) {
    box(ptr, "this");
    //nochildren
}

void gv_visitor::visit(NotExpr* ptr) {
    box(ptr, "Not(!)");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(MethodInvocationExpr* ptr) {
    box(ptr, "method invoce expr");
    arrow(ptr, ptr->invocation);
    ptr->invocation->accept(this);
}

void gv_visitor::visit(PlusExpr* ptr) {
    box(ptr, "+");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(MinusExpr* ptr) {
    box(ptr, "-");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(MulExpr* ptr) {
    box(ptr, "*");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(DivExpr* ptr) {
    box(ptr, "/");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(PercentExpr* ptr) {
    box(ptr, "%");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(AndExpr* ptr) {
    box(ptr, "&&");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(OrExpr* ptr) {
    box(ptr, "or");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(SmallerExpr* ptr) {
    box(ptr, "<");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(BiggerExpr* ptr) {
    box(ptr, ">");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(EqualExpr* ptr) {
    box(ptr, "==");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(NotEqualExpr* ptr) {
    box(ptr, "!=");
    arrow(ptr, ptr->first, "left");
    ptr->first->accept(this);
    arrow(ptr, ptr->second, "right");
    ptr->second->accept(this);
}

void gv_visitor::visit(BracketsExpr* ptr) {
    box(ptr, "into brackets");
    arrow(ptr, ptr->expr);
    ptr->expr->accept(this);
}

void gv_visitor::visit(IntValue* ptr) {
    std::stringstream stream;
    stream << "int: " << ptr->value;
    box(ptr, stream.str());
    //value(int)
}

void gv_visitor::visit(BoolValue* ptr) {
    std::stringstream stream;
    stream << "bool: " << ptr->value;
    box(ptr, stream.str());
    //value(bool)
}