#pragma once

//#include <big_include.hpp>
#include <iostream>

class Program;
class MainClass;

class Body;
class EmptyStatements;
class NotEmptyStatements;

class Statement;
class IfElseStatement;
class IfStatement;
class AssertStatement;
class VarDeclStatement;
class ScopeStatement;
class WhileStatement;
class PrintStatement;
class AssignmentStatement;
class ReturnStatement;
class MethodInvocationStatement;


class NotEmptyClassDeclarations;
class EmptyClassDeclarations;


class Class_declaration;
class ExtendedClassDeclaration;
class NotExtendedClassDeclaration;


class Declarations;
class DeclarationsWithVariable;
class DeclarationsWithMethod;
class EmptyDeclarations;

class MethodDeclaration;
class VariableDeclaration;

class Method_args;
class EmptyMethodArgs;
class SingleMethodArg;
class MoreThanOneMethodArgs;
class Method_arg;
class LastMethodArg;
class NotLastMethodArgs;

class SimpleType;
class ArrayType;

class Assignment;

class Single_Lvalue;
class Arr_el_Lvalue;
class Field_Lvalue;
class Field_arr_el_Lvalue;

class MethodInvocation;
class FieldInvocation;

class EmptyExpressions;
class SingleExpression;
class MoreThanOneExpression;
class LastExpression;
class NotLastExpressions;

class ValueExpr;
class IdExpr;
class ArrayElementExpr;
class LengthExpr;


class NewArrayExpr;
class NewSingleExpr;
class FieldInvocationExpr;
class ThisExpr;
class NotExpr;
class MethodInvocationExpr;
class PlusExpr;
class MinusExpr;
class MulExpr;
class DivExpr;
class PercentExpr;
class AndExpr;
class OrExpr;
class SmallerExpr;
class BiggerExpr;
class EqualExpr;
class NotEqualExpr;
class BracketsExpr;

class IntValue;
class BoolValue;

class Visitor
{

public:
    virtual void visit(Program*) = 0; //program
    virtual void visit(MainClass*) = 0;

    virtual void visit(NotEmptyClassDeclarations*) = 0;
    virtual void visit(EmptyClassDeclarations*) = 0;

    virtual void visit(Body*) = 0;
    virtual void visit(EmptyStatements*) = 0;
    virtual void visit(NotEmptyStatements*) = 0;

    virtual void visit(IfElseStatement*) = 0;
    virtual void visit(IfStatement*) = 0;
    virtual void visit(AssertStatement*) = 0;
    virtual void visit(VarDeclStatement*) = 0;
    virtual void visit(ScopeStatement*) = 0;
    virtual void visit(WhileStatement*) = 0;
    virtual void visit(PrintStatement*) = 0;
    virtual void visit(AssignmentStatement*) = 0;
    virtual void visit(ReturnStatement*) = 0;
    virtual void visit(MethodInvocationStatement*) = 0;


    virtual void visit(ExtendedClassDeclaration*) = 0;
    virtual void visit(NotExtendedClassDeclaration*) = 0;


    virtual void visit(DeclarationsWithVariable*) = 0;
    virtual void visit(DeclarationsWithMethod*) = 0;
    virtual void visit(EmptyDeclarations*) = 0;

    virtual void visit(MethodDeclaration*) = 0;
    virtual void visit(VariableDeclaration*) = 0;

    virtual void visit(EmptyMethodArgs*) = 0;
    virtual void visit(SingleMethodArg*) = 0;
    virtual void visit(MoreThanOneMethodArgs*) = 0;
    virtual void visit(Method_arg*) = 0;
    virtual void visit(LastMethodArg*) = 0;
    virtual void visit(NotLastMethodArgs*) = 0;

    virtual void visit(SimpleType*) = 0;
    virtual void visit(ArrayType*) = 0;

    virtual void visit(Assignment*) = 0;

    virtual void visit(MethodInvocation*) = 0;
    virtual void visit(FieldInvocation*) = 0;

    virtual void visit(EmptyExpressions*) = 0;
    virtual void visit(SingleExpression*) = 0;
    virtual void visit(MoreThanOneExpression*) = 0;
    virtual void visit(LastExpression*) = 0;
    virtual void visit(NotLastExpressions*) = 0;

    virtual void visit(ValueExpr*) = 0;
    virtual void visit(IdExpr*) = 0;
    virtual void visit(ArrayElementExpr*) = 0;
    virtual void visit(LengthExpr*) = 0;

    virtual void visit(FieldInvocationExpr*) = 0;

    virtual void visit(NewArrayExpr*) = 0;
    virtual void visit(NewSingleExpr*) = 0;
    virtual void visit(ThisExpr*) = 0;

    virtual void visit(NotExpr*) = 0;
    virtual void visit(MethodInvocationExpr*) = 0;
    virtual void visit(PlusExpr*) = 0;
    virtual void visit(MinusExpr*) = 0;
    virtual void visit(MulExpr*) = 0;
    virtual void visit(DivExpr*) = 0;
    virtual void visit(PercentExpr*) = 0;
    virtual void visit(AndExpr*) = 0;
    virtual void visit(OrExpr*) = 0;
    virtual void visit(SmallerExpr*) = 0;
    virtual void visit(BiggerExpr*) = 0;
    virtual void visit(EqualExpr*) = 0;
    virtual void visit(NotEqualExpr*) = 0;
    virtual void visit(BracketsExpr*) = 0;

    virtual void visit(IntValue*) = 0;
    virtual void visit(BoolValue*) = 0;
};


#include "template_visitor.hpp" //template for other visitors

#include "delete_visitor.hpp"
#include "gv_visitor.hpp"
#include "optimization_visitor.hpp"
#include "interpreter_visitor.hpp"
#include "symbol_table_visitor.hpp"
#include "ir_tree_visitor.hpp"











