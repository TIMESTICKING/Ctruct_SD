#ifndef __STACKS_H__
#define __STACKS_H__

#include "arraylist.h"

typedef struct stacks {
	ArrayList sta_arr;
	char *name;
	c8 (*INSERT_sta)(struct stacks*,void*);
	int (*COUNT_sta)(struct stacks*);
	void* (*POP_sta)(struct stacks*);
	void (*FREE_sta)(struct stacks*);
	void (*PRINT_sta)(struct stacks*);
	c8 ifInital;
}Stacks;


c8 InitStacks(Stacks* stack);
c8 CreateStacks(Stacks** stack);
c8 insert_stack(Stacks* stack,void* ele);
void* pop_sta(Stacks *stack);
int count_sta(Stacks *stack);
void free_sta(Stacks *stack);
void print_sta(Stacks *stack);

#endif

