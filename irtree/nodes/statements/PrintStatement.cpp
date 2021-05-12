#include "PrintStatement.h"
#include "../expressions/Expression.h"

namespace IRT {

void PrintStatement::Accept(Visitor *visitor) {
    visitor->Visit(this);
}

PrintStatement::PrintStatement(IRT::Expression *expression) : expression_(expression) {
}

}
