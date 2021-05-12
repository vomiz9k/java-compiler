#include "MallocExpression.h"


namespace IRT {

void MallocExpression::Accept(Visitor *visitor) {
    visitor->Visit(this);
}

MallocExpression::MallocExpression(Expression *expression) : expression_(expression) {

}
}
