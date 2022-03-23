#include <stdio.h>
#include "iterators.h"
#include <stdarg.h>

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
	switch(type){
		case ITERTYPE_REVERSE_4ARRAY:
			// 逆序 
			iter->next = next_reverse_4array;
			iter->hasNext = hasNext_4array;
			break;
		case ITERTYPE_2DIVSION_4ARRAY:
			// 二分
			iter->temp = INTarr_new(2);
			(iter->temp)[0] = 0;
			(iter->temp)[1] = arr->length - 1;
			iter->pos = (arr->length - 1) / 2;
			iter->next = next_2divsion_4array;
			iter->hasNext = hasNext_2div_4array;
			break; 
		case ITERTYPE_POSI_SEQ_4ARRAY:
			//正序 
			iter->next = next_4array;
			iter->hasNext = hasNext_4array;
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
void* next_reverse_4array(ITER_4ARRAY* iter,...){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
		
	int ind = -1 - iter->pos;
	iter->pos++;
	
	return get_list(iter->array, ind);
}


/**
	Description: 
		顺序输出的下一个节点的地址 
	Arguments:
		ITER_4ARRAY* iter:	ITER_4ARRAY类型的变量的地址 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind下标不合法
		-5: ARR_UN_INIT: 未初始化
		x：地址 
*/
void* next_4array(ITER_4ARRAY* iter,...){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
	
	return get_list(iter->array, iter->pos++);
}

/**
	Description: 
		是否有下一个（二分遍历） 
	Arguments:
		ITER_4ARRAY* iter：迭代器地址
		int direction：向左分支走还是右分支，取值：
					ITERDIREC_LEFT=-1，ITERDIREC_INIT=0，ITERDIREC_RIGHT=1 
	Returns:
		-5  ARR_UN_INIT： 未初始化
		0：无下一个
		1：有下一个 
*/
c8 hasNext_2div_4array(ITER_4ARRAY* iter, int direction){
	if (iter->ifInital != 1)
		return ARR_UN_INIT; 
	
	int *temp = iter->temp;
	return (temp[1] >= temp[0]);
}


/**
	Description: 
		二分遍历的下一个值 
	Arguments:
		ITER_4ARRAY* iter：迭代器地址
		int direction：向左分支走还是右分支，取值：
					ITERDIREC_LEFT=-1，ITERDIREC_INIT=0，ITERDIREC_RIGHT=1 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind下标不合法
		-5:	ARR_UN_INIT 	列表未初始化 
		X:	元素地址 
*/
void* next_2divsion_4array(ITER_4ARRAY* iter, int direction){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 

	int *temp = iter->temp;
	if (direction==-1){
		// 往左找 
		temp[1] = iter->pos - 1;
	}else if (direction==1){
		// 往右找
		temp[0] = iter->pos + 1;
	}
	iter->pos = (temp[0] + temp[1]) / 2;

	return get_list(iter->array, iter->pos);;
}





