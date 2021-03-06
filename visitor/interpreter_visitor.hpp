#pragma once
#include "visitor.hpp"
#include <variant>
#include <string>
#include <vector>
#include <map>


class interpreter_visitor: public Visitor
{
    std::map<std::string, int> var;
    //int result;
    std::map<std::string, std::vector<int>> array;
    int result;
    int* lvalue;

    bool is_array = false;

public:
    void visit(Program*) override;
    void visit(MainClass*) override;

    void visit(NotEmptyClassDeclarations*) override {};
    void visit(EmptyClassDeclarations*) override {};
    
    void visit(Body*) override;
    void visit(EmptyStatements*) override {};
    void visit(NotEmptyStatements*) override {};

    void visit(IfElseStatement*) override;
    void visit(IfStatement*) override;
    void visit(AssertStatement*) override;
    void visit(VarDeclStatement*) override;
    void visit(ScopeStatement*) override;
    void visit(WhileStatement*) override;
    void visit(PrintStatement*) override;
    void visit(AssignmentStatement*) override;
    void visit(ReturnStatement*) override {};
    void visit(MethodInvocationStatement*) override {};

    void visit(ExtendedClassDeclaration*) override {};
    void visit(NotExtendedClassDeclaration*) override {};
    

    void visit(DeclarationsWithVariable*) override {};
    void visit(DeclarationsWithMethod*) override {};
    void visit(EmptyDeclarations*) override {};

    void visit(MethodDeclaration*) override {};
    void visit(VariableDeclaration*) override;
    
    void visit(EmptyMethodArgs*) override {};
    void visit(SingleMethodArg*) override {};
    void visit(MoreThanOneMethodArgs*) override {};
    void visit(Method_arg*) override {};
    void visit(LastMethodArg*) override {};
    void visit(NotLastMethodArgs*) override {};

    void visit(SimpleType*) override;
    void visit(ArrayType*) override;

    void visit(Assignment*) override;
    void visit(MethodInvocation*) override {};
    void visit(FieldInvocation*) override;

    void visit(EmptyExpressions*) override {};
    void visit(SingleExpression*) override {};
    void visit(MoreThanOneExpression*) override {};
    void visit(LastExpression*) override {};
    void visit(NotLastExpressions*) override {};

    void visit(ValueExpr*) override;
    void visit(IdExpr*) override;
    void visit(ArrayElementExpr*) override {};
    void visit(LengthExpr*) override {};

    void visit(FieldInvocationExpr*) override {};

    void visit(NewArrayExpr*) override;
    void visit(NewSingleExpr*) override {};
    void visit(ThisExpr*) override {};

    void visit(NotExpr*) override;
    void visit(MethodInvocationExpr*) override {};
    void visit(PlusExpr*) override;
    void visit(MinusExpr*) override;
    void visit(MulExpr*) override;
    void visit(DivExpr*) override;
    void visit(PercentExpr*) override;
    void visit(AndExpr*) override;
    void visit(OrExpr*) override;
    void visit(SmallerExpr*) override;
    void visit(BiggerExpr*) override;
    void visit(EqualExpr*) override;
    void visit(NotEqualExpr*) override;
    void visit(BracketsExpr*) override;

    void visit(IntValue*) override;
    void visit(BoolValue*) override;
};