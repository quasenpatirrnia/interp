#include "alloc.h"

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

DFA *NewDFA(Arena *parent, int size, int *accepting, int acclen) {
	DFA *ret = (DFA *)PushToArena(parent, size * size);
	ret->accepting = accepting;
	ret->acclen = acclen;
	return ret;
}
