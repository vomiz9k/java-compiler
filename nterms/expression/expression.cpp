#include "expression.hpp"

   

Value_Expr::Value_Expr(Value* value): value(value)
{

}

void Value_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}



Id_Expr::Id_Expr(std::string* name) : name(name)
{

}

void Id_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}



Array_el_Expr::Array_el_Expr(Expr* array, Expr* index)
    :array(array), index(index)
{

}

void Array_el_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}



Length_Expr::Length_Expr(Expr* array)
    :array(array)
{

}
void Length_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}



Field_invocation_Expr::Field_invocation_Expr(Field_invocation* invocation)
    :invocation(invocation)
{

}
void Field_invocation_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

New_arr_Expr::New_arr_Expr(std::string* type, Expr* count)
    :type(type), count(count)
{
    
}

void New_arr_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

New_single_Expr::New_single_Expr(std::string* name) : name(name)
{

}

void New_single_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


Not_Expr::Not_Expr(Expr* expr): expr(expr)
{

}

void Not_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


This_Expr::This_Expr()
{

}
void This_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


Method_invocation_Expr::Method_invocation_Expr(Method_invocation* invocation)
    :invocation(invocation)
{

}
void Method_invocation_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}



Plus_Expr::Plus_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{

}

void Plus_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


Minus_Expr::Minus_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Minus_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Star_Expr::Star_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Star_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Slash_Expr::Slash_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Slash_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Percent_Expr::Percent_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Percent_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

And_Expr::And_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void And_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Or_Expr::Or_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Or_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Smaller_Expr::Smaller_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Smaller_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Bigger_Expr::Bigger_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Bigger_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Equal_Expr::Equal_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Equal_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}

Not_equal_Expr::Not_equal_Expr(Expr* first, Expr* second)
    : first(first), second(second)
{
    
}

void Not_equal_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}



Brackets_Expr::Brackets_Expr(Expr* expr): expr(expr)
{
    
}
void Brackets_Expr::accept(Visitor* visitor) 
{
    visitor->visit(this);
}


