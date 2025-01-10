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
int AddTransition(DFA *automaton, char c, int state1, int state2);
DFA *NewDFA(Arena *parent, int accepting[], int acclen, int transitions[], int size);

#endif
