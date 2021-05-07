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
    BaseScope* parent = nullptr;

    inline virtual bool frame_start() const {
        return false;
    }
};


class MethodScope: public BaseScope {
public:
    inline bool frame_start() const override {
        return true;
    }
};
