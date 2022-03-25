#include <stdio.h>
#include <stdlib.h>
#include "cirqueue.h"

/**
	Description: 
		静态初始化循环队列 
	Arguments:
		int size:	队列容量，一旦设定将不会变动 
	Returns:
		1: success
		3:	内存申请失败 
*/
c8 InitCirQueue(CirQueues *cq,int size){
	c8 sta;
	sta = CreateArrayList(&(cq->cq_arr),size);
	if ( sta != ARR_OK )
		return sta;
    (cq->cq_arr)->length = size;
	cq->front = -1;
	cq->rear = -1;
	cq->size= size;
	cq->ifInital = 1;
	cq->name = "cirqueue_def";
	cq->ENQUEUE_cq = enqueue_cq;
	cq->DEQUEUE_cq = dequeue_cq;
	cq->COUNT_cq = count_cq;
	cq->FREE_cq = free_cq;
	cq->PRINT_cq = print_cq;
	
	return ARR_OK;
}


/**
	Description: 
		动态创建循环队列 
	Arguments:
		int size:	容量 
	Returns:
		1: success
		3: 内存申请失败 
*/
c8 CreateCirQueue(CirQueues **cq,int size){
	*cq = (CirQueues*)SD_MALLOC(sizeof(CirQueues));
	if (*cq == (CirQueues*)0) return ARR_MALLOC_FAIL;
	
	if (InitCirQueue(*cq,size) != ARR_OK){
		SD_FREE(*cq);
		return ARR_MALLOC_FAIL;
	}
	
	return ARR_OK;
}

//是否队满 
static c8 isFull(CirQueues *cq){
	return ((cq->rear + 1)%cq->size == cq->front);
}

//是否队空 
static c8 isEmpty(CirQueues *cq){
	return (cq->front == -1 || cq->rear == -1);
}


/**
	Description: 
		入队 
	Arguments:
		void *ele: 入队元素的地址 
	Returns:
		1: success
		0:	队满 
		-5: 队列未初始化
		-1: 入队时下标超出队列长度
*/
c8 enqueue_cq(CirQueues *cq,void *ele){
	c8 sta;
	if (cq->ifInital != 1)
		return ARR_UN_INIT;
		
	if (isFull(cq)){
		return ARR_FALSE;
	}
	
	sta = edit_list(cq->cq_arr,(cq->rear + 1) % cq->size,ele);
	if ( sta != ARR_OK ){
		return sta;
	}
	//修改成功,rear++ 
	cq->rear = (cq->rear + 1) % cq->size;
	if (isEmpty(cq)){//本次入队是不是从空队过来的 
		cq->front = 0;
	}
	return ARR_OK;
}

/**
	Description: 
		出队 
	Arguments:
		nothing
	Returns:
		-5: 队列未初始化
		0:	队列为空 
		-1:	取数据的下标超出队列长度 
		X:	元素地址 
*/
void* dequeue_cq(CirQueues *cq){
	void* temp;
	c8 sta;
	if (cq->ifInital != 1)
		return (void*)ARR_UN_INIT;
		
	if (isEmpty(cq)){
		return NULL_void;
	}
	temp = get_list(cq->cq_arr,cq->front);
	if (temp == (void*)ARR_WRONG_INDEX)
		return (void*)ARR_WRONG_INDEX;
		
	if (cq->front == cq->rear){
		//只有一个元素，直接变成空队-1,-1 
		cq->front = -1;
		cq->rear = -1;
	}else{
		cq->front = (cq->front + 1) % cq->size;
	}
	return temp;
}

/**
	Description: 
		队列中的元素个数 
	Arguments:
		nothing
	Returns:
		-5:	队列未初始化
	 	X:	元素个数 
*/
int count_cq(CirQueues *cq){
	if (cq->ifInital != 1)
		return ARR_UN_INIT;
		
	if (isEmpty(cq))
		return 0;
	return (cq->rear - cq->front + cq->size) % cq->size + 1;
}

/**
	Description: 
		释放队列 
	Arguments:
		nothing
	Returns:
		none
*/
void free_cq(CirQueues *cq){
	if (cq->ifInital == 1)
		free_arr(cq->cq_arr);
	SD_FREE(cq);
}

void print_cq(CirQueues *cq){
	SD_PRINT_HEAD("CirqQueues",cq->name);
	SD_PRINT("=>cirqueue=>ifinitial:	%d",cq->ifInital);
	SD_PRINT("=>cirqueue=>size:	%d",cq->size);
	SD_PRINT("=>cirqueue=>count:	%d",cq->COUNT_cq(cq));
	SD_PRINT("=>cirqueue=>front:	%d",cq->front);
	SD_PRINT("=>cirqueue=>rear:	%d",cq->rear);
	print_arr_main(cq->cq_arr);
	SD_PRINT_END;
}
