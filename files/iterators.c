#include <stdio.h>
#include "iterators.h"


///////////////////////////iters for Arraylist


/**
	Description: 
		��ʼ�� ITER_4ARRAY�ṹ�� 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY���͵ı����ĵ�ַ 
		ArrayList* arr�� ArrayList���͵�����ĵ�ַ 
	Return:
		1: ARR_OK
*/
c8 InitITER_4array(ITER_4ARRAY* iter, ArrayList* arr, ENUM_ITERTYPE_4ARRAY type){
	iter->array = arr;
	iter->pos = 0;
	iter->ifInital = 1;
	iter->hasNext = hasNext_4array;
	if (type == ITERTYPE_REVERSE_4ARRAY){
		iter->next = next_reverse_4array;
	}
	
	return ARR_OK;
}


/**
	Description: 
		�Ƿ���ĩ�ڵ� 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY���͵ı����ĵ�ַ 
	Returns:
		-5: ARR_UN_INIT: δ��ʼ��
		1��������һ��
		0��û����һ�� 
*/
c8 hasNext_4array(ITER_4ARRAY* iter){
	if (iter->ifInital != 1)
		return ARR_UN_INIT; 
		
	return iter->pos < iter->array->length;
}

/**
	Description: 
		�����������һ���ڵ�ĵ�ַ 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY���͵ı����ĵ�ַ 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind�±겻�Ϸ�
		-5: ARR_UN_INIT: δ��ʼ��
		x����ַ 
*/
void* next_reverse_4array(ITER_4ARRAY* iter){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
		
	int ind = iter->array->length - 1 - iter->pos;
	iter->pos++;
	
	return get_list(iter->array, ind);
}





