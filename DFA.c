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

typedef struct {
	int dest;
	char transition;
} DFATransition;

typedef struct {
	DFATransition **transitions;
	int size;
	int *accepting;
	int acclen;
} DFA;

int isaccepting(DFA *automaton, int state);

int accepts(DFA *automaton, int state, const char *string, int count) {
	int i = 0;
	char c;
	while ((i < automaton->size) && ((c = automaton->transitions[state][i].transition) != string[0]))
		i++;
	if (c == string[0])
		return accepts(automaton, i, string, count+1);
	else if (isaccepting(automaton, state))
		return count;
	else
		return 0;
}

int isaccepting(DFA *automaton, int state) {
	int i = 0;
	while ((i < automaton->acclen) && (state != automaton->accepting[i]))
		i++;
	if (state == automaton->accepting[i])
		return 1;
	return 0;
}

DFA *NewDFA(int states, int *accepting, int acclen) {
	DFA *
