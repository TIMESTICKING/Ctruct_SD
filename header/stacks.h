#ifndef __STACKS_H__
#define __STACKS_H__

#include "arraylist.h"


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus


typedef struct stacks {
	ArrayList* sta_arr;
	char *name;
	c8 (*INSERT_sta)(struct stacks*,void*);
	int (*COUNT)(struct stacks*);
	void* (*POP_sta)(struct stacks*);
	void (*FREE)(struct stacks*);
	void (*PRINT)(struct stacks*);
	c8 ifInital;
}Stacks;

c8 InitStacks(Stacks* stack);
c8 CreateStacks(Stacks** stack);
c8 insert_stack(Stacks* stack,void* ele);
void* pop_sta(Stacks *stack);
int count_sta(Stacks *stack);
void free_sta(Stacks *stack);
void print_sta(Stacks *stack);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif

