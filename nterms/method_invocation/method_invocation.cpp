#include "method_invocation.hpp"

Method_invocation::Method_invocation(Expr* from, std::string* name, Expressions* args)
    :from(from), name(name), args(args)
{

}

void Method_invocation::accept(Visitor* visitor)
{
    visitor->visit(this);
}