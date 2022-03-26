#include <stdio.h>
#include <stdlib.h>


#include "stacks.h"

/**
	Description: 
		初始化。静态创建 
	Arguments:
		nothing
	Returns:
		1:	success
		3:	内存申请失败 
*/
c8 InitStacks(Stacks* stack){
	c8 sta;
	sta = CreateArrayList(&(stack->sta_arr),7);
	if ( sta != ARR_OK )
		return sta;
	(*stack).ifInital = 1;
	(*stack).name = "stack_def";
	(*stack).INSERT_sta = insert_stack;
	(*stack).COUNT = count_sta;
	(*stack).POP_sta = pop_sta;
	(*stack).FREE = free_sta;
	(*stack).PRINT = print_sta;
	
	return ARR_OK;
}


/**
	Description: 
		初始化。动态创建 
	Arguments:
		nothing
	Returns:
		1:	success
		3:	内存申请失败 
*/
c8 CreateStacks(Stacks** stack){
	*stack = (Stacks*)SD_MALLOC(sizeof(Stacks));
	if (*stack == (Stacks*)0)	return ARR_MALLOC_FAIL;
	
	if (InitStacks(*stack) == ARR_MALLOC_FAIL){
		SD_FREE(*stack);
		return ARR_MALLOC_FAIL;
	}
	return ARR_OK;
}

/**
	Description: 
		入栈 
	Arguments:
		void* ele:	入栈元素的地址 
	Returns:
		1: ARR_OK 			success
		-5:ARR_UN_INIT		栈未初始化 
		3: ARR_MALLOC_FAIL	分配内存失败 
		2: ARR_MOVE_FAIL	复制失败
*/
c8 insert_stack(Stacks* stack,void* ele){
	c8 sta;
	if ((*stack).ifInital == 0)
		return ARR_UN_INIT;
	
	sta = add_list(stack->sta_arr,ele);
	if (sta != ARR_OK)
		return sta;
		
	return ARR_OK;
}

/**
	Description: 
		返回栈的元素个数 
	Arguments:
		nothing
	Returns:
		-5:	栈未初始化
		X:	元素个数 
*/
int count_sta(Stacks *stack){
	if ((*stack).ifInital == 0)
		return ARR_UN_INIT;

    return (stack->sta_arr)->length;
}

/**
	Description: 
		出栈 
	Arguments:
		nothing
	Returns:
		-5: 栈未初始化
		0:	无元素，空指针
		X:	元素地址 
*/
void* pop_sta(Stacks *stack){
	void* res;
	if ((*stack).ifInital == 0)
		return (void*)ARR_UN_INIT;

	if (count_sta(stack) == 0)
		return NULL_void;
	
    res = get_list(stack->sta_arr,(stack->sta_arr)->length - 1);
	if (res == (void*)ARR_WRONG_INDEX)
		return res;
	
    (stack->sta_arr)->length --;
	return res;
}

/**
	Description: 
		释放栈内存，用于动态创建的栈 
	Arguments:
		nothing
	Returns:
		none
*/
void free_sta(Stacks *stack){
	if ((*stack).ifInital == 1)
		free_arr(stack->sta_arr);
	SD_FREE(stack);
}

void print_sta(Stacks *stack){
	SD_PRINT_HEAD("Stacks",stack->name);
	SD_PRINT("=>stack=>ifinitial:	%d",stack->ifInital);
	print_arr_main(stack->sta_arr);
	SD_PRINT_END;
}
