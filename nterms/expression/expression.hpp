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
class Value_Expr: public Expr
{
    #include <friends_visitors>
    Value* value;
public:
    Value_Expr(Value* value);
    void accept(Visitor* visitor) override;
};

class Id_Expr: public Expr
{
    #include <friends_visitors>
    std::string* name;
public:
    Id_Expr(std::string* name);
    void accept(Visitor* visitor) override;
};

class Array_el_Expr: public Expr
{
    #include <friends_visitors>
    Expr* array;
    Expr* index;
public:
    Array_el_Expr(Expr* array, Expr* index);
    void accept(Visitor* visitor) override;
};

class Length_Expr: public Expr
{
    #include <friends_visitors>
    Expr* array;
public:
    Length_Expr(Expr* array);
    void accept(Visitor* visitor) override;
};

class Field_invocation;
class Field_invocation_Expr: public Expr
{
    #include <friends_visitors>
    Field_invocation* invocation;
public:
    Field_invocation_Expr(Field_invocation* invocation);
    void accept(Visitor* visitor) override;
};

class New_arr_Expr: public Expr
{
    #include <friends_visitors>
    std::string* name;
    Expr* count;

public:
    New_arr_Expr(std::string* name, Expr* count);
    void accept(Visitor* visitor) override;
};

class New_single_Expr: public Expr
{
    #include <friends_visitors>
    std::string* name;

public:
    New_single_Expr(std::string* name);
    void accept(Visitor* visitor) override;
};


class Not_Expr: public Expr
{
    #include <friends_visitors>
    Expr* expr;
public:
    Not_Expr(Expr* expr);
    void accept(Visitor* visitor) override;
};

class This_Expr: public Expr
{
    #include <friends_visitors>
public:
    This_Expr();
    void accept(Visitor* visitor) override;
};

class Method_invocation;
class Method_invocation_Expr: public Expr
{
    #include <friends_visitors>
    Method_invocation* invocation;
public:
    Method_invocation_Expr(Method_invocation* invocation);
    void accept(Visitor* visitor) override;
};

class Plus_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Plus_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Minus_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Minus_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Star_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Star_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Slash_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Slash_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Percent_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Percent_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class And_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    And_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Or_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Or_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Smaller_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Smaller_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Bigger_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Bigger_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Equal_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Equal_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};

class Not_equal_Expr: public Expr
{   
    #include <friends_visitors>
    Expr* first;
    Expr* second;
public:
    Not_equal_Expr(Expr* first, Expr* second);

    void accept(Visitor* visitor) override;
};


class Brackets_Expr:public Expr
{
    #include <friends_visitors>
    Expr* expr;
public:
    Brackets_Expr(Expr* expr);
    void accept(Visitor* visitor) override;
};


