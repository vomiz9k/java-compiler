%skeleton "lalr1.cc"
%require "3.7"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <big_include.hpp>


    class Lexer;
    class Driver;
}


%define parse.trace
%define parse.error verbose


%code {
    #include <driver.hpp>
    
    static yy::parser::symbol_type yylex(Lexer &lexer) {
        return lexer.ScanToken();
    }
}



%lex-param { Lexer &lexer }

%parse-param { Lexer& lexer }
%parse-param { Driver& driver }




%token
    END 0 "end of file"

    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    VOID  "void" 
    MAIN "main"
    EXTENDS "extends"

    IF "if"
    ELSE "else"
    WHILE "while"
    SOP "System.out.println"

    INT "int"
    BOOL "bool"

    ASSERT "assert"
    RETURN "return"

    LENGTH "length"
    THIS "this"
    NEW "new"

    TRUE "true"
    FALSE "false"


    LBRACKET "("
    RBRACKET ")"
    LFBRACKET "{" //Figure
    RFBRACKET "}"
    LSBRACKET "[" //Square
    ARRAY_DECL_BRACKETS "[]"
    RSBRACKET "]"

    BIGGER ">"
    SMALLER "<"

    EQUAL "=="
    NOT_EQUAL "!="

    ASSIGN "="

    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    PERCENT "%"

    SEMICOLON ";"

    POINT "."
    COMMA ","

    LOGIC_AND "&&"
    LOGIC_OR "||"
    LOGIC_NOT "!"
;

%nterm <Program*> program
%nterm <Main_class*> main_class
%nterm <Class_declarations*> class_declarations
%nterm <Class_declaration*> class_declaration
%nterm <Declarations*> declarations
%nterm <Method_declaration*> method_declaration
%nterm <Variable_declaration*> variable_declaration
%nterm <Method_args*> method_args
%nterm <Method_multiple_arg*> method_multiple_arg
%nterm <Method_arg*> method_arg
%nterm <Type*> type
%nterm <std::string*> simple_type
%nterm <Statements*> statements
%nterm <Statement*> statement
%nterm <Assignment*> assignment
%nterm <Expressions*> expressions
%nterm <Multiple_expressions*> multiple_expressions
%nterm <Method_invocation*> method_invocation
%nterm <Field_invocation*> field_invocation
%nterm <Value*> value;
%nterm <Expr*> expr


%token <std::string*> IDENTIFIER 
%token <int> NUMBER 



%%

%left "+" "-";
%left "*" "/" "%";
%left "(";
%left "[";
%left ".";
%left "!";
%left "||";
%left "&&";
%left ">" "<" "==" "!=";
%left "=";
%left ";";

%nonassoc "then";
%nonassoc "else";

%start program;

program: 
    main_class class_declarations {$$ = new Program($1, $2); driver.program = $$; };

main_class: 
    "class" IDENTIFIER "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" {$$ = new Main_class($IDENTIFIER, $statements);};

class_declarations: 
    class_declarations[prev] class_declaration  {$$ = new Not_empty_Class_declarations($prev, $class_declaration);}
    | %empty {$$ = new Empty_Class_declarations();};

class_declaration:  
    "class" IDENTIFIER[name] "extends" IDENTIFIER[base] "{" declarations "}" {$$ = new Extended_Class_declaration($name, $base, $declarations);}
    | "class" IDENTIFIER[name] "{" declarations "}" {$$ = new Not_extended_Class_declaration($name, $declarations);};

declarations: 
    declarations[prev] variable_declaration  {$$ = new Declarations_with_variable($prev, $variable_declaration);}
    | declarations[prev] method_declaration  {$$ = new Declarations_with_method($prev, $method_declaration);}
    | %empty {$$ = new Empty_Declarations();};

method_declaration:
    "public" type IDENTIFIER "(" method_args ")" "{" statements "}" {$$ = new Method_declaration($type, $IDENTIFIER, $method_args, $statements);};

variable_declaration:
    type IDENTIFIER ";" {$$ = new Variable_declaration($type, $IDENTIFIER);};

method_args:
    %empty {$$ = new Empty_Method_args();} 
    | method_arg {$$ = new Single_Method_args($method_arg);}
    | method_multiple_arg "," method_arg  {$$ = new Many_Method_args($method_multiple_arg, $method_arg);};

method_arg:
    type IDENTIFIER {$$ = new  Method_arg($type, $IDENTIFIER);};

method_multiple_arg:
    method_arg {$$ = new Last_Method_multiple_arg($method_arg);}
    | method_multiple_arg[prev] "," method_arg {$$ = new Many_Method_multiple_arg($prev, $method_arg);};

type:
    simple_type {$$ = new Simple_Type($simple_type);}
    | simple_type "[]" {$$ = new Array_Type($simple_type);};

simple_type:
    "int" {$$ = new std::string("int");}
    | "bool" {$$ = new std::string("bool");}
    | "void" {$$ = new  std::string("void");}
    | IDENTIFIER {$$ = $IDENTIFIER;};

statements:   
    %empty {$$ = new Empty_Statements();} 
    | statements[prev] statement  {$$ = new Not_empty_Statements($prev, $statement);};


statement:
    "if" "(" expr ")" statement[true] "else" statement[else] {$$ = new If_else_Statement($expr, $true, $else);}
    | "if" "(" expr ")" statement[true] %prec "then" {$$ = new If_Statement($expr, $true);}
    | "assert" "(" expr ")" ";" {$$ = new Assert_Statement($expr);}
    | variable_declaration {$$ = new Var_decl_Statement($variable_declaration);}
    | "{" statements "}" {$$ = new Big_Statement($statements);}
    | "while" "(" expr ")" statement[true] {$$ = new While_Statement($expr, $true);}
    | "System.out.println" "(" expr ")" ";" {$$ = new Print_Statement($expr);}
    | assignment ";" {$$ = new Assignment_Statement($assignment);}
    | "return" expr ";" {$$ = new Return_Statement($expr);}
    | method_invocation ";" {$$ = new Method_invocation_Statement($method_invocation);};


assignment:
    expr[lvalue] "=" expr[rvalue] {$$ = new Assignment($lvalue, $rvalue);};

method_invocation:
    expr "." IDENTIFIER "(" expressions ")" {$$ = new Method_invocation($expr, $IDENTIFIER, $expressions);};

field_invocation:
    "this" "." IDENTIFIER {$$ = new Field_invocation($IDENTIFIER);};

expressions:
    %empty {$$ = new Empty_Expressions();}
    | expr {$$ = new Single_Expressions($expr);}
    | multiple_expressions "," expr {$$ = new Many_Expressions($multiple_expressions, $expr);};

multiple_expressions:
    expr  {$$ = new Single_Multiple_expressions($expr);}
    | multiple_expressions[prev] "," expr  {$$ = new Many_Multiple_expressions($prev, $expr);};

expr: 
    value {$$ = new Value_Expr($value);}
    | IDENTIFIER {$$ = new Id_Expr($IDENTIFIER);}
    | expr[arr] "[" expr[index] "]" {$$ = new Array_el_Expr($arr, $index);}
    | expr[arr] "." "length" {$$ = new Length_Expr($arr);}
    | field_invocation {$$ = new Field_invocation_Expr($field_invocation);}
    | "new" simple_type "[" expr[index] "]" {$$ = new New_arr_Expr($simple_type, $index);}
    | "new" IDENTIFIER "(" ")" {$$ = new New_single_Expr($IDENTIFIER);}
    | "!" expr[neg] {$$ = new Not_Expr($neg);}
    | "this" {$$ = new This_Expr();}
    | method_invocation {$$ = new Method_invocation_Expr($method_invocation);}
    | expr[first] "+" expr[second] {$$ = new Plus_Expr($first, $second);}
    | expr[first] "-" expr[second] {$$ = new Minus_Expr($first, $second);}
    | expr[first] "*" expr[second] {$$ = new Star_Expr($first, $second);}
    | expr[first] "/" expr[second] {$$ = new Slash_Expr($first, $second);}
    | expr[first] "%" expr[second] {$$ = new Percent_Expr($first, $second);}
    | expr[first] "&&" expr[second] {$$ = new And_Expr($first, $second);}
    | expr[first] "||" expr[second] {$$ = new Or_Expr($first, $second);}
    | expr[first] "<" expr[second] {$$ = new Smaller_Expr($first, $second);}
    | expr[first] ">" expr[second] {$$ = new Bigger_Expr($first, $second);}
    | expr[first] "==" expr[second] {$$ = new Equal_Expr($first, $second);}
    | expr[first] "!=" expr[second] {$$ = new Not_equal_Expr($first, $second);}
    | "(" expr[in] ")" {$$ = new Brackets_Expr($in);};

value:
    NUMBER {$$ = new Number_Value($NUMBER);}
    | "true" {$$ = new TF_Value(true);}
    | "false" {$$ = new TF_Value(false);};
   

%%

void yy::parser::error(const std::string& str)
{
    std::cerr << "Syntax Error: " << str << '\n';
}

