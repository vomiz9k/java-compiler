#include "class_declaration.hpp"
#include <visitor.hpp>
#include <base_scope.hpp>

 void Class_declaration::SetScope(BaseScope* value){
     scope = value;
 }

ExtendedClassDeclaration::ExtendedClassDeclaration(std::string* namee, std::string* base, Declarations* declarationss)
    :  base(base)
{
    declarations = declarationss;
    name = namee;
}

void ExtendedClassDeclaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}


NotExtendedClassDeclaration::NotExtendedClassDeclaration(std::string* namee, Declarations* declarationss)
{
    declarations = declarationss;
    name = namee;
}

void NotExtendedClassDeclaration::accept(Visitor* visitor)
{
    visitor->visit(this);
}