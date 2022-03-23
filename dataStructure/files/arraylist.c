#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arraylist.h"


/**
	Description: 
		init ArrayList struct
	Arguments:
		int cap:	length of array, 15 recommend
	Return:
		1: ARR_OK
		3: ARR_MALLOC_FAIL
*/
c8 InitArrayList(ArrayList* arrlit,u32_ds cap){
	void** i;
	i = (void**)SD_MALLOC(sizeof(void*) * cap);
	if (i == (void**)0) return ARR_MALLOC_FAIL;
	(*arrlit).arr = i;
	(*arrlit).ifInital = 1;
	(*arrlit).length = 0;
	(*arrlit).capacity = cap;
	(*arrlit).name = "arraylist_def";
	(*arrlit).GET_arr = get_list;
	(*arrlit).ADD_one = add_list;
	(*arrlit).ADD_lots = add_list_lots;
	(*arrlit).EDIT_arr = edit_list;
	(*arrlit).INSERT_one = insert_at_list_one;
	(*arrlit).INSERT_lots = insert_at_list_lots;
	(*arrlit).COPY_arr = copy_arr;
	(*arrlit).COUNT = count_list;
	(*arrlit).REVERSE_arr = reverse_list;
	(*arrlit).REVERSE_arr_copy = reverse_list_copy;
	(*arrlit).FREE_arr = free_arr;
	(*arrlit).SLICE_arr_copy = slice_list_copy;
	(*arrlit).DEL_arr = delete_list;
	(*arrlit).CLEAR_arr = clear_arr;
	(*arrlit).PRINT_arr = print_arl;
	
	return ARR_OK;
}

/**
	Description: 
		dynamicly create list
	Arguments:
		ArrayList** arrlit_pointer:	address of list's pointer
	 	int cap: init list length, 15 recommend
	Returns:
		1: ARR_OK
		3: ARR_MALLOC_FAIL
*/
c8 CreateArrayList(ArrayList** arrlit_pointer,u32_ds cap){
	*arrlit_pointer = (ArrayList*)SD_MALLOC(sizeof(ArrayList));
	if (*arrlit_pointer == (ArrayList*)0) return ARR_MALLOC_FAIL;//memory alloc fail
	
	if ( InitArrayList(*arrlit_pointer,cap) == ARR_MALLOC_FAIL	){
		SD_FREE(*arrlit_pointer);
		return ARR_MALLOC_FAIL;//init a new list failed, wrong in memory allocing
	}
	return ARR_OK;
}


/**
	Description: 
		if list needs expand cap
	Arguments:
		int moree: number of ele which need to be added
	Returns:
		0: ARR_FALSE dont need expand
		1: ARR_OK need expand
*/
static c8 ifNeed_expand(ArrayList* arrlit,int moree){
	if ( (*arrlit).length + moree > (*arrlit).capacity )
		return ARR_OK;
	return ARR_FALSE;
}

/**
	Description: 
		move to right 'step' step from some index at list
	Arguments:
		int ind: index
	 	int step:number index to move. positive number move to right, negative to left
	Returns:
		1: ARR_OK success
		2: ARR_MOVE_FAIL memory moving fail
*/
static c8 arr_move(ArrayList* arrlit,int ind,int step){
	if ( memmove((*arrlit).arr + ind + step,(*arrlit).arr + ind,sizeof(void*) * ((*arrlit).length - ind)) == (void*)0 )
		//move fail
		return ARR_MOVE_FAIL;
	return ARR_OK; 
}


/**
	Description: 
		获取数组的ind下标的元素的地址 
	Arguments:
		ArrayList* arrlit	: (nothing)
		int ind				: 下标。可取负值，数组末尾为-1 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind下标不合法
		-5:	ARR_UN_INIT 	列表未初始化 
		X:	元素地址 
*/
void* get_list(ArrayList* arrlit,int ind){
	if ((*arrlit).ifInital == 0)
		return (void*)ARR_UN_INIT;

	ind = index_format(arrlit->length,ind);//下标格式化 
	if (ind == ARR_WRONG_INDEX) return (void*)ARR_WRONG_INDEX;//不合法
	return (*arrlit).arr[ind];
}

/**
	Description: 
		修改length长度内的数据 
	Arguments:
		int index：下标，可负，-1为末元素
		void* ele_addr：要在index下标处更新的新元素 
	Returns:
		1：ARR_OK 	success
		-1: ARR_WRONG_INDEX 下标超出length范围
		-5: ARR_UN_INIT	列表未初始化 
*/
c8 edit_list(ArrayList* arrlit,int index,void* ele_addr){
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	index = index_format(arrlit->length,index);//下标格式化
	if (index == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;//不合法
	
	(*arrlit).arr[index] = ele_addr;
	return ARR_OK;
}

/**
	Description: 
		返回列表长度，可直接arrlit.Length，本方法只增加初始化检测功能 
	Arguments:
		nothing
	Returns:
		-5:	ARR_UN_INIT	列表未初始化
		X:	列表长度 
*/
int count_list(ArrayList* arrlit){
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	return (*arrlit).length;
}

/**
	Description: 
		扩展数组长度，并把原先的内容复制到新内存中，再释放原先的内存 
	Arguments:
		int expend_length:	要扩展的大小（字节）; -1为默认，扩展值为0.09 * x + 9.09，x为当前容量 
	Returns:
		1: ARR_OK	success
		3: ARR_MALLOC_FAIL	分配内存失败 
		2: ARR_MOVE_FAIL	复制失败
*/
static c8 expand_list(ArrayList* arrlit,int expend_length){
	void* (*arr_new);
	int expand_sp;//临时变量 
	if (expend_length == -1){
		//默认
		expand_sp = EXPEND_SPACE((*arrlit).capacity);
	 	arr_new = (void*)SD_MALLOC(((*arrlit).capacity + expand_sp) * sizeof(void*));
	}else{
		if (expend_length < 0) return 0;
		expand_sp = expend_length;
	 	arr_new = (void*)SD_MALLOC(((*arrlit).capacity + expand_sp) * sizeof(void*));
	}
	
 	if (arr_new == (void*)0)
 		return ARR_MALLOC_FAIL;//分配内存失败 
	//分配内存成功 
	
 	(*arrlit).capacity += expand_sp;//写入扩容 
 	
	if ( memcpy(arr_new,(*arrlit).arr,(*arrlit).capacity * sizeof(void*)) == (void*)0)//复制数组到新的 
		return ARR_MOVE_FAIL;//复制失败 
	SD_FREE((*arrlit).arr);//释放旧的
 	(*arrlit).arr = arr_new;
 	
 	return ARR_OK;
}

/**
	Description: 
		向列表末尾追加一个元素的地址 
	Arguments:
		void* ele_addr:	元素的地址 
	Returns:
		1: ARR_OK success
		-5:ARR_UN_INIT列表未初始化 
		else: refer to FUNC expand_list()
*/
c8 add_list(ArrayList* arrlit,void* ele_addr){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
		
	if ( ifNeed_expand(arrlit,1) == 1){
		sta = expand_list(arrlit,-1);//扩容 
		if (sta != ARR_OK) return sta;
		//扩展数组内存分配成功，且复制成功 
	}
	(*arrlit).arr[(*arrlit).length] = ele_addr;
	((*arrlit).length)++;
	return ARR_OK;
}

/**
	Description: 
		在列表的某下标插入新元素 
	Arguments:
		int index： 	下标，可负，-1为末元素
	 	void* ele_addr: 新元素 
	Returns:
		1: success
		-5: ARR_UN_INIT 列表未初始化
		-1: 下标不合法
		2: 数组后移失败
		else: refer to FUNC expand_list() 
*/
c8 insert_at_list_one(ArrayList* arrlit,int index,void* ele_addr){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;

	index = index_format(arrlit->length,index);
	if (index == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;//不合法
	
	if ( ifNeed_expand(arrlit,1) == ARR_OK)//要不要扩容
	{ 
		sta = expand_list(arrlit,-1);//扩容 
		if (sta != ARR_OK) return sta;//扩容失败 ,sta refer to FUNC expand_list()
	}
	
	if ( arr_move(arrlit,index,1) == ARR_MOVE_FAIL) return ARR_MOVE_FAIL;//内存移动失败 
	(*arrlit).arr[index] = ele_addr;
	(*arrlit).length ++;
	return ARR_OK; 
}


/**
	Description: 
		在列表的某下标插入新列表 
	Arguments:
		int index： 	下标，可负，-1为末元素
	 	ArrayList* arrsub: 新列表 
	Returns:
		1: success
		-5: 列表未初始化
		-1: 下标不合法
		2: 数组内存移动失败 
		else: refer to FUNC expand_list() 
*/
c8 insert_at_list_lots(ArrayList* arrlit,int index,ArrayList* arrsub){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;

	index = index_format(arrlit->length,index);
	if (index == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;//不合法
	
	if ( ifNeed_expand(arrlit,(*arrsub).length) == ARR_OK)//要不要扩容
	{ 
		sta = expand_list(arrlit,(*arrsub).capacity);//扩容 
		if (sta != ARR_OK) return sta;//扩容失败,sta refer to FUNC expand_list()
	}
	//arrlit的 index处右移 (*arrsub).length个长度 
	if ( arr_move(arrlit,index,(*arrsub).length) == ARR_MOVE_FAIL)
		return ARR_MOVE_FAIL;//内存移动失败
	//arrsub内容复制到 arrlit的 index起始处
	if ( memcpy((*arrlit).arr + index, (*arrsub).arr, (*arrsub).length * sizeof(void*)) == (void*)0 )
		return ARR_MOVE_FAIL;//复制失败
		
	(*arrlit).length += (*arrsub).length;
	return ARR_OK;
}

/**
	Description: 
		向列表末尾追加一个列表 
	Arguments:
		ArrayList* arrlit_tail:	将它加到 arrlit 尾部 
	Returns:
		1: success
		-5:列表未初始化 
		else: refer to FUNC expand_list()
*/
c8 add_list_lots(ArrayList* arrlit,ArrayList* arrlit_tail){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
		
	if ( ifNeed_expand(arrlit, (*arrlit_tail).length) == ARR_OK ){
		//剩余容量不够，须扩容
		sta = expand_list(arrlit,(*arrlit_tail).capacity);
		if (sta != ARR_OK) return sta;//扩容失败
		//扩容成功 
	}
	if ( memcpy(&(((*arrlit).arr)[(*arrlit).length]), (*arrlit_tail).arr, (*arrlit_tail).length * sizeof(void*)) == (void*)0)//复制数组 
		return ARR_MOVE_FAIL;//复制失败 
	(*arrlit).length += (*arrlit_tail).length;
	return ARR_OK;
}

/**
	Description: 
		销毁动态创建的列表 
	Arguments:
		nothing
	Returns:
		none
*/
void free_arr(ArrayList* arrlit){
	if((*arrlit).ifInital == 1)
		SD_FREE((*arrlit).arr);//释放数组空间
	SD_FREE(arrlit);//释放结构体 
}

/**
	Description: 
		对列表进行拷贝 
	Arguments:
		ArrayList** new_arr: 列表指针的地址 
	Returns:
		1: success
		-5: 列表未初始化
		else: refer to FUNC  CreateArrayList() and expand_list()
*/
c8 copy_arr(ArrayList* arrlit,ArrayList** new_arr){
	c8 sta;

	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	if (*new_arr == arrlit) return ARR_OK;//两者相同 
	
	sta = CreateArrayList(new_arr,(*arrlit).length);
	if (sta != ARR_OK) return sta;//动态列表创建失败，sta refer to FUNC CreateArrayList() 

	sta = add_list_lots(*new_arr,arrlit);//复制数组 
	if (sta != ARR_OK){
		free_arr(*new_arr);
		return sta;//复制数组失败 
	}
	
	(**new_arr).length = (*arrlit).length;
	
	return ARR_OK;
}

/**
	Description: 
		逆序列表，原列表会被修改 
	Arguments:
		nothing
	Returns:
		1: success
		-5: 列表未初始化 
*/
c8 reverse_list(ArrayList* arrlit){
	void* temp;
	int n = (int)floor((*arrlit).length / 2.0);//循环的次数。向下取整 
	int i,i_opp;
	int l = (*arrlit).length;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;

	for (i=0;i<n;i++){
		i_opp = l - i - 1;
		temp = (*arrlit).arr[i];
		(*arrlit).arr[i] = (*arrlit).arr[i_opp];
		(*arrlit).arr[i_opp] = temp;
	}
	
	return ARR_OK;
}

/**
	Description: 
		申请内存放置逆序列表，原列表不会被修改， 
	Arguments:
		ArrayList** arrcopy:	存放逆序列表的列表指针的地址 
	Returns:
		1: success;
		5: 未初始化
		else: refer to FUNC CreateArrayList()
*/
c8 reverse_list_copy(ArrayList* arrlit,ArrayList** arrcopy){
	ArrayList *temp;
	int l = (*arrlit).length;
	int i,i_opp;
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;

	sta = CreateArrayList(&temp,l);
	if (sta != ARR_OK) return sta;//动态列表创建失败，sta refer to FUNC CreateArrayList() 

	for(i=0;i<l;i++){
		(*temp).arr[i] = (*arrlit).arr[l - i -1];
	}
	(*temp).length += l;
	*arrcopy = temp;
	
	return ARR_OK;
}

/**
	Description: 
		选取列表的某一部分，并以新列表返回，原列表不变 
	Arguments:
		ArrayList** arrnew: 存放新列表的列表指针的地址
		int start:	从下标start开始截取，包括这一位。可负，-1为末元素 
		int count:	要截取的个数。负数：start开始到末尾；count若超出剩余数量，则也取到末尾 
	Returns:
		1: success
		-5:	列表未初始化
		-1:	下标不合法
		2:	数组复制失败
		else: refer to FUNC  CreateArrayList()
*/
c8 slice_list_copy(ArrayList* arrlit,ArrayList** arrnew,int start,int count){
	c8 sta;
	ArrayList* temp;//有了临时变量可使 arrnew为 arrlit的地址 
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	start = index_format(arrlit->length,start);
	if (start == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;
	
	if (count == 0) return ARR_OK;
	if (count > (*arrlit).length - start || count < 0)
		count = (*arrlit).length - start;//count若超过了剩余数量或是负数，则截取剩余的全部 

	sta = CreateArrayList(&temp,count);
	if (sta != ARR_OK) return sta;//动态列表创建失败，sta refer to FUNC CreateArrayList() 

	if (memcpy((*temp).arr, (*arrlit).arr + start, sizeof(void*)*count ) == (void*)0 )
		return ARR_MOVE_FAIL;//复制数组失败
		
	(*temp).length += count;
	*arrnew = temp;
	return ARR_OK; 
}

/**
	Description: 
		删除列表中的部分元素，原列表会被修改 
	Arguments:
		int start:	起始位，包括此位。可负，-1为末元素
		int count:	要删除的个数 。若超过了剩余数量或是负数，则截取剩余的全部 
	Returns:
		1: success
		-5: 列表未初始化
		-1:	下标不合法
		2:	数组内存移动失败 
*/
c8 delete_list(ArrayList* arrlit,int start,int count){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	start = index_format(arrlit->length,start);
	if (start == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;
	
	if (count == 0) return ARR_OK;
	if (count > (*arrlit).length - start || count < 0)
		count = (*arrlit).length - start;//count若超过了剩余数量或是负数，则截取剩余的全部 

	if (arr_move(arrlit,start+count,-count) == ARR_MOVE_FAIL)
		return ARR_MOVE_FAIL;
		
	(*arrlit).length -= count;
	return ARR_OK;
}

/**
	Description: 
		清空列表，但容量不变 
	Arguments:
		nothing
	Returns:
		none
*/
void clear_arr(ArrayList *arrlit){
	arrlit->length = 0;
}

void print_arr_main(ArrayList *arrlit){
	SD_PRINT("=>arraylist=>ifinitial:	%d",arrlit->ifInital);
	SD_PRINT("=>arraylist=>length:	%d",arrlit->length);
	SD_PRINT("=>arraylist=>capacity:	%d",arrlit->capacity);
}

void print_arl(ArrayList *arrlit){
	SD_PRINT_HEAD("ArrayList",arrlit->name);
	print_arr_main(arrlit);
	SD_PRINT_END;
}
