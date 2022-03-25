#include <stdio.h>
#include <stdlib.h>
#include "cirqueue.h"

/**
	Description: 
		��̬��ʼ��ѭ������ 
	Arguments:
		int size:	����������һ���趨������䶯 
	Returns:
		1: success
		3:	�ڴ�����ʧ�� 
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
		��̬����ѭ������ 
	Arguments:
		int size:	���� 
	Returns:
		1: success
		3: �ڴ�����ʧ�� 
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

//�Ƿ���� 
static c8 isFull(CirQueues *cq){
	return ((cq->rear + 1)%cq->size == cq->front);
}

//�Ƿ�ӿ� 
static c8 isEmpty(CirQueues *cq){
	return (cq->front == -1 || cq->rear == -1);
}


/**
	Description: 
		��� 
	Arguments:
		void *ele: ���Ԫ�صĵ�ַ 
	Returns:
		1: success
		0:	���� 
		-5: ����δ��ʼ��
		-1: ���ʱ�±곬�����г���
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
	//�޸ĳɹ�,rear++ 
	cq->rear = (cq->rear + 1) % cq->size;
	if (isEmpty(cq)){//��������ǲ��Ǵӿնӹ����� 
		cq->front = 0;
	}
	return ARR_OK;
}

/**
	Description: 
		���� 
	Arguments:
		nothing
	Returns:
		-5: ����δ��ʼ��
		0:	����Ϊ�� 
		-1:	ȡ���ݵ��±곬�����г��� 
		X:	Ԫ�ص�ַ 
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
		//ֻ��һ��Ԫ�أ�ֱ�ӱ�ɿն�-1,-1 
		cq->front = -1;
		cq->rear = -1;
	}else{
		cq->front = (cq->front + 1) % cq->size;
	}
	return temp;
}

/**
	Description: 
		�����е�Ԫ�ظ��� 
	Arguments:
		nothing
	Returns:
		-5:	����δ��ʼ��
	 	X:	Ԫ�ظ��� 
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
		�ͷŶ��� 
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
