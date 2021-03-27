#include "class_declarations.hpp"

Empty_Class_declarations::Empty_Class_declarations()
{

}
    
void Empty_Class_declarations::accept(Visitor* visitor)
{
    visitor->visit(this);
}



Not_empty_Class_declarations::Not_empty_Class_declarations(Class_declarations* prev_class_decls, Class_declaration* class_decl)
    :prev_class_decls(prev_class_decls), class_decl(class_decl)
{

}

void  Not_empty_Class_declarations::accept(Visitor* visitor)
{
    visitor->visit(this);
}
