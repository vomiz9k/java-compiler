#include "class_declarations.hpp"
#include <visitor.hpp>

EmptyClassDeclarations::EmptyClassDeclarations()
{

}
    
void EmptyClassDeclarations::accept(Visitor* visitor)
{
    visitor->visit(this);
}



NotEmptyClassDeclarations::NotEmptyClassDeclarations(Class_declarations* prev_class_decls, Class_declaration* class_decl)
    :prev_class_decls(prev_class_decls), class_decl(class_decl)
{

}

void  NotEmptyClassDeclarations::accept(Visitor* visitor)
{
    visitor->visit(this);
}
