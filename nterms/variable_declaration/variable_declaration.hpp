#pragma once

#include <string>
#include <base.hpp>
#include "../declaration/declaration.hpp"

class Type;
class Method_args;

class VariableDeclaration: public Declaration {

#include <friends_visitors>
    Type* type;
    std::string* name;

public:
    VariableDeclaration (Type* type, std::string* name);
    void accept(Visitor* visitor) override;
};