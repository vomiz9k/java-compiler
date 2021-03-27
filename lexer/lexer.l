%option noyywrap nounput noinput batch debug
%option c++
%option yyclass="Lexer"
%{
    #include <string>
    #include <string.h>
    #include <iostream>
    #include <driver.hpp>
    #include <bison.hpp>

%}



identifier     [_a-zA-Z][_a-zA-Z0-9]*
number         [0-9]+


%%


[\n]+               {}

[ \t\r]+            {}

"class"             {
                        return yy::parser::make_CLASS ();
                    }

"public"            {
                        return yy::parser::make_PUBLIC ();
                    }

"static"            {
                        return yy::parser::make_STATIC ();
                    }

"void"              {
                        return yy::parser::make_VOID ();
                    }

"main"              {
                        return yy::parser::make_MAIN ();
                    }

"extends"           {
                        return yy::parser::make_EXTENDS ();
                    }

"if"                {
                        return yy::parser::make_IF ();
                    }


"else"              {
                        return yy::parser::make_ELSE ();
                    }

"while"             {
                        return yy::parser::make_WHILE ();
                    }

"System.out.println" {
                        return yy::parser::make_SOP ();
                    }

"assert"            {
                        return yy::parser::make_ASSERT ();
                    }

"return"            {
                        return yy::parser::make_RETURN ();
                    }

"bool"              {
                        return yy::parser::make_BOOL ();
                    }

"int"               {
                        return yy::parser::make_INT ();
                    }

"length"            {
                        return yy::parser::make_LENGTH ();
                    }

"this"              {
                        return yy::parser::make_THIS ();
                    }

"new"               {
                        return yy::parser::make_NEW();
                    }

"true"              {
                        return yy::parser::make_TRUE ();
                    }

"false"             {
                        return yy::parser::make_FALSE ();
                    }



"("                 {
                        return yy::parser::make_LBRACKET ();
                    }

")"                 {
                        return yy::parser::make_RBRACKET ();
                    }  

"{"                 {
                        return yy::parser::make_LFBRACKET ();
                    }

"}"                 {
                        return yy::parser::make_RFBRACKET ();
                    }

"[]"                {
                        return yy::parser::make_ARRAY_DECL_BRACKETS ();
                    }

"["                 {
                        return yy::parser::make_LSBRACKET ();
                    }

"]"                 {
                        return yy::parser::make_RSBRACKET ();
                    }

">"                 {
                        return yy::parser::make_BIGGER ();
                    }
                
"<"                 {
                        return yy::parser::make_SMALLER ();
                    }

"=="                {
                        return yy::parser::make_EQUAL ();
                    }

"!="                {
                        return yy::parser::make_NOT_EQUAL ();
                    }

"="                 {
                        return yy::parser::make_ASSIGN ();
                    }

"+"                 {
                        return yy::parser::make_PLUS ();
                    }
                
"-"                 {
                        return yy::parser::make_MINUS ();
                    }

"*"                 {
                        return yy::parser::make_STAR ();
                    }  

"/"                 {
                        return yy::parser::make_SLASH ();
                    }

"%"                 {
                        return yy::parser::make_PERCENT ();
                    }    



";"                 {
                        return yy::parser::make_SEMICOLON ();
                    }     

"."                 {
                        return yy::parser::make_POINT ();
                    }

","                 {
                        return yy::parser::make_COMMA ();
                    }

"&&"                {
                        return yy::parser::make_LOGIC_AND ();
                    }

"||"                {
                        return yy::parser::make_LOGIC_OR ();
                    }

"!"                {
                        return yy::parser::make_LOGIC_NOT ();
                    }




{number}            {
                        return yy::parser::make_NUMBER (atoi(yytext));
                    }

{identifier}        {
                        return yy::parser::make_IDENTIFIER (new std::string(yytext));
                    }

<<EOF>>             {
                        return yy::parser::make_END ();
                    }



%%

