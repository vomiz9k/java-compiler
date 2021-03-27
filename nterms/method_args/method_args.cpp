#include "method_args.hpp"

     
void Empty_Method_args::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Single_Method_args::Single_Method_args(Method_arg* arg) : arg(arg)
{

}   

void Single_Method_args::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Many_Method_args::Many_Method_args(Method_multiple_arg* prev_args, Method_arg* arg)
: arg(arg), prev_args(prev_args)
{

}  

void Many_Method_args::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Last_Method_multiple_arg::Last_Method_multiple_arg(Method_arg* arg): arg(arg)
{

}     

void Last_Method_multiple_arg::accept(Visitor* visitor)
{
    visitor->visit(this);
}


Many_Method_multiple_arg::Many_Method_multiple_arg(Method_multiple_arg* prev_args, Method_arg* arg)
    :prev_args(prev_args), arg(arg)
{

}
 

void Many_Method_multiple_arg::accept(Visitor* visitor)
{
    visitor->visit(this);
}


