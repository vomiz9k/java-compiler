#pragma once

#include <string>
#include <base.hpp>
#include "../declaration/declaration.hpp"

class Type;
class Method_args;
class BaseScope;
class Body;

class MethodDeclaration: public Declaration
{
#include <friends_visitors>
    BaseScope* scope;
    Type* type;
    std::string* name;
    Method_args* args;
    Body* body;
public:

    MethodDeclaration (Type* type,
                       std::string* name,
                       Method_args* args,
                       Body* body);

    void accept(Visitor* visitor) override;

    void SetScope(BaseScope* scope);
};