#include <stdio.h>
#include "iterators.h"


///////////////////////////iters for Arraylist


/**
	Description: 
		初始化 ITER_4ARRAY结构体 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY类型的变量的地址 
		ArrayList* arr： ArrayList类型的数组的地址 
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
		是否是末节点 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY类型的变量的地址 
	Returns:
		-5: ARR_UN_INIT: 未初始化
		1：还有下一个
		0：没有下一个 
*/
c8 hasNext_4array(ITER_4ARRAY* iter){
	if (iter->ifInital != 1)
		return ARR_UN_INIT; 
		
	return iter->pos < iter->array->length;
}

/**
	Description: 
		逆序输出的下一个节点的地址 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY类型的变量的地址 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind下标不合法
		-5: ARR_UN_INIT: 未初始化
		x：地址 
*/
void* next_reverse_4array(ITER_4ARRAY* iter){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
		
	int ind = iter->array->length - 1 - iter->pos;
	iter->pos++;
	
	return get_list(iter->array, ind);
}





