#include <big_include.hpp>
#include <visitor.hpp>
#include "symbol_table_visitor.hpp"
#include <base_scope.hpp>
#include <base_symbol.hpp>



symbol_table_visitor::symbol_table_visitor() {
    int_simple = new Simple_Type(new std::string("int"));
    bool_simple = new Simple_Type(new std::string("bool"));
}

symbol_table_visitor::~symbol_table_visitor() {
    delete int_simple;
    delete bool_simple;
}



size_t symbol_table_visitor::get_size(const Type* type) {
    if (!type->is_array) {
        if (*type->name == "int") {
            return 4;
        } else if (*type->name == "bool") {
            return 1;
        }
    }
    return 8;
}

void symbol_table_visitor::assert_declared(std::string* name, int type) {
    BaseSymbol* symbol = Find(name);
    if (symbol == nullptr) {
        throw "syntax error: " + *name + " not declared";
    }
    if (symbol->SymbolType() != type) {
        throw "syntax error: " + *name + " is wrong type";
    }
}


void symbol_table_visitor::assert_not_declared_in_this_scope(std::string* name) {
    if (curr->symbols.count(*name) > 0) {
        throw "syntax error: " + *name + " already declared";
    }
}

void symbol_table_visitor::assert_type(const Type* checking, const Type* needed) {
    if (*checking->name != *needed->name || checking->is_array != needed->is_array) {
        throw "syntax error: got " + *checking->name + (checking->is_array ? "[]" : "") + 
            ", " + *needed->name + (needed->is_array ? "[]" : "") + " expected";
    }
}

void symbol_table_visitor::assert_array(Type* type) {
    if (!type->is_array) {
        throw std::string("syntax error: must be an array");
    }
}



void symbol_table_visitor::visit(Program* ptr) {
    curr = new BaseScope();
    curr->symbols["int"] = new ClassSymbol("int");
    curr->symbols["bool"] = new ClassSymbol("bool");
    ptr->SetScope(curr);

    for (auto i : ptr->declarations) {
        i->accept(this);
    }
    ptr->main_class->accept(this);
}

void symbol_table_visitor::visit(Main_class* ptr) {
    auto old = curr;
    curr_class = new ClassSymbol(ptr);
    old->symbols[*ptr->name] = curr_class;
    curr = new MethodScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);
    
    ptr->body->accept(this);

    curr = old;
    curr_class = nullptr;
    //class_name
}


//unused
void symbol_table_visitor::visit(Not_empty_Class_declarations* ptr) {
    
    // ptr->class_decl->accept(this);
    // ptr->prev_class_decls->accept(this);
    
}

//unused
void symbol_table_visitor::visit(Empty_Class_declarations* ptr) {
    
    //nochildren
}

void symbol_table_visitor::visit(Extended_Class_declaration* ptr) {

    assert_declared(ptr->base, SYMBOL_CLASS);
    assert_not_declared_in_this_scope(ptr->name);

    auto base_symbol = Find(ptr->base);
    auto old = curr;

    curr_class = new ClassSymbol(ptr);
    old->symbols[*ptr->name] = curr_class;

    curr = new BaseScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);
    
    auto parent_class = reinterpret_cast<ClassSymbol*>(base_symbol);
    for(auto& field: parent_class->fields) {
        curr_class->fields.push_back(field);
    }
    for(auto& method: parent_class->methods) {
        curr_class->methods.push_back(method);
    }

    for(auto i : ptr->decls) {
        i->accept(this);
    }
    
    curr = old;
    curr_class = nullptr;
    //name, base
}

void symbol_table_visitor::visit(Not_extended_Class_declaration* ptr) {
    assert_not_declared_in_this_scope(ptr->name);
    
    auto old = curr;

    curr_class = new ClassSymbol(ptr);
    old->symbols[*ptr->name] = curr_class;
    curr = new BaseScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);

    for(auto i : ptr->decls) {
        i->accept(this);
    }

    curr = old;
    curr_class = nullptr;
    //name
}

void symbol_table_visitor::visit(Body* ptr) {
    auto old = curr;
    curr = new BaseScope();
    old->children.push_back(curr);
    curr->parent = old;
    for (auto i: ptr->stmts) {
        i->accept(this);
    }
    curr = old;
    //nochildren
}


//unused
void symbol_table_visitor::visit(Empty_Statements* ptr) {
    
    //nochildren
}

//unused
void symbol_table_visitor::visit(Not_empty_Statements* ptr) {

    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
}

void symbol_table_visitor::visit(If_else_Statement* ptr) {

    ptr->condition->accept(this);
    assert_type(ptr->condition->type, bool_simple);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
}

void symbol_table_visitor::visit(If_Statement* ptr) {

    ptr->condition->accept(this);
    assert_type(ptr->condition->type, bool_simple);
    ptr->do_if_true->accept(this);
}


void symbol_table_visitor::visit(Assert_Statement* ptr) {
    ptr->check->accept(this);
    assert_type(ptr->check->type, bool_simple);
}

void symbol_table_visitor::visit(Var_decl_Statement* ptr) {
    ptr->decl->accept(this);
}

void symbol_table_visitor::visit(Big_Statement* ptr) {
    ptr->body->accept(this);
}

void symbol_table_visitor::visit(While_Statement* ptr) {

    ptr->condition->accept(this);
    assert_type(ptr->condition->type, bool_simple);
    ptr->do_if_true->accept(this);
}

void symbol_table_visitor::visit(Print_Statement* ptr) {

    ptr->to_print->accept(this);
    assert_type(ptr->to_print->type, int_simple);
}

void symbol_table_visitor::visit(Assignment_Statement* ptr) {
    ptr->assignment->accept(this);
}


void symbol_table_visitor::visit(Single_Lvalue* ptr) {
    assert_declared(ptr->name, SYMBOL_VARIABLE);
    ptr->type = reinterpret_cast<VariableSymbol*>(Find(ptr->name))->type;
    //name
}

void symbol_table_visitor::visit(Arr_el_Lvalue* ptr) {
    assert_declared(ptr->name, SYMBOL_VARIABLE);
    ptr->type = reinterpret_cast<VariableSymbol*>(Find(ptr->name))->type;
    ptr->index->accept(this);
    assert_type(ptr->index->type, int_simple);
    //name
}

void symbol_table_visitor::visit(Field_Lvalue* ptr) {
    ptr->invocation->accept(this);
    ptr->type = reinterpret_cast<VariableSymbol*>(Find(ptr->invocation->name))->type;
}


void symbol_table_visitor::visit(Field_arr_el_Lvalue* ptr) {
    ptr->invocation->accept(this);
    ptr->type = reinterpret_cast<VariableSymbol*>(Find(ptr->invocation->name))->type;

    ptr->index->accept(this);
    assert_type(ptr->index->type, int_simple);
}

void symbol_table_visitor::visit(Return_Statement* ptr) {

    ptr->to_return->accept(this);
    assert_type(ptr->to_return->type, curr_method->type);
}

void symbol_table_visitor::visit(Method_invocation_Statement* ptr) {
    ptr->invocation->accept(this);
}





//unused
void symbol_table_visitor::visit(Declarations_with_variable* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
}

//unused
void symbol_table_visitor::visit(Declarations_with_method* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
}

//unused
void symbol_table_visitor::visit(Empty_Declarations* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(Method_declaration* ptr) {
    assert_not_declared_in_this_scope(ptr->name);
    
    curr_method = new MethodSymbol(ptr);
    curr->symbols[*ptr->name] = curr_method;
    auto old = curr;
    curr = new MethodScope();
    ptr->SetScope(curr);
    curr->parent = old;
    old->children.push_back(curr);
    
    curr_class->methods.push_back(curr_method);

    if (*ptr->type->name != "void") {
        ptr->type->accept(this);
    }

    ptr->args->accept(this);
    ptr->body->accept(this);

    curr_method = nullptr;
    curr = old;
    //name
}

void symbol_table_visitor::visit(Variable_declaration* ptr) {
    assert_not_declared_in_this_scope(ptr->name);

    auto var_symbol = new VariableSymbol(ptr);
    curr->symbols[*ptr->name] = var_symbol;
    curr_class->fields.push_back(var_symbol);

    ptr->type->accept(this);
    //name
}

void symbol_table_visitor::visit(Empty_Method_args* ptr) {

    //nochildren
}


void symbol_table_visitor::visit(Single_Method_args* ptr) {
    ptr->arg->accept(this);
}

void symbol_table_visitor::visit(Many_Method_args* ptr) {
    for(auto i : ptr->args) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(Method_arg* ptr) {
    assert_not_declared_in_this_scope(ptr->name);
    auto arg = new VariableSymbol(ptr);
    curr->symbols[*ptr->name] = arg;
    curr_method->arguments.push_back(arg);

    ptr->type->accept(this);
    //name
}


//unused
void symbol_table_visitor::visit(Last_Method_multiple_arg* ptr) {

    ptr->arg->accept(this);
}


//unused
void symbol_table_visitor::visit(Many_Method_multiple_arg* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void symbol_table_visitor::visit(Simple_Type* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);
    
    //name
}

void symbol_table_visitor::visit(Array_Type* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);

    //name
}

void symbol_table_visitor::visit(Assignment* ptr) {
    ptr->lvalue->accept(this);
    ptr->rvalue->accept(this);
    if (!ptr->lvalue->is_lvalue) {
        throw std::string("syntax error: not lvalue in left part of assignment");
    }
    assert_type(ptr->rvalue->type, ptr->lvalue->type);
}

void symbol_table_visitor::visit(Method_invocation* ptr) {
    ptr->from->accept(this);
    ClassSymbol* method_holder = nullptr;
    MethodSymbol* calling_method = nullptr;
    
    if (*ptr->from->type->name != "this") {
        assert_declared(ptr->from->type->name, SYMBOL_CLASS);
        method_holder = reinterpret_cast<ClassSymbol*>(Find(ptr->from->type->name));
    }
    else {
        method_holder = curr_class;
    }


    for (auto method : method_holder->methods) {
        if (method->name == *ptr->name) {
            calling_method = method;
            break;
        }
    }
    
    if (calling_method == nullptr) {
        throw "syntax error: class " + method_holder->name + " has no method named " + *ptr->name;
    }
    
    
    ptr->args->accept(this);
    if (ptr->args->exprs.size() != calling_method->arguments.size()) {
        throw "syntax error: can't call " + method_holder->name + "." + calling_method->name + " with this count of arguments";
    }
    for(size_t i = 0; i < calling_method->arguments.size(); ++i) {
        assert_type(ptr->args->exprs[i]->type, calling_method->arguments[i]->type);
    }

    ptr->type = calling_method->type;
    //name
}

void symbol_table_visitor::visit(Field_invocation* ptr) {
    bool field_exists = false;
    for(auto field : curr_class->fields) {
        if (field->name == *ptr->name) {
            field_exists = true;
            ptr->type = field->type;
            break;
        }
    }
    if (!field_exists) {
        throw "syntax error: can't find field " + *ptr->name;
    }
    //name
}

void symbol_table_visitor::visit(Empty_Expressions* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(Single_Expressions* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Many_Expressions* ptr) {
    for(auto i: ptr->exprs) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(Single_Multiple_expressions* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Many_Multiple_expressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(Value_Expr* ptr) {
    ptr->type = ptr->value->type;
    ptr->value->accept(this);
}

void symbol_table_visitor::visit(Id_Expr* ptr) {
    assert_declared(ptr->name, SYMBOL_VARIABLE);
    ptr->type = reinterpret_cast<VariableSymbol*>(Find(*ptr->name))->type;
    //name
}

void symbol_table_visitor::visit(Array_el_Expr* ptr) {
    ptr->array->accept(this);
    assert_array(ptr->array->type);


    ptr->index->accept(this);
    assert_type(ptr->index->type, int_simple);

    ptr->type = new Simple_Type(ptr->array->type->name);
}

void symbol_table_visitor::visit(Length_Expr* ptr) {
    ptr->array->accept(this);
    assert_array(ptr->array->type);
    ptr->type = int_simple;
    //type=int
}

void symbol_table_visitor::visit(Field_invocation_Expr* ptr) {
    ptr->invocation->accept(this);
    ptr->type = ptr->invocation->type;
}

void symbol_table_visitor::visit(New_arr_Expr* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);
    ptr->count->accept(this);
    assert_type(ptr->count->type, int_simple);
    
    ptr->type = new Array_Type(ptr->name);
}

void symbol_table_visitor::visit(New_single_Expr* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);
    ptr->type = new Simple_Type(ptr->name);
}

void symbol_table_visitor::visit(This_Expr* ptr) {
    ptr->type = new Simple_Type(&curr_class->name);
    //nochildren
}

void symbol_table_visitor::visit(Not_Expr* ptr) {
    ptr->expr->accept(this);
    assert_type(ptr->expr->type, bool_simple);
    ptr->type = ptr->expr->type;
}

void symbol_table_visitor::visit(Method_invocation_Expr* ptr) {
    ptr->invocation->accept(this);
    ptr->type =  ptr->invocation->type;
}

void symbol_table_visitor::visit(Plus_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(Minus_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(Star_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(Slash_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(Percent_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(And_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, bool_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, bool_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(Or_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, bool_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, bool_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(Smaller_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(Bigger_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(Equal_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(Not_equal_Expr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(Brackets_Expr* ptr) {
    ptr->expr->accept(this);
    ptr->type = ptr->expr->type;
}

void symbol_table_visitor::visit(Number_Value* ptr) {

    //value(int)
}

void symbol_table_visitor::visit(TF_Value* ptr) {

    //value(bool)
}