#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DFA.h"
#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) < (b)) ? (b) : (a))

typedef struct {
	char text[];
	int pos;
} Scanner;

typedef enum {
	KEYWORD,
	IDENTIFIER,
	CONSTANT,
	STRINGLITERAL,
	OPERATOR,
	PUNCTUATOR,
	HEADERNAME,
	PPNUMBER,
	CHARACTERCONSTANT,
} TokenType;

typedef enum {
	AUTO,
	BREAK,
	CASE,
	CHAR,
	CONST,
	CONTINUE,
	DEFAULT,
	DO,
	DOUBLE,
	ELSE,
	ENUM,
	EXTERN,
	FLOAT,
	FOR,
	GOTO,
	IF,
	INT,
	LONG,
	REGISTER,
	RETURN,
	SHORT,
	SIGNED,
	SIZEOF,
	STATIC,
	STRUCT,
	SWITCH,
	TYPEDEF,
	UNION,
	UNSIGNED,
	VOID,
	VOLATILE,
	WHILE,
} Keyword;

typedef struct {
	TokenType type;
	char *value;
} Token;

int KeywordMatch(char s[]) {
	char keywords[][32] = {
		"auto", "break", "case", "char", 
		"const", "continue", "default", "do",
		"double", "else", "enum", "extern",
		"float", "for", "goto", "if",
		"int", "long", "register", "return",
		"short", "signed", "sizeof", "static",
		"struct", "switch", "typedef", "union",
		"unsigned", "void", "volatile", "while"}
	int i = 0;
	int ret;
	while ((ret = strncmp(s, keywords[i], 8)) && (i < 32))
		i++;
	return ret;
}

int IdentifierMatch(char s[], Arena scratch) {
	int transitions[2][128];
	int accepting = 1;
	DFA *IdentifierDFA = NewDFA(&scratch, &accepting, 1, transitions, 2);
	for (char c = 'a'; c <= 'z'; c++) {
		AddTransition(IdentifierDFA, c, 0, 1);
		AddTransition(IdentifierDFA, c, 1, 1);
	}
	for (char c = 'A'; c <= 'Z'; c++) {
		AddTransition(IdentifierDFA, c, 0, 1);
		AddTransition(IdentifierDFA, c, 1, 1);
	}
	for (char c = '0'; c <= '9'; c++)
		AddTransition(IdentifierDFA, c, 0, 1);
	AddTransition(IdentifierDFA, '_', 1, 1);
	AddTransition(IdentifierDFA, '_', 0, 1);
	return accepts(IdentifierDFA, 0, s, 0);
}

int ConstantMatch(char s[], Arena scratch) {
	int f = FloatingMatch(s, scratch);
	int n = IntegerMatch(s, scratch);
	int e = EnumerationMatch(s, scratch);
	int c = CharacterMatch(s, scatch);
	return max(max(f, n), max(e, c));
}

int FloatingMatch(char s[], Arena scratch) {
	int
