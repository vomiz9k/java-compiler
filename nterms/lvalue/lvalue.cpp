#include <string>
#include "lvalue.hpp"

void Single_Lvalue::accept(Visitor* visitor) {
    visitor->visit(this);
}

Single_Lvalue::Single_Lvalue(std::string* name) : name(name) {

}


void Arr_el_Lvalue::accept(Visitor* visitor) {
    visitor->visit(this);
}

Arr_el_Lvalue::Arr_el_Lvalue(std::string* name, Expr* index) : name(name), index(index) {

}

void Field_Lvalue::accept(Visitor* visitor) {
    visitor->visit(this);
}

Field_Lvalue::Field_Lvalue(Field_invocation* invocation) : invocation(invocation) {

}


void Field_arr_el_Lvalue::accept (Visitor* visitor) {
    visitor->visit(this);
}

Field_arr_el_Lvalue::Field_arr_el_Lvalue(Field_invocation* invocation, Expr* index)
    : invocation(invocation) , index(index) {

}

