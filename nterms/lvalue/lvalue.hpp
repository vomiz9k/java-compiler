#pragma once

#include <string>
#include <base.hpp>

class Expr;
class Type;

class Lvalue: public Base
{
    #include <friends_visitors>
        
public:
    Type* type;
    virtual void accept(Visitor* visitor) = 0;
};

class Single_Lvalue: public Lvalue {
    #include <friends_visitors>
    std::string* name;

public:
    void accept(Visitor* visitor);
    Single_Lvalue(std::string* name);
};

class Arr_el_Lvalue: public Lvalue {
    #include <friends_visitors>
    std::string* name;
    Expr* index;

public:
    void accept(Visitor* visitor);
    Arr_el_Lvalue(std::string* name, Expr* index);
};

class Field_invocation;

class Field_Lvalue: public Lvalue {
    #include <friends_visitors>
    Field_invocation* invocation;

public:
    void accept(Visitor* visitor);
    Field_Lvalue(Field_invocation* invocation);
};

class Field_arr_el_Lvalue: public Lvalue {
    #include <friends_visitors>
    Field_invocation* invocation;
    Expr* index;
public:
    void accept(Visitor* visitor);
    Field_arr_el_Lvalue(Field_invocation* invocation, Expr* index);
};

