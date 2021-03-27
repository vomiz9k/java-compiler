#pragma once
#ifndef LEXER
#define LEXER
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type Lexer::ScanToken()

#include <bison.hpp>





class Driver;

class Lexer: public yyFlexLexer {
 public:
    Lexer(Driver& driver): driver(driver) {}
	virtual ~Lexer() {}
	virtual yy::parser::symbol_type ScanToken();
    Driver &driver;
};
#endif