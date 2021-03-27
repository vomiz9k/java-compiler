#include "statements.hpp"

Empty_Statements::Empty_Statements()
{

}

void Empty_Statements::accept(Visitor* visitor)
{
    visitor->visit(this);
}

Not_empty_Statements::Not_empty_Statements(Statements* prev_statements, Statement* statement)
    : prev_statements(prev_statements), statement(statement)
{

}

void Not_empty_Statements::accept(Visitor* visitor)
{
    visitor->visit(this);
}