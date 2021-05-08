#include "method_invocation.hpp"
#include <visitor.hpp>

MethodInvocation::MethodInvocation(Expr* from, std::string* name, Expressions* args)
    :from(from), name(name), args(args)
{

}

void MethodInvocation::accept(Visitor* visitor)
{
    visitor->visit(this);
}