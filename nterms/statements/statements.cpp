#include "statements.hpp"
#include <visitor.hpp>

EmptyStatements::EmptyStatements()
{

}

void EmptyStatements::accept(Visitor* visitor)
{
    visitor->visit(this);
}

NotEmptyStatements::NotEmptyStatements(Statements* prev_statements, Statement* statement)
    : prev_statements(prev_statements), statement(statement)
{

}

void NotEmptyStatements::accept(Visitor* visitor)
{
    visitor->visit(this);
}