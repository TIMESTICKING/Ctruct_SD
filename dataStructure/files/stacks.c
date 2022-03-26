#include <stdio.h>
#include <stdlib.h>


#include "stacks.h"

/**
	Description: 
		��ʼ������̬���� 
	Arguments:
		nothing
	Returns:
		1:	success
		3:	�ڴ�����ʧ�� 
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
		��ʼ������̬���� 
	Arguments:
		nothing
	Returns:
		1:	success
		3:	�ڴ�����ʧ�� 
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
		��ջ 
	Arguments:
		void* ele:	��ջԪ�صĵ�ַ 
	Returns:
		1: ARR_OK 			success
		-5:ARR_UN_INIT		ջδ��ʼ�� 
		3: ARR_MALLOC_FAIL	�����ڴ�ʧ�� 
		2: ARR_MOVE_FAIL	����ʧ��
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
		����ջ��Ԫ�ظ��� 
	Arguments:
		nothing
	Returns:
		-5:	ջδ��ʼ��
		X:	Ԫ�ظ��� 
*/
int count_sta(Stacks *stack){
	if ((*stack).ifInital == 0)
		return ARR_UN_INIT;

    return (stack->sta_arr)->length;
}

/**
	Description: 
		��ջ 
	Arguments:
		nothing
	Returns:
		-5: ջδ��ʼ��
		0:	��Ԫ�أ���ָ��
		X:	Ԫ�ص�ַ 
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
		�ͷ�ջ�ڴ棬���ڶ�̬������ջ 
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
