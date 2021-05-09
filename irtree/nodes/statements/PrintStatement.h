#pragma once
#include "../statements/Statement.h"



namespace IRT {

    class Expression;

    class PrintStatement: public Statement {
    public:
        explicit PrintStatement(Expression *expression);
        void Accept(Visitor *visitor) override;
        Expression* expression_;
    };

};

