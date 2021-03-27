#pragma once

#include <string>
#include <base.hpp>
#include <vector>

class Method_arg;

class Method_args: public Base
{    
    std::vector <Method_arg*> args;
    #include <friends_visitors>
public:    
    virtual void accept(Visitor* visitor) = 0;
};

class Empty_Method_args: public Method_args
{ 
    #include <friends_visitors>
public:       
    void accept(Visitor* visitor) override;
};

class Single_Method_args: public Method_args
{   
    #include <friends_visitors>
    Method_arg* arg;
public:
    Single_Method_args(Method_arg* arg);     
    void accept(Visitor* visitor) override;
};

class Method_multiple_arg;
class Many_Method_args: public Method_args
{
    #include <friends_visitors>
    Method_arg* arg;
    Method_multiple_arg* prev_args;
public:
    Many_Method_args(Method_multiple_arg* prev_args, Method_arg* arg);     
    void accept(Visitor* visitor) override;
};

class Method_multiple_arg: public Base //other rule same smysel
{   
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class Last_Method_multiple_arg : public Method_multiple_arg
{
    #include <friends_visitors>
    Method_arg* arg;
public:
    Last_Method_multiple_arg(Method_arg* arg);     
    void accept(Visitor* visitor) override;
};

class Many_Method_multiple_arg : public Method_multiple_arg
{
    #include <friends_visitors>
    Method_arg* arg;
    Method_multiple_arg* prev_args;
public:
    Many_Method_multiple_arg(Method_multiple_arg* prev_args, Method_arg* arg);     
    void accept(Visitor* visitor) override;
};



