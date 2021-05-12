#pragma once

#include <base.hpp>
#include <string>
class Type;

class Expr: public Base
{
    #include <friends_visitors>
    virtual void accept(Visitor* visitor) = 0;

public:
    bool is_lvalue = false;
    Type* type;
};

class Value;    
class ValueExpr: public Expr
{
    #include <friends_visitors>
    Value* value;
public:
    ValueExpr(Value* value);
    void accept(Visitor* visitor) override;
};

class IdExpr: public Expr
{
    #include <friends_visitors>
    std::string* name;
public:
    IdExpr(std::string* name);
    void accept(Visitor* visitor) override;
};

class ArrayElementExpr: public Expr
{
    #include <friends_visitors>
    Expr* array;
    Expr* index;
public:
    ArrayElementExpr(Expr* array, Expr* index);
    void accept(Visitor* visitor) override;
};

class LengthExpr: public Expr
{
    #include <friends_visitors>
    Expr* array;
public:
    LengthExpr(Expr* array);
    void accept(Visitor* visitor) override;
};

class FieldInvocation;
class FieldInvocationExpr: public Expr
{
    #include <friends_visitors>
    FieldInvocation* invocation;
public:
    FieldInvocationExpr(FieldInvocation* invocation);
    void accept(Visitor* visitor) override;
};

class NewArrayExpr: public Expr
{
    #include <friends_visitors>
    std::string* name;
    Expr* count;

public:
    NewArrayExpr(std::string* name, Expr* count);
    void accept(Visitor* visitor) override;
};

class NewSingleExpr: public Expr
{
    #include <friends_visitors>
    std::string* name;

public:
    NewSingleExpr(std::string* name);
    void accept(Visitor* visitor) override;
};


class NotExpr: public Expr
{
    #include <friends_visitors>
    Expr* expr;
public:
    NotExpr(Expr* expr);
    void accept(Visitor* visitor) override;
};

class ThisExpr: public Expr
{
    #include <friends_visitors>
public:
    ThisExpr();
    void accept(Visitor* visitor) override;
};

class MethodInvocation;
class MethodInvocationExpr: public Expr
{
    #include <friends_visitors>
    MethodInvocation* invocation;
public:
    MethodInvocationExpr(MethodInvocation* invocation);
    void accept(Visitor* visitor) override;
};

class PlusExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    PlusExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class MinusExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    MinusExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class MulExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    MulExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class DivExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    DivExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class PercentExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    PercentExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class AndExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    AndExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class OrExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    OrExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class SmallerExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    SmallerExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class BiggerExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    BiggerExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class EqualExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    EqualExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class NotEqualExpr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    NotEqualExpr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};


class BracketsExpr: public Expr
{
    #include <friends_visitors>
    Expr* expr;
public:
    BracketsExpr(Expr* expr);
    void accept(Visitor* visitor) override;
};


