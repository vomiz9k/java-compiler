#include <big_include.hpp>
#include <visitor.hpp>
#include "symbol_table_visitor.hpp"
#include <base_scope.hpp>
#include <base_symbol.hpp>



symbol_table_visitor::symbol_table_visitor() {
    int_simple = new SimpleType(new std::string("int"));
    bool_simple = new SimpleType(new std::string("bool"));
}

symbol_table_visitor::~symbol_table_visitor() {
    delete int_simple;
    delete bool_simple;
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
    if (curr_scope->symbols.count(*name) > 0) {
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
    curr_scope = new BaseScope();
    curr_scope->symbols["int"] = new ClassSymbol("int");
    curr_scope->symbols["bool"] = new ClassSymbol("bool");
    ptr->SetScope(curr_scope);

    for (auto i : ptr->declarations) {
        i->accept(this);
    }
    ptr->main_class->accept(this);
}

void symbol_table_visitor::visit(MainClass* ptr) {
    auto old = curr_scope;
    curr_class = new ClassSymbol(ptr);
    old->symbols[*ptr->name] = curr_class;

    curr_frame = new MethodScope("main");
    curr_scope = curr_frame;
    ptr->SetScope(curr_scope);
    curr_scope->parent = old;
    old->children.push_back(curr_scope);
    
    ptr->body->accept(this);

    curr_scope = old;
    curr_frame = nullptr;
    curr_class = nullptr;
    //class_name
}


//unused
void symbol_table_visitor::visit(NotEmptyClassDeclarations* ptr) {
    
    // ptr->class_decl->accept(this);
    // ptr->prev_class_decls->accept(this);
    
}

//unused
void symbol_table_visitor::visit(EmptyClassDeclarations* ptr) {
    
    //nochildren
}

void symbol_table_visitor::visit(ExtendedClassDeclaration* ptr) {

    assert_declared(ptr->base, SYMBOL_CLASS);
    assert_not_declared_in_this_scope(ptr->name);

    auto base_symbol = Find(ptr->base);
    auto old = curr_scope;

    curr_class = new ClassSymbol(ptr);
    old->symbols[*ptr->name] = curr_class;

    curr_scope = new BaseScope();
    ptr->SetScope(curr_scope);
    curr_scope->parent = old;
    old->children.push_back(curr_scope);
    
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

    curr_scope = old;
    curr_class = nullptr;
    //name, base
}

void symbol_table_visitor::visit(NotExtendedClassDeclaration* ptr) {
    assert_not_declared_in_this_scope(ptr->name);
    
    auto old = curr_scope;

    curr_class = new ClassSymbol(ptr);
    old->symbols[*ptr->name] = curr_class;
    curr_scope = new BaseScope();
    ptr->SetScope(curr_scope);
    curr_scope->parent = old;
    old->children.push_back(curr_scope);

    for(auto i : ptr->decls) {
        i->accept(this);
    }

    curr_scope = old;
    curr_class = nullptr;
    //name
}

void symbol_table_visitor::visit(Body* ptr) {
    auto old = curr_scope;
    curr_scope = new BaseScope();
    ptr->SetScope(curr_scope);
    old->children.push_back(curr_scope);
    curr_scope->parent = old;
    for (auto i: ptr->stmts) {
        i->accept(this);
    }
    curr_scope = old;
    //nochildren
}


//unused
void symbol_table_visitor::visit(EmptyStatements* ptr) {
    
    //nochildren
}

//unused
void symbol_table_visitor::visit(NotEmptyStatements* ptr) {

    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
}

void symbol_table_visitor::visit(IfElseStatement* ptr) {

    ptr->condition->accept(this);
    assert_type(ptr->condition->type, bool_simple);
    ptr->do_if_true->accept(this);
    ptr->do_else->accept(this);
}

void symbol_table_visitor::visit(IfStatement* ptr) {

    ptr->condition->accept(this);
    assert_type(ptr->condition->type, bool_simple);
    ptr->do_if_true->accept(this);
}


void symbol_table_visitor::visit(AssertStatement* ptr) {
    ptr->check->accept(this);
    assert_type(ptr->check->type, bool_simple);
}

void symbol_table_visitor::visit(VarDeclStatement* ptr) {
    ptr->decl->accept(this);
}

void symbol_table_visitor::visit(ScopeStatement* ptr) {
    ptr->body->accept(this);
}

void symbol_table_visitor::visit(WhileStatement* ptr) {

    ptr->condition->accept(this);
    assert_type(ptr->condition->type, bool_simple);
    ptr->do_if_true->accept(this);
}

void symbol_table_visitor::visit(PrintStatement* ptr) {

    ptr->to_print->accept(this);
    assert_type(ptr->to_print->type, int_simple);
}

void symbol_table_visitor::visit(AssignmentStatement* ptr) {
    ptr->assignment->accept(this);
}



void symbol_table_visitor::visit(ReturnStatement* ptr) {

    ptr->to_return->accept(this);
    assert_type(ptr->to_return->type, curr_method->type);
}

void symbol_table_visitor::visit(MethodInvocationStatement* ptr) {
    ptr->invocation->accept(this);
}


//unused
void symbol_table_visitor::visit(DeclarationsWithVariable* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
}

//unused
void symbol_table_visitor::visit(DeclarationsWithMethod* ptr) {
    
    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
}

//unused
void symbol_table_visitor::visit(EmptyDeclarations* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(MethodDeclaration* ptr) {
    assert_not_declared_in_this_scope(ptr->name);
    
    curr_method = new MethodSymbol(ptr);
    curr_scope->symbols[*ptr->name] = static_cast<BaseSymbol *>(curr_method);
    auto old = curr_scope;
    curr_frame = new MethodScope(*ptr->name);
    curr_scope = curr_frame;

    ptr->SetScope(curr_scope);
    curr_scope->parent = old;
    old->children.push_back(curr_scope);
    
    curr_class->methods.push_back(curr_method);

    if (*ptr->type->name != "void") {
        ptr->type->accept(this);
    }

    ptr->args->accept(this);
    ptr->body->accept(this);

    curr_method = nullptr;
    curr_frame = nullptr;
    curr_scope = old;
    //name
}

void symbol_table_visitor::visit(VariableDeclaration* ptr) {
    assert_not_declared_in_this_scope(ptr->name);

    auto var_symbol = new VariableSymbol(ptr);
    curr_scope->symbols[*ptr->name] = var_symbol;

    if (curr_frame == nullptr) {
        curr_class->fields.push_back(var_symbol);
    }

    ptr->type->accept(this);

    //name
}

void symbol_table_visitor::visit(EmptyMethodArgs* ptr) {

    //nochildren
}


void symbol_table_visitor::visit(SingleMethodArg* ptr) {
    ptr->arg->accept(this);
}

void symbol_table_visitor::visit(MoreThanOneMethodArgs* ptr) {
    for(auto i : ptr->args) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(Method_arg* ptr) {
    assert_not_declared_in_this_scope(ptr->name);
    auto arg = new VariableSymbol(ptr);
    curr_scope->symbols[*ptr->name] = arg;
    curr_method->arguments.push_back(arg);

    ptr->type->accept(this);
    //name
}


//unused
void symbol_table_visitor::visit(LastMethodArg* ptr) {

    ptr->arg->accept(this);
}


//unused
void symbol_table_visitor::visit(NotLastMethodArgs* ptr) {
    
    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void symbol_table_visitor::visit(SimpleType* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);
    
    //name
}

void symbol_table_visitor::visit(ArrayType* ptr) {
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

void symbol_table_visitor::visit(MethodInvocation* ptr) {
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

void symbol_table_visitor::visit(FieldInvocation* ptr) {
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

void symbol_table_visitor::visit(EmptyExpressions* ptr) {

    //nochildren
}

void symbol_table_visitor::visit(SingleExpression* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(MoreThanOneExpression* ptr) {
    for(auto i: ptr->exprs) {
        i->accept(this);
    }
}

void symbol_table_visitor::visit(LastExpression* ptr) {

    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(NotLastExpressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
}

void symbol_table_visitor::visit(ValueExpr* ptr) {
    ptr->type = ptr->value->type;
    ptr->value->accept(this);
}

void symbol_table_visitor::visit(IdExpr* ptr) {
    assert_declared(ptr->name, SYMBOL_VARIABLE);
    ptr->type = reinterpret_cast<VariableSymbol*>(Find(*ptr->name))->type;
    //name
}

void symbol_table_visitor::visit(ArrayElementExpr* ptr) {
    ptr->array->accept(this);
    assert_array(ptr->array->type);


    ptr->index->accept(this);
    assert_type(ptr->index->type, int_simple);

    ptr->type = new SimpleType(ptr->array->type->name);
}

void symbol_table_visitor::visit(LengthExpr* ptr) {
    ptr->array->accept(this);
    assert_array(ptr->array->type);
    ptr->type = int_simple;
    //type=int
}

void symbol_table_visitor::visit(FieldInvocationExpr* ptr) {
    ptr->invocation->accept(this);
    ptr->type = ptr->invocation->type;
}

void symbol_table_visitor::visit(NewArrayExpr* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);
    ptr->count->accept(this);
    assert_type(ptr->count->type, int_simple);
    
    ptr->type = new ArrayType(ptr->name);
}

void symbol_table_visitor::visit(NewSingleExpr* ptr) {
    assert_declared(ptr->name, SYMBOL_CLASS);
    ptr->type = new SimpleType(ptr->name);
}

void symbol_table_visitor::visit(ThisExpr* ptr) {
    ptr->type = new SimpleType(&curr_class->name);
    //nochildren
}

void symbol_table_visitor::visit(NotExpr* ptr) {
    ptr->expr->accept(this);
    assert_type(ptr->expr->type, bool_simple);
    ptr->type = ptr->expr->type;
}

void symbol_table_visitor::visit(MethodInvocationExpr* ptr) {
    ptr->invocation->accept(this);
    ptr->type =  ptr->invocation->type;
}

void symbol_table_visitor::visit(PlusExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(MinusExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(MulExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(DivExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(PercentExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = int_simple;
}

void symbol_table_visitor::visit(AndExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, bool_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, bool_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(OrExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, bool_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, bool_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(SmallerExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(BiggerExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(EqualExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(NotEqualExpr* ptr) {

    ptr->first->accept(this);
    assert_type(ptr->first->type, int_simple);
    ptr->second->accept(this);
    assert_type(ptr->second->type, int_simple);
    ptr->type = bool_simple;
}

void symbol_table_visitor::visit(BracketsExpr* ptr) {
    ptr->expr->accept(this);
    ptr->type = ptr->expr->type;
}

void symbol_table_visitor::visit(IntValue* ptr) {

    //value(int)
}

void symbol_table_visitor::visit(BoolValue* ptr) {

    //value(bool)
}