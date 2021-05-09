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
    THIS "this."
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
%nterm <MainClass*> main_class
%nterm <Class_declarations*> class_declarations
%nterm <Class_declaration*> class_declaration
%nterm <Declarations*> declarations
%nterm <MethodDeclaration*> method_declaration
%nterm <VariableDeclaration*> variable_declaration
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
%nterm <MethodInvocation*> method_invocation
%nterm <FieldInvocation*> field_invocation
%nterm <Value*> value
%nterm <Expr*> expr

%nterm <Body*> body


%token <std::string*> IDENTIFIER 
%token <int> NUMBER 



%%

%left "+" "-";
%left "*" "/" "%";
%left "(" ")";
%left "[" "[]" "]";
%left "!";
%left "||";
%left "&&";
%left ">" "<" "==" "!=";
%left ".";

%nonassoc "then";
%nonassoc "else";

%start program;

program: 
    main_class class_declarations {$$ = new Program($1, $2); driver.set_program($$); };

main_class: 
    "class" IDENTIFIER "{" "public" "static" "void" "main" "(" ")" "{" body "}" "}" {$$ = new MainClass($IDENTIFIER, $body);};

class_declarations: 
    class_declarations[prev] class_declaration  {$$ = new NotEmptyClassDeclarations($prev, $class_declaration);}
    | %empty {$$ = new EmptyClassDeclarations();};

class_declaration:  
    "class" IDENTIFIER[name] "extends" IDENTIFIER[base] "{" declarations "}" {$$ = new ExtendedClassDeclaration($name, $base, $declarations);}
    | "class" IDENTIFIER[name] "{" declarations "}" {$$ = new NotExtendedClassDeclaration($name, $declarations);};

declarations: 
    declarations[prev] variable_declaration  {$$ = new DeclarationsWithVariable($prev, $variable_declaration);}
    | declarations[prev] method_declaration  {$$ = new DeclarationsWithMethod($prev, $method_declaration);}
    | %empty {$$ = new EmptyDeclarations();};

method_declaration:
    "public" type IDENTIFIER "(" method_args ")" "{" body "}" {$$ = new MethodDeclaration($type, $IDENTIFIER, $method_args, $body);};

variable_declaration:
    type IDENTIFIER ";" {$$ = new VariableDeclaration($type, $IDENTIFIER);};

method_args:
    %empty {$$ = new EmptyMethodArgs();}
    | method_arg {$$ = new SingleMethodArg($method_arg);}
    | method_multiple_arg "," method_arg  {$$ = new MoreThanOneMethodArgs($method_multiple_arg, $method_arg);};

method_arg:
    type IDENTIFIER {$$ = new  Method_arg($type, $IDENTIFIER);};

method_multiple_arg:
    method_arg {$$ = new LastMethodArg($method_arg);}
    | method_multiple_arg[prev] "," method_arg {$$ = new NotLastMethodArgs($prev, $method_arg);};

type:
    simple_type {$$ = new SimpleType($simple_type);}
    | simple_type "[]" {$$ = new ArrayType($simple_type);};

simple_type:
    "int" {$$ = new std::string("int");}
    | "bool" {$$ = new std::string("bool");}
    | "void" {$$ = new  std::string("void");}
    | IDENTIFIER {$$ = $IDENTIFIER;};

body:
    statements {$$ = new Body($statements);};


statements:   
    %empty {$$ = new EmptyStatements();}
    | statements[prev] statement  {$$ = new NotEmptyStatements($prev, $statement);};


statement:
    "if" "(" expr ")" statement[true] "else" statement[else] {$$ = new IfElseStatement($expr, $true, $else);}
    | "if" "(" expr ")" statement[true] %prec "then" {$$ = new IfStatement($expr, $true);}
    | "assert" "(" expr ")" ";" {$$ = new AssertStatement($expr);}
    | variable_declaration {$$ = new VarDeclStatement($variable_declaration);}
    | "{" body "}" {$$ = new ScopeStatement($body);}
    | "while" "(" expr ")" statement[true] {$$ = new WhileStatement($expr, $true);}
    | "System.out.println" "(" expr ")" ";" {$$ = new PrintStatement($expr);}
    | assignment ";" {$$ = new AssignmentStatement($assignment);}
    | "return" expr ";" {$$ = new ReturnStatement($expr);}
    | method_invocation ";" {$$ = new MethodInvocationStatement($method_invocation);};


assignment:
    expr[lvalue] "=" expr[rvalue] {$$ = new Assignment($lvalue, $rvalue);};

method_invocation:
    expr "." IDENTIFIER "(" expressions ")" {$$ = new MethodInvocation($expr, $IDENTIFIER, $expressions);}
    | "this." IDENTIFIER "(" expressions ")" {$$ = new MethodInvocation(new ThisExpr(), $IDENTIFIER, $expressions);};

field_invocation:
    "this." IDENTIFIER {$$ = new FieldInvocation($IDENTIFIER);};

expressions:
    %empty {$$ = new EmptyExpressions();}
    | expr {$$ = new SingleExpression($expr);}
    | multiple_expressions "," expr {$$ = new MoreThanOneExpression($multiple_expressions, $expr);};

multiple_expressions:
    expr  {$$ = new LastExpression($expr);}
    | multiple_expressions[prev] "," expr  {$$ = new NotLastExpressions($prev, $expr);};

expr:
    value {$$ = new ValueExpr($value);}
    | IDENTIFIER {$$ = new IdExpr($IDENTIFIER);}
    | expr[arr] "[" expr[index] "]" {$$ = new ArrayElementExpr($arr, $index);}
    | expr[arr] "." "length" {$$ = new LengthExpr($arr);}
    | "new" simple_type "[" expr[index] "]" {$$ = new NewArrayExpr($simple_type, $index);}
    | "new" IDENTIFIER "(" ")" {$$ = new NewSingleExpr($IDENTIFIER);}
    | "!" expr[neg] {$$ = new NotExpr($neg);}
    | expr[first] "+" expr[second] {$$ = new PlusExpr($first, $second);}
    | expr[first] "-" expr[second] {$$ = new MinusExpr($first, $second);}
    | expr[first] "*" expr[second] {$$ = new MulExpr($first, $second);}
    | expr[first] "/" expr[second] {$$ = new DivExpr($first, $second);}
    | expr[first] "%" expr[second] {$$ = new PercentExpr($first, $second);}
    | expr[first] "&&" expr[second] {$$ = new AndExpr($first, $second);}
    | expr[first] "||" expr[second] {$$ = new OrExpr($first, $second);}
    | expr[first] "<" expr[second] {$$ = new SmallerExpr($first, $second);}
    | expr[first] ">" expr[second] {$$ = new BiggerExpr($first, $second);}
    | expr[first] "==" expr[second] {$$ = new EqualExpr($first, $second);}
    | expr[first] "!=" expr[second] {$$ = new NotEqualExpr($first, $second);}
    | "(" expr[in] ")" {$$ = new BracketsExpr($in);}
    | method_invocation {$$ = new MethodInvocationExpr($method_invocation);}
    | field_invocation {$$ = new FieldInvocationExpr($field_invocation);};

value:
    NUMBER {$$ = new IntValue($NUMBER);}
    | "true" {$$ = new BoolValue(true);}
    | "false" {$$ = new BoolValue(false);};
   

%%

void yy::parser::error(const std::string& str)
{
    std::cerr << "Syntax Error: " << str << '\n';
}

