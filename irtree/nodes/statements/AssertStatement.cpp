#include "AssertStatement.h"
#include "../expressions/Expression.h"

namespace IRT {

    void AssertStatement::Accept(Visitor *visitor) {
        visitor->Visit(this);
    }

    AssertStatement::AssertStatement(IRT::Expression *expression) : expression_(expression) {
    }

}
