#include "ir_tree_visitor.hpp"


#include <irtree/tree_wrapper/ExpressionWrapper.h>
#include <irtree/nodes/expressions/ConstExpression.h>
#include <irtree/tree_wrapper/conditional_wrappers/NegateConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/AndConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/OrConditionalWrapper.h>
#include <irtree/types/BinaryOperatorType.h>
#include <irtree/generators/Temporary.h>
#include <irtree/nodes/expressions/BinopExpression.h>
#include <irtree/nodes/expressions/TempExpression.h>
#include <irtree/nodes/expressions/MemExpression.h>
#include <irtree/nodes/expressions/MallocExpression.h>
#include <irtree/nodes/statements/MoveStatement.h>
#include <irtree/tree_wrapper/StatementWrapper.h>
#include <irtree/nodes/statements/LabelStatement.h>
#include <irtree/nodes/statements/SeqStatement.h>
#include <irtree/nodes/statements/PrintStatement.h>
#include <irtree/nodes/statements/JumpStatement.h>
#include <irtree/nodes/ExpressionList.h>
#include <irtree/nodes/expressions/CallExpression.h>
#include <irtree/nodes/expressions/NameExpression.h>
#include <irtree/types/LogicOperatorType.h>
#include <irtree/tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.h>

size_t ir_tree_visitor::ptr_len = 8;
size_t ir_tree_visitor::int_len = 4;
size_t ir_tree_visitor::bool_len = 1;

ir_tree_visitor::frame::frame(MethodDeclaration* ptr) {
    scope = reinterpret_cast<MethodScope*>(ptr->scope);
    curr_offset = ptr_len;
}

ir_tree_visitor::frame::frame(MainClass* ptr) {
    scope = reinterpret_cast<MethodScope*>(ptr->scope);
    curr_offset = 0;
}


bool ir_tree_visitor::is_field(std::string& name) {
    BaseScope* scope = curr_scope;
    while (scope->symbols.count(name) == 0 && !scope->frame_start()) {
        scope = scope->parent;
    }

    return scope->symbols.count(name);
}



void ir_tree_visitor::visit(Program* ptr) {
    curr_scope = ptr->scope;


    for (auto i : ptr->declarations) {
        i->accept(this);
    }

    ptr->main_class->accept(this);
}

size_t ir_tree_visitor::get_size(Type* type) {
    if (!type->is_array) {
        if (*type->name == "int") {
            return int_len;
        } else if (*type->name == "bool") {
            return bool_len;
        }
    }
    return ptr_len;
}

void ir_tree_visitor::add_class_symbols(std::string* class_name) {
    auto symbol = curr_scope->symbols[*class_name];
    if (symbol->SymbolType() != SYMBOL_CLASS) {
        throw std::string("unknown error\n");
    }
    auto class_symbol = reinterpret_cast<ClassSymbol*>(symbol);

    size_t offset = 0;
    for (auto& symbol: class_symbol->fields) {
        auto this_addr = new IRT::MemExpression(frame_pointer_address.ToExpression());
        addresses[symbol->name].push(new IRT::AddressInFrame(this_addr, offset));
        offset += get_size(symbol->type);
    }
    class_sizes[*class_name] = offset;
}

void ir_tree_visitor::visit(MainClass* ptr) {
    //add_class_symbols(ptr->scope, ptr->name);
    auto old_scope = curr_scope;
    curr_scope = ptr->scope;
    curr_frame = new frame(ptr);

    curr_class_name = *ptr->name;
    ptr->body->accept(this);
    auto name = *ptr->name + "::" + "main";
    if (curr_wrapper != nullptr) {
        curr_wrapper = new IRT::StatementWrapper(
            new IRT::SeqStatement(
                 new IRT::LabelStatement(IRT::Label(name)),
                 curr_wrapper->ToStatement()
            )
        );
    } else {
        curr_wrapper = new IRT::StatementWrapper(
            new IRT::SeqStatement(
                new IRT::LabelStatement(IRT::Label(name)),
                new IRT::MoveStatement(
                     return_value_address.ToExpression(),
                    new IRT::ConstExpression(0)
                )
            )
        );
    }
    method_trees[*ptr->name] = curr_wrapper->ToStatement();

    close_scope();

    delete curr_frame;
    curr_frame = nullptr;
    curr_scope = old_scope;

    //class_name
}

void ir_tree_visitor::visit(NotEmptyClassDeclarations* ptr) {

    ptr->class_decl->accept(this);
    ptr->prev_class_decls->accept(this);
}

void ir_tree_visitor::visit(EmptyClassDeclarations* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(ExtendedClassDeclaration* ptr) {
    add_class_symbols(ptr->name);
    auto old_scope = curr_scope;
    curr_scope = ptr->scope;

    curr_class_name = *ptr->name;
    for (auto i : ptr->decls) {
        i->accept(this);
    }
    close_scope();

    curr_scope = old_scope;
    //name, base
}

void ir_tree_visitor::visit(NotExtendedClassDeclaration* ptr) {
    add_class_symbols(ptr->name);
    auto old_scope = curr_scope;
    curr_scope = ptr->scope;

    curr_class_name = *ptr->name;
    for (auto i : ptr->decls) {
        i->accept(this);
    }
    close_scope();

    curr_scope = old_scope;
    //name
}

void ir_tree_visitor::visit(Body* ptr) {
    auto old_scope = curr_scope;
    curr_scope = ptr->scope;

    if (ptr->stmts.empty()) {
        curr_wrapper = nullptr;
        return;
    }

    std::vector<IRT::Statement*> statements;
    statements.reserve(ptr->stmts.size());


    for (auto statement: ptr->stmts) {
        statement->accept(this);
        if (curr_wrapper) {
            statements.push_back(curr_wrapper->ToStatement());
        }
    }
    if (statements.empty()) {
        curr_wrapper = nullptr;
        return;
    }

    IRT::Statement* suffix = statements.back();

    for (int index = static_cast<int>(statements.size()) - 2; index >= 0; --index) {
        suffix = new IRT::SeqStatement(
                statements.at(index),
                suffix
        );
    }

    curr_wrapper = new IRT::StatementWrapper(suffix);
    close_scope();
    curr_scope = old_scope;
    //nochildren
}

void ir_tree_visitor::visit(EmptyStatements* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(NotEmptyStatements* ptr) {
    ptr->prev_statements->accept(this);
    ptr->statement->accept(this);
}

void ir_tree_visitor::visit(IfElseStatement* ptr) {
    ptr->condition->accept(this);
    auto condition = curr_wrapper;
    ptr->do_if_true->accept(this);
    auto true_branch = curr_wrapper;
    ptr->do_else->accept(this);
    auto false_branch = curr_wrapper;

    IRT::Label label_true;
    IRT::Label label_false;
    IRT::Label label_join;

    IRT::Statement* suffix = new IRT::LabelStatement(label_join);

    IRT::Label* result_true = &label_join;
    IRT::Label* result_false = &label_join;

    if (false_branch) {
        result_false = &label_false;
        suffix = new IRT::SeqStatement(
            new IRT::LabelStatement(label_false),
            new IRT::SeqStatement(false_branch->ToStatement(), suffix)
        );

        if (true_branch) {
            suffix = new IRT::SeqStatement(
                new IRT::JumpStatement(label_join),
                suffix
            );
        }
    }

    if (true_branch) {
        result_true = &label_true;
        suffix = new IRT::SeqStatement(
            new IRT::LabelStatement(label_true),
            new IRT::SeqStatement(true_branch->ToStatement(), suffix)
        );
    }

    curr_wrapper = new IRT::StatementWrapper(
        new IRT::SeqStatement(
                condition->ToConditional(*result_true, *result_false),
                suffix
        )
    );
}

void ir_tree_visitor::visit(IfStatement* ptr) {
    ptr->condition->accept(this);
    auto condition = curr_wrapper;
    ptr->do_if_true->accept(this);
    auto true_branch = curr_wrapper;

    IRT::Label label_true;
    IRT::Label label_join;
    IRT::Statement* suffix = new IRT::LabelStatement(label_join);

    IRT::Label* result_true = &label_join;

    if (true_branch) {
        result_true = &label_true;
        suffix = new IRT::SeqStatement(
            new IRT::LabelStatement(label_true),
            new IRT::SeqStatement(true_branch->ToStatement(), suffix)
        );
    }

    curr_wrapper = new IRT::StatementWrapper(
            new IRT::SeqStatement(
                condition->ToConditional(*result_true, label_join),
                suffix
            )
    );
}


void ir_tree_visitor::visit(AssertStatement* ptr) {

    ptr->check->accept(this);
    curr_wrapper = new IRT::StatementWrapper(
            new IRT::MoveStatement(
                    return_value_address.ToExpression(),
                    curr_wrapper->ToExpression()
            ));
}//TODO

void ir_tree_visitor::visit(VarDeclStatement* ptr) {
    ptr->decl->accept(this);
    curr_wrapper = nullptr;
}

void ir_tree_visitor::visit(ScopeStatement* ptr) {
    ptr->body->accept(this);
}

void ir_tree_visitor::visit(WhileStatement* ptr) {
    ptr->condition->accept(this);
    auto condition = curr_wrapper;
    ptr->do_if_true->accept(this);
    auto true_branch = curr_wrapper;

    IRT::Label label_true;
    IRT::Label label_join;
    IRT::Statement* suffix = new IRT::LabelStatement(label_join);

    IRT::Label* result_true = &label_join;

    if (true_branch) {
        result_true = &label_true;
        suffix = new IRT::SeqStatement(
                new IRT::LabelStatement(label_true),
                new IRT::SeqStatement(true_branch->ToStatement(), suffix)
        );
    }

    curr_wrapper = new IRT::StatementWrapper(
            new IRT::SeqStatement(
                    condition->ToConditional(*result_true, label_join),
                    suffix
            )
    );
}

void ir_tree_visitor::visit(PrintStatement* ptr) {

    ptr->to_print->accept(this);
    curr_wrapper = new IRT::StatementWrapper(
        new IRT::PrintStatement(curr_wrapper->ToExpression())
    );
}//TODO

void ir_tree_visitor::visit(AssignmentStatement* ptr) {
    ptr->assignment->accept(this);
}

void ir_tree_visitor::visit(ReturnStatement* ptr) {
    ptr->to_return->accept(this);

    curr_wrapper = new IRT::StatementWrapper(
            new IRT::MoveStatement(
            return_value_address.ToExpression(),
            curr_wrapper->ToExpression()
    ));
}

void ir_tree_visitor::visit(MethodInvocationStatement* ptr) {
    ptr->invocation->accept(this);
}


void ir_tree_visitor::visit(DeclarationsWithVariable* ptr) {

    ptr->prev_decls->accept(this);
    ptr->var_decl->accept(this);
}

void ir_tree_visitor::visit(DeclarationsWithMethod* ptr) {

    ptr->prev_decls->accept(this);
    ptr->method_decl->accept(this);
}

void ir_tree_visitor::visit(EmptyDeclarations* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(MethodDeclaration* ptr) {
    auto old_scope = curr_scope;
    curr_scope = ptr->scope;
    curr_frame = new frame(ptr);

    ptr->type->accept(this);
    ptr->args->accept(this);
    ptr->body->accept(this);

    auto name = curr_class_name + "::" + *ptr->name;
    if (curr_wrapper != nullptr) {
        curr_wrapper = new IRT::StatementWrapper(
            new IRT::SeqStatement(
                new IRT::LabelStatement(IRT::Label(name)),
                curr_wrapper->ToStatement()
            )
        );
    } else {
        curr_wrapper = new IRT::StatementWrapper(
            new IRT::SeqStatement(
                new IRT::LabelStatement(IRT::Label(name)),
                new IRT::MoveStatement(
                   return_value_address.ToExpression(),
                   new IRT::ConstExpression(0)
                )
            )
        );
    }

    method_trees[*ptr->name] = curr_wrapper->ToStatement();


    close_scope();
    delete curr_frame;
    curr_frame = nullptr;
    curr_scope = old_scope;
    //name
}

void ir_tree_visitor::visit(VariableDeclaration* ptr) {
    ptr->type->accept(this);

    if(curr_frame != nullptr) {
        addresses[*ptr->name].push(new IRT::AddressInFrame(
                &frame_pointer_address, curr_frame->curr_offset
        ));
        curr_frame->curr_offset += get_size(ptr->type);
    }

    curr_wrapper = nullptr;
    //name
}

void ir_tree_visitor::visit(EmptyMethodArgs* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(SingleMethodArg* ptr) {

    ptr->arg->accept(this);
}

void ir_tree_visitor::visit(MoreThanOneMethodArgs* ptr) {
    for(auto i : ptr->args) {
        i->accept(this);
    }
}

void ir_tree_visitor::visit(Method_arg* ptr) {

    ptr->type->accept(this);

    addresses[*ptr->name].push(new IRT::AddressInFrame(
            new IRT::AddressInRegister(frame_pointer_address), curr_frame->curr_offset
    ));
    curr_frame->curr_offset += get_size(ptr->type);
    //name
}

void ir_tree_visitor::visit(LastMethodArg* ptr) {

    ptr->arg->accept(this);
}

void ir_tree_visitor::visit(NotLastMethodArgs* ptr) {

    ptr->prev_args->accept(this);
    ptr->arg->accept(this);
}

void ir_tree_visitor::visit(SimpleType* ptr) {

    //name
}

void ir_tree_visitor::visit(ArrayType* ptr) {

    //name
}

void ir_tree_visitor::visit(Assignment* ptr) {

    ptr->lvalue->accept(this);
    auto lvalue = curr_wrapper;
    ptr->rvalue->accept(this);
    auto rvalue = curr_wrapper;

    curr_wrapper = new IRT::StatementWrapper(new IRT::MoveStatement(
            lvalue->ToExpression() ,rvalue->ToExpression())
    );
}

void ir_tree_visitor::visit(MethodInvocation* ptr) {
    auto irt_expressions = new IRT::ExpressionList();

    ptr->from->accept(this);
    irt_expressions->Add(curr_wrapper->ToExpression());

    for(auto arg: ptr->args->exprs) {
        arg->accept(this);
        irt_expressions->Add(curr_wrapper->ToExpression());
    }

    auto name = *ptr->from->type->name + "::" + *ptr->name;

    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::CallExpression(
                    new IRT::NameExpression(IRT::Label(name)),
                    irt_expressions
            )
    );
    //ptr->args->accept(this);
    //name
}

void ir_tree_visitor::visit(FieldInvocation* ptr) {
    //name

    auto address = addresses[*ptr->name].top();
    curr_wrapper = new IRT::ExpressionWrapper(address->ToExpression());
}

void ir_tree_visitor::visit(EmptyExpressions* ptr) {

    //nochildren
}

void ir_tree_visitor::visit(SingleExpression* ptr) {

    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(MoreThanOneExpression* ptr) {
    for(auto i: ptr->exprs) {
        i->accept(this);
    }
}

void ir_tree_visitor::visit(LastExpression* ptr) {

    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(NotLastExpressions* ptr) {

    ptr->prev_exprs->accept(this);
    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(ValueExpr* ptr) {
    ptr->value->accept(this);
}

void ir_tree_visitor::visit(IdExpr* ptr) {
    auto address = addresses[*ptr->name].top();
    curr_wrapper = new IRT::ExpressionWrapper(address->ToExpression());
    //name
}

void ir_tree_visitor::visit(ArrayElementExpr* ptr) {

    ptr->array->accept(this);
    auto array = curr_wrapper;
    ptr->index->accept(this);

    curr_wrapper = new IRT::ExpressionWrapper(new IRT::MemExpression(new IRT::BinopExpression(
            IRT::BinaryOperatorType::PLUS,
                new IRT::BinopExpression(
                    IRT::BinaryOperatorType::PLUS,
                    array->ToExpression(),
                    new IRT::ConstExpression(int_len)
                ),
                new IRT::BinopExpression(
                    IRT::BinaryOperatorType::MUL,
                    curr_wrapper->ToExpression(),
                    new IRT::ConstExpression(get_class_size(ptr->array->type))
                )
            ))
    );
}


void ir_tree_visitor::visit(LengthExpr* ptr) {
    ptr->array->accept(this);
    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::MemExpression(curr_wrapper->ToExpression()));
}

void ir_tree_visitor::visit(FieldInvocationExpr* ptr) {
    ptr->invocation->accept(this);
}

size_t ir_tree_visitor::get_class_size(Type* type) {
    return class_sizes[*type->name];
}

void ir_tree_visitor::visit(NewArrayExpr* ptr) {
    ptr->count->accept(this);

    curr_wrapper = new IRT::ExpressionWrapper(new IRT::MallocExpression(
        new IRT::BinopExpression(
            IRT::BinaryOperatorType::PLUS,
            new IRT::ConstExpression(int_len),
            new IRT::BinopExpression(
                    IRT::BinaryOperatorType::MUL,
                    new IRT::ConstExpression(get_class_size(ptr->type)),
                    curr_wrapper->ToExpression()
                    )
        )
    ));
    //type(str)
}

void ir_tree_visitor::visit(NewSingleExpr* ptr) {
    curr_wrapper = new IRT::ExpressionWrapper(new IRT::MallocExpression(
       new IRT::ConstExpression(get_class_size(ptr->type))
    ));
    //name
}

void ir_tree_visitor::visit(ThisExpr* ptr) {
    std::cout << "THIS?\n";
    curr_wrapper = new IRT::ExpressionWrapper(frame_pointer_address.ToExpression());
    //nochildren
}//TODO: delete?

void ir_tree_visitor::visit(NotExpr* ptr) {
    ptr->expr->accept(this);
    curr_wrapper = new IRT::NegateConditionalWrapper(curr_wrapper);
}

void ir_tree_visitor::visit(MethodInvocationExpr* ptr) {
    ptr->invocation->accept(this);
}

void ir_tree_visitor::visit(PlusExpr* ptr) {
    ptr->first->accept(this);
    auto lhs = curr_wrapper;
    ptr->second->accept(this);
    auto rhs = curr_wrapper;

    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::BinopExpression(
                    IRT::BinaryOperatorType::PLUS,
                    lhs->ToExpression(),
                    rhs->ToExpression()
            )
    );
}

void ir_tree_visitor::visit(MinusExpr* ptr) {
    ptr->first->accept(this);
    auto lhs = curr_wrapper;
    ptr->second->accept(this);
    auto rhs = curr_wrapper;

    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::BinopExpression(
                    IRT::BinaryOperatorType::MINUS,
                    lhs->ToExpression(),
                    rhs->ToExpression()
            )
    );
}

void ir_tree_visitor::visit(MulExpr* ptr) {

    ptr->first->accept(this);
    auto lhs = curr_wrapper;
    ptr->second->accept(this);
    auto rhs = curr_wrapper;

    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::BinopExpression(
                    IRT::BinaryOperatorType::MUL,
                    lhs->ToExpression(),
                    rhs->ToExpression()
            )
    );
}

void ir_tree_visitor::visit(DivExpr* ptr) {

    ptr->first->accept(this);
    auto lhs = curr_wrapper;
    ptr->second->accept(this);
    auto rhs = curr_wrapper;

    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::BinopExpression(
                    IRT::BinaryOperatorType::DIV,
                    lhs->ToExpression(),
                    rhs->ToExpression()
            )
    );
}

void ir_tree_visitor::visit(PercentExpr* ptr) {

    ptr->first->accept(this);
    auto lhs = curr_wrapper;
    ptr->second->accept(this);
    auto rhs = curr_wrapper;

    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::BinopExpression(
                    IRT::BinaryOperatorType::PERCENT,
                    lhs->ToExpression(),
                    rhs->ToExpression()
            )
    );
}

void ir_tree_visitor::visit(AndExpr* ptr) {
    ptr->first->accept(this);
    auto first = curr_wrapper;
    ptr->second->accept(this);
    auto second = curr_wrapper;

    curr_wrapper = new IRT::AndConditionalWrapper(
        first,
        second
    );
}

void ir_tree_visitor::visit(OrExpr* ptr) {
    ptr->first->accept(this);
    auto first = curr_wrapper;
    ptr->second->accept(this);
    auto second = curr_wrapper;

    curr_wrapper = new IRT::OrConditionalWrapper(
        first,
        second
    );
}

void ir_tree_visitor::visit(SmallerExpr* ptr) {
    ptr->first->accept(this);
    auto first = curr_wrapper;
    ptr->second->accept(this);
    auto second = curr_wrapper;

    curr_wrapper = new IRT::RelativeConditionalWrapper(
        IRT::LogicOperatorType::LT,
        first->ToExpression(),
        second->ToExpression()
    );
}

void ir_tree_visitor::visit(BiggerExpr* ptr) {
    ptr->first->accept(this);
    auto first = curr_wrapper;
    ptr->second->accept(this);
    auto second = curr_wrapper;

    curr_wrapper = new IRT::RelativeConditionalWrapper(
        IRT::LogicOperatorType::GT,
        first->ToExpression(),
        second->ToExpression()
    );
}

void ir_tree_visitor::visit(EqualExpr* ptr) {
    ptr->first->accept(this);
    auto first = curr_wrapper;
    ptr->second->accept(this);
    auto second = curr_wrapper;

    curr_wrapper = new IRT::RelativeConditionalWrapper(
        IRT::LogicOperatorType::EQ,
         first->ToExpression(),
         second->ToExpression()
    );
}

void ir_tree_visitor::visit(NotEqualExpr* ptr) {
    ptr->first->accept(this);
    auto first = curr_wrapper;
    ptr->second->accept(this);
    auto second = curr_wrapper;

    curr_wrapper = new IRT::RelativeConditionalWrapper(
        IRT::LogicOperatorType::NE,
        first->ToExpression(),
        second->ToExpression()
    );
}

void ir_tree_visitor::visit(BracketsExpr* ptr) {
    ptr->expr->accept(this);
}

void ir_tree_visitor::visit(IntValue* ptr) {
    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::ConstExpression(ptr->value));
    //value(int)
}

void ir_tree_visitor::visit(BoolValue* ptr) {
    curr_wrapper = new IRT::ExpressionWrapper(
            new IRT::ConstExpression(ptr->value));
    //value(bool)
}

