#ifndef __CIRQUEUE_H__
#define __CIRQUEUE_H__

#include "arraylist.h"

typedef struct cirqueues {
	char *name;
	ArrayList* cq_arr;
	int front;
	int rear;
	int size;
	c8 (*ENQUEUE_cq)(struct cirqueues*,void*);
	void* (*DEQUEUE_cq)(struct cirqueues*);
	int (*COUNT)(struct cirqueues*);
	void (*FREE)(struct cirqueues*);
	void (*PRINT)(struct cirqueues*);
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

#endif

