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

class EmptyMethodArgs: public Method_args
{ 
    #include <friends_visitors>
public:       
    void accept(Visitor* visitor) override;
};

class SingleMethodArg: public Method_args
{   
    #include <friends_visitors>
    Method_arg* arg;
public:
    SingleMethodArg(Method_arg* arg);
    void accept(Visitor* visitor) override;
};

class Method_multiple_arg;
class MoreThanOneMethodArgs: public Method_args
{
    #include <friends_visitors>
    Method_arg* arg;
    Method_multiple_arg* prev_args;
public:
    MoreThanOneMethodArgs(Method_multiple_arg* prev_args, Method_arg* arg);
    void accept(Visitor* visitor) override;
};

class Method_multiple_arg: public Base //other rule same smysel
{   
    #include <friends_visitors>
public:
    virtual void accept(Visitor* visitor) = 0;
};

class LastMethodArg : public Method_multiple_arg
{
    #include <friends_visitors>
    Method_arg* arg;
public:
    LastMethodArg(Method_arg* arg);
    void accept(Visitor* visitor) override;
};

class NotLastMethodArgs : public Method_multiple_arg
{
    #include <friends_visitors>
    Method_multiple_arg* prev_args;
    Method_arg* arg;

public:
    NotLastMethodArgs(Method_multiple_arg* prev_args, Method_arg* arg);
    void accept(Visitor* visitor) override;
};



