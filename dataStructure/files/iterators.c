#include <stdio.h>
#include "iterators.h"
#include <stdarg.h>

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
	switch(type){
		case ITERTYPE_REVERSE_4ARRAY:
			// ���� 
			iter->next = next_reverse_4array;
			iter->hasNext = hasNext_4array;
			break;
		case ITERTYPE_2DIVSION_4ARRAY:
			// ����
			iter->temp = INTarr_new(2);
			(iter->temp)[0] = 0;
			(iter->temp)[1] = arr->length - 1;
			iter->pos = (arr->length - 1) / 2;
			iter->next = next_2divsion_4array;
			iter->hasNext = hasNext_2div_4array;
			break; 
		case ITERTYPE_POSI_SEQ_4ARRAY:
			//���� 
			iter->next = next_4array;
			iter->hasNext = hasNext_4array;
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
void* next_reverse_4array(ITER_4ARRAY* iter,...){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
		
	int ind = -1 - iter->pos;
	iter->pos++;
	
	return get_list(iter->array, ind);
}


/**
	Description: 
		˳���������һ���ڵ�ĵ�ַ 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY���͵ı����ĵ�ַ 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind�±겻�Ϸ�
		-5: ARR_UN_INIT: δ��ʼ��
		x����ַ 
*/
void* next_4array(ITER_4ARRAY* iter,...){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
	
	return get_list(iter->array, iter->pos++);
}

/**
	Description: 
		�Ƿ�����һ�������ֱ����� 
	Arguments:
		ITER_4ARRAY* iter����������ַ
		int direction�������֧�߻����ҷ�֧��ȡֵ��
					ITERDIREC_LEFT=-1��ITERDIREC_INIT=0��ITERDIREC_RIGHT=1 
	Returns:
		-5  ARR_UN_INIT�� δ��ʼ��
		0������һ��
		1������һ�� 
*/
c8 hasNext_2div_4array(ITER_4ARRAY* iter, int direction){
	if (iter->ifInital != 1)
		return ARR_UN_INIT; 
	
	int *temp = iter->temp;
	return (temp[1] >= temp[0]);
}


/**
	Description: 
		���ֱ�������һ��ֵ 
	Arguments:
		ITER_4ARRAY* iter����������ַ
		int direction�������֧�߻����ҷ�֧��ȡֵ��
					ITERDIREC_LEFT=-1��ITERDIREC_INIT=0��ITERDIREC_RIGHT=1 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind�±겻�Ϸ�
		-5:	ARR_UN_INIT 	�б�δ��ʼ�� 
		X:	Ԫ�ص�ַ 
*/
void* next_2divsion_4array(ITER_4ARRAY* iter, int direction){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 

	int *temp = iter->temp;
	if (direction==-1){
		// ������ 
		temp[1] = iter->pos - 1;
	}else if (direction==1){
		// ������
		temp[0] = iter->pos + 1;
	}
	iter->pos = (temp[0] + temp[1]) / 2;

	return get_list(iter->array, iter->pos);;
}





