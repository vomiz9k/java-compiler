#include "method_arg.hpp"
#include <visitor.hpp>


Method_arg::Method_arg(Type* type, std::string* name)
    :type(type), name(name)
{

}

void Method_arg::accept(Visitor* visitor)
{
    visitor->visit(this);
}
