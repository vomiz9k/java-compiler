#pragma once
#include "../statements/Statement.h"



namespace IRT {

    class Expression;

    class AssertStatement: public Statement {
    public:
        explicit AssertStatement(Expression *expression);
        void Accept(Visitor *visitor) override;
        Expression* expression_;
    };

};

