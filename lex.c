
typedef struct {
	char *text;
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
} Keyword;

typedef struct {
	TokenType type;
	char *value;
} Token;
