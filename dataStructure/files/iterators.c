#include <stdio.h>
#include "iterators.h"
#include <stdarg.h>

///////////////////////////iters for Arraylist


/**
	Description: 
		init ITER_4ARRAY struct
	Arguments:
		ITER_4ARRAY* iter: address of a var which has type ITER_4ARRAY
		ArrayList* arr£ºaddress of a list which has type ArrayList
	Return:
		1: ARR_OK
*/
c8 InitITER_4array(ITER_4ARRAY* iter, ArrayList* arr, ENUM_ITERTYPE_4ARRAY type){
	iter->array = arr;
	iter->pos = 0;
	iter->ifInital = 1;
	switch(type){
		case ITERTYPE_REVERSE_4ARRAY:
			// inverse sequence
			iter->next = next_reverse_4array;
			iter->hasNext = hasNext_4array;
			break;
		case ITERTYPE_2DIVSION_4ARRAY:
			// 2divsion sequence
			iter->temp = INTarr_new(2);
			(iter->temp)[0] = 0;
			(iter->temp)[1] = arr->length - 1;
			iter->pos = (arr->length - 1) / 2;
			iter->next = next_2divsion_4array;
			iter->hasNext = hasNext_2div_4array;
			break; 
		case ITERTYPE_POSI_SEQ_4ARRAY:
			//positive sequence
			iter->next = next_4array;
			iter->hasNext = hasNext_4array;
	}

	
	return ARR_OK;
}


/**
	Description: 
		is it the last node
	Arguments:
		ITER_4ARRAY* iter: address of a var which has type ITER_4ARRAY
	Returns:
		-5: ARR_UN_INIT: not inited
		1£ºhas next
		0£ºno next
*/
c8 hasNext_4array(ITER_4ARRAY* iter){
	if (iter->ifInital != 1)
		return ARR_UN_INIT; 
		
	return iter->pos < iter->array->length;
}

/**
	Description: 
		give out the addr of next node in inverse sequence
	Arguments:
		ITER_4ARRAY* iter:	address of a var which has type ITER_4ARRAY
	Returns:
		-1:	ARR_WRONG_INDEX  illegal index of array
		-5: ARR_UN_INIT: no inited
		x£ºaddr
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
		give out the addr of next node in positive sequence
	Arguments:
		ITER_4ARRAY* iter: address of a var which has type ITER_4ARRAY
	Returns:
		-1:	ARR_WRONG_INDEX  illegal index of array
		-5: ARR_UN_INIT: no inited
		x£ºaddr
*/
void* next_4array(ITER_4ARRAY* iter,...){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 
	
	return get_list(iter->array, iter->pos++);
}

/**
	Description: 
		does it has next(2divsion iteration)
	Arguments:
		ITER_4ARRAY* iter£ºaddress of a var which has type ITER_4ARRAY
		int direction£ºgo to the right branch or left, values can be
					ITERDIREC_LEFT=-1£¬ITERDIREC_INIT=0£¬ITERDIREC_RIGHT=1 
	Returns:
		-5  ARR_UN_INIT£ºnot inited
		0£ºno next
		1£ºhas next
*/
c8 hasNext_2div_4array(ITER_4ARRAY* iter, int direction){
	if (iter->ifInital != 1)
		return ARR_UN_INIT; 
	
	int *temp = iter->temp;
	return (temp[1] >= temp[0]);
}


/**
	Description: 
		next value in 2divsion
	Arguments:
		ITER_4ARRAY* iter£ºaddress of a var which has type ITER_4ARRAY
		int direction£ºgo to the right branch or left, values can be
					ITERDIREC_LEFT=-1£¬ITERDIREC_INIT=0£¬ITERDIREC_RIGHT=1 
	Returns:
		-1:	ARR_WRONG_INDEX   illegal index
		-5:	ARR_UN_INIT      list no inited
		X: addr of ele
*/
void* next_2divsion_4array(ITER_4ARRAY* iter, int direction){
	if (iter->ifInital != 1)
		return (void*)ARR_UN_INIT; 

	int *temp = iter->temp;
	if (direction==-1){
		// looking in left
		temp[1] = iter->pos - 1;
	}else if (direction==1){
		// looking in right
		temp[0] = iter->pos + 1;
	}
	iter->pos = (temp[0] + temp[1]) / 2;

	return get_list(iter->array, iter->pos);;
}





