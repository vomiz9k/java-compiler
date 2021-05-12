#pragma once
#include "Expression.h"

namespace IRT {

class MallocExpression: public Expression {
public:
    MallocExpression(Expression *expression);
    void Accept(Visitor *visitor) override;
    Expression* expression_;
};

};

