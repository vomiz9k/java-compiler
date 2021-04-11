#pragma once

#include <unordered_map>
#include <vector>


class BaseSymbol;
class Base;

class BaseScope {
    public:
    Base* holder; 
    std::unordered_map<std::string, BaseSymbol*> symbols;
    std::vector<BaseScope*> children;
    BaseScope* parent;
};
