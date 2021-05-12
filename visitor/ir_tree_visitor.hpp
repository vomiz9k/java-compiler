#pragma once

#include <big_include.hpp>
#include "visitor.hpp"
#include <irtree/tree_wrapper/SubtreeWrapper.h>
#include <function-mechanisms/address/AddressInRegister.h>
#include <function-mechanisms/address/AddressInFrame.h>
#include <unordered_map>



class ir_tree_visitor: public Visitor
{
    static size_t ptr_len;
    static size_t int_len;
    static size_t bool_len;

    IRT::SubtreeWrapper* curr_wrapper = nullptr;
    BaseScope* curr_scope = nullptr;
    std::string curr_class_name;

    const std::string return_address_name = "::return";
    const std::string frame_pointer_address_name = "::fp";
    const std::string return_value_address_name = "::return_value";

    IRT::AddressInRegister frame_pointer_address = IRT::AddressInRegister(IRT::Temporary("::fp"));
    IRT::AddressInRegister return_address = IRT::AddressInRegister(IRT::Temporary("::return"));
    IRT::AddressInRegister return_value_address = IRT::AddressInRegister(IRT::Temporary("::return_value"));

    struct frame {
        MethodScope* scope;

        size_t curr_offset;

        explicit frame(MethodDeclaration* ptr);
        explicit frame(MainClass* inv);
    };

    frame* curr_frame = nullptr;



    void add_class_symbols(std::string* class_name);
    static size_t get_size(Type* type);
    size_t get_class_size(Type* type);
    std::unordered_map<std::string, size_t> class_sizes;

    std::unordered_map<std::string, std::stack<IRT::Address*>> addresses;

    void close_scope() {
        for (auto& symbol: curr_scope->symbols) {
            if (symbol.second->SymbolType() == SYMBOL_VARIABLE) {
                if (addresses.count(symbol.first) == 0) {
                    std::cout << "error closing scope: " + symbol.first + "\n";
                }
                addresses[symbol.first].pop();
            }
        }
    }
    bool is_field(std::string& name);
public:
    #include "visitor_header_body"

    std::unordered_map<std::string, IRT::Statement*> method_trees;

    ir_tree_visitor() {
        class_sizes["int"] = int_len;
        class_sizes["bool"] = bool_len;
    }
};