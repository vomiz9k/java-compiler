#include "method_args.hpp"
#include <visitor.hpp>
     
void EmptyMethodArgs::accept(Visitor* visitor)
{
    visitor->visit(this);
}


SingleMethodArg::SingleMethodArg(Method_arg* arg) : arg(arg)
{

}   

void SingleMethodArg::accept(Visitor* visitor)
{
    visitor->visit(this);
}


MoreThanOneMethodArgs::MoreThanOneMethodArgs(Method_multiple_arg* prev_args, Method_arg* arg)
: arg(arg), prev_args(prev_args)
{

}  

void MoreThanOneMethodArgs::accept(Visitor* visitor)
{
    visitor->visit(this);
}


LastMethodArg::LastMethodArg(Method_arg* arg): arg(arg)
{

}     

void LastMethodArg::accept(Visitor* visitor)
{
    visitor->visit(this);
}


NotLastMethodArgs::NotLastMethodArgs(Method_multiple_arg* prev_args, Method_arg* arg)
    :prev_args(prev_args), arg(arg)
{

}
 

void NotLastMethodArgs::accept(Visitor* visitor)
{
    visitor->visit(this);
}


