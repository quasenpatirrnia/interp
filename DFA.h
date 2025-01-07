#ifndef DFA_H
#define DFA_H

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

int accepts(DFA *automaton, int state, const char *string, int count);

#endif
