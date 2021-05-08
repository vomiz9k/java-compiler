#pragma once

#include <unordered_map>
#include <vector>
#include <stack>

#include <function-mechanisms/address/AddressInFrame.h>
#include <function-mechanisms/address/AddressInRegister.h>

class Base;
class MethodScope;
class BaseSymbol;

class BaseScope {
    public:
    Base* holder = nullptr;
    std::unordered_map<std::string, BaseSymbol*> symbols;
    std::vector<BaseScope*> children;
    BaseScope* parent = nullptr;
    std::unordered_map <std::string, std::stack<IRT::Address*>> addresses;


    inline virtual bool frame_start() const {
        return false;
    }
};



class MethodScope: public BaseScope {
public:
    std::string name;
    explicit MethodScope(const std::string& name) : name(name) {};

    inline bool frame_start() const override {
        return true;
    }


//    IRT::Address* get_address(const std::string& name) {
//    }
};


