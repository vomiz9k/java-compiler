#include <base.hpp>
#include <string>


class Type;

class Field_invocation: public Base
{
    #include <friends_visitors>
    std::string* name;
    Type* type;    
public:
    Field_invocation(std::string* name);
    void accept(Visitor* visitor) override;
};