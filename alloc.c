#include <stdio.h>
#include <stdlib.h>

typedef struct {
	void *content;
	void *stackptr;
	int size;
} Arena;

Arena *CreateArena(int size) {
	Arena *ret = (Arena *)malloc(sizeof(Arena));
	ret->content == malloc(size);
	ret->stackptr = ret->content;
	ret->size = size;
	return ret;
}

void DestroyArena(Arena *arena) {
	free(arena->content);
	free(arena);
}

int ArenaUsed(Arena *arena) {
	return (arena->stackptr - arena->content);
}

void *PushToArena(Arena *arena, int bytes) {
	if ((ArenaUsed(arena) + bytes) > arena->size)
		return NULL;
	return(arena->stackptr += bytes);
}

void FreeArena(Arena *arena, int bytes) {
	PushToArena(arena, -bytes);
}
