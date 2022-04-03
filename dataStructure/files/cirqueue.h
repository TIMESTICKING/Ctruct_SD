#ifndef __CIRQUEUE_H__
#define __CIRQUEUE_H__

#include "arraylist.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef struct cirqueues {
	char *name;
	ArrayList cq_arr;
	int front;
	int rear;
	int size;
	c8 (*ENQUEUE_cq)(struct cirqueues*,void*);
	void* (*DEQUEUE_cq)(struct cirqueues*);
	int (*COUNT_cq)(struct cirqueues*);
	void (*FREE_cq)(struct cirqueues*);
	void (*PRINT_cq)(struct cirqueues*);
	c8 ifInital;
}CirQueues;


c8 InitCirQueue(CirQueues *cq,int size);
c8 CreateCirQueue(CirQueues **cq,int size);
c8 enqueue_cq(CirQueues *cq,void *ele);
void* dequeue_cq(CirQueues *cq);
int count_cq(CirQueues *cq);
void free_cq(CirQueues *cq);
void print_cq(CirQueues *cq);


static c8 isFull(CirQueues *cq);
static c8 isEmpty(CirQueues *cq);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif

