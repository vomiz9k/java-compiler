#pragma once

#include <base.hpp>
#include <string>
#include <vector>

class BaseScope;

class Declarations;
class Declaration;
class Class_declaration: public Base
{
    
    std::vector<Declaration*> decls;
    #include <friends_visitors>
    
public:
   
    std::string* name;
    BaseScope* scope;

    void SetScope(BaseScope* scope);
    virtual void accept(Visitor* visitor) = 0;
};

class Extended_Class_declaration: public Class_declaration
{
    //std::vector<Declaration*> decls;
    #include <friends_visitors>
    
    std::string* base;
    Declarations* declarations;
public:
    Extended_Class_declaration(std::string* name, std::string* base, Declarations* declarations);
    void accept(Visitor* visitor) override;
};

class Not_extended_Class_declaration: public Class_declaration
{
    //std::vector<Declaration*> decls;
    #include <friends_visitors>
    Declarations* declarations;
public:
    Not_extended_Class_declaration(std::string* name, Declarations* declarations);
    void accept(Visitor* visitor) override;
};