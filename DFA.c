#include "alloc.h"

typedef struct {
	int **transitions;
	int size;
	int *accepting;
	int acclen;
} DFA;

int isaccepting(DFA *automaton, int state);

int accepts(DFA *automaton, int state, const char *string, int count) {
	int trans;
	if ((trans = automaton->transitions[state][(int)*string]) > 0)
		return accepts(automaton, trans-1, string+1, count+1);
	if (isaccepting(automaton, state))
		return count;
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
	DFA *ret = (DFA *)PushToArena(parent, sizeof(DFA));
	ret->accepting = accepting;
	ret->acclen = acclen;
	return ret;
}
