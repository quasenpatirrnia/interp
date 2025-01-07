#ifndef ALLOC_H
#define ALLOC_H

typedef struct {
	void *content;
	void *stackptr;
	int size;
} Arena;

Arena *CreateArena(int size);
void DestroyArena(Arena *arena);
int ArenaUsed(Arena *arena);
void *PushToArena(Arena *arena, int bytes);
void FreeArena(Arena *arena, int bytes);

#endif
