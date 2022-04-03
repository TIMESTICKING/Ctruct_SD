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
	(*arrlit).FREE = free_arr;
	(*arrlit).SLICE_arr_copy = slice_list_copy;
	(*arrlit).DEL_arr = delete_list;
	(*arrlit).CLEAR_arr = clear_arr;
	(*arrlit).PRINT = print_arl;
	
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
		��ȡ�����ind�±��Ԫ�صĵ�ַ 
	Arguments:
		ArrayList* arrlit	: (nothing)
		int ind				: �±ꡣ��ȡ��ֵ������ĩβΪ-1 
	Returns:
		-1:	ARR_WRONG_INDEX 	ind�±겻�Ϸ�
		-5:	ARR_UN_INIT 	�б�δ��ʼ�� 
		X:	Ԫ�ص�ַ 
*/
void* get_list(ArrayList* arrlit,int ind){
	if ((*arrlit).ifInital == 0)
		return (void*)ARR_UN_INIT;

	ind = index_format(arrlit->length,ind);//�±��ʽ�� 
	if (ind == ARR_WRONG_INDEX) return (void*)ARR_WRONG_INDEX;//���Ϸ�
	return (*arrlit).arr[ind];
}

/**
	Description: 
		�޸�length�����ڵ����� 
	Arguments:
		int index���±꣬�ɸ���-1ΪĩԪ��
		void* ele_addr��Ҫ��index�±괦���µ���Ԫ�� 
	Returns:
		1��ARR_OK 	success
		-1: ARR_WRONG_INDEX �±곬��length��Χ
		-5: ARR_UN_INIT	�б�δ��ʼ�� 
*/
c8 edit_list(ArrayList* arrlit,int index,void* ele_addr){
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	index = index_format(arrlit->length,index);//�±��ʽ��
	if (index == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;//���Ϸ�
	
	(*arrlit).arr[index] = ele_addr;
	return ARR_OK;
}

/**
	Description: 
		�����б����ȣ���ֱ��arrlit.Length��������ֻ���ӳ�ʼ����⹦�� 
	Arguments:
		nothing
	Returns:
		-5:	ARR_UN_INIT	�б�δ��ʼ��
		X:	�б����� 
*/
int count_list(ArrayList* arrlit){
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	return (*arrlit).length;
}

/**
	Description: 
		��չ���鳤�ȣ�����ԭ�ȵ����ݸ��Ƶ����ڴ��У����ͷ�ԭ�ȵ��ڴ� 
	Arguments:
		int expend_length:	Ҫ��չ�Ĵ�С���ֽڣ�; -1ΪĬ�ϣ���չֵΪ0.09 * x + 9.09��xΪ��ǰ���� 
	Returns:
		1: ARR_OK	success
		3: ARR_MALLOC_FAIL	�����ڴ�ʧ�� 
		2: ARR_MOVE_FAIL	����ʧ��
*/
static c8 expand_list(ArrayList* arrlit,int expend_length){
	void* (*arr_new);
	int expand_sp;//��ʱ���� 
	if (expend_length == -1){
		//Ĭ��
		expand_sp = EXPEND_SPACE((*arrlit).capacity);
	 	arr_new = (void*)SD_MALLOC(((*arrlit).capacity + expand_sp) * sizeof(void*));
	}else{
		if (expend_length < 0) return 0;
		expand_sp = expend_length;
	 	arr_new = (void*)SD_MALLOC(((*arrlit).capacity + expand_sp) * sizeof(void*));
	}
	
 	if (arr_new == (void*)0)
 		return ARR_MALLOC_FAIL;//�����ڴ�ʧ�� 
	//�����ڴ�ɹ� 
	
 	(*arrlit).capacity += expand_sp;//д������ 
 	
	if ( memcpy(arr_new,(*arrlit).arr,(*arrlit).capacity * sizeof(void*)) == (void*)0)//�������鵽�µ� 
		return ARR_MOVE_FAIL;//����ʧ�� 
	SD_FREE((*arrlit).arr);//�ͷžɵ�
 	(*arrlit).arr = arr_new;
 	
 	return ARR_OK;
}

/**
	Description: 
		���б�ĩβ׷��һ��Ԫ�صĵ�ַ 
	Arguments:
		void* ele_addr:	Ԫ�صĵ�ַ 
	Returns:
		1: ARR_OK success
		-5:ARR_UN_INIT�б�δ��ʼ�� 
		else: refer to FUNC expand_list()
*/
c8 add_list(ArrayList* arrlit,void* ele_addr){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
		
	if ( ifNeed_expand(arrlit,1) == 1){
		sta = expand_list(arrlit,-1);//���� 
		if (sta != ARR_OK) return sta;
		//��չ�����ڴ����ɹ����Ҹ��Ƴɹ� 
	}
	(*arrlit).arr[(*arrlit).length] = ele_addr;
	((*arrlit).length)++;
	return ARR_OK;
}

/**
	Description: 
		���б���ĳ�±������Ԫ�� 
	Arguments:
		int index�� 	�±꣬�ɸ���-1ΪĩԪ��
	 	void* ele_addr: ��Ԫ�� 
	Returns:
		1: success
		-5: ARR_UN_INIT �б�δ��ʼ��
		-1: �±겻�Ϸ�
		2: �������ʧ��
		else: refer to FUNC expand_list() 
*/
c8 insert_at_list_one(ArrayList* arrlit,int index,void* ele_addr){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;

	index = index_format(arrlit->length,index);
	if (index == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;//���Ϸ�
	
	if ( ifNeed_expand(arrlit,1) == ARR_OK)//Ҫ��Ҫ����
	{ 
		sta = expand_list(arrlit,-1);//���� 
		if (sta != ARR_OK) return sta;//����ʧ�� ,sta refer to FUNC expand_list()
	}
	
	if ( arr_move(arrlit,index,1) == ARR_MOVE_FAIL) return ARR_MOVE_FAIL;//�ڴ��ƶ�ʧ�� 
	(*arrlit).arr[index] = ele_addr;
	(*arrlit).length ++;
	return ARR_OK; 
}


/**
	Description: 
		���б���ĳ�±�������б� 
	Arguments:
		int index�� 	�±꣬�ɸ���-1ΪĩԪ��
	 	ArrayList* arrsub: ���б� 
	Returns:
		1: success
		-5: �б�δ��ʼ��
		-1: �±겻�Ϸ�
		2: �����ڴ��ƶ�ʧ�� 
		else: refer to FUNC expand_list() 
*/
c8 insert_at_list_lots(ArrayList* arrlit,int index,ArrayList* arrsub){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;

	index = index_format(arrlit->length,index);
	if (index == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;//���Ϸ�
	
	if ( ifNeed_expand(arrlit,(*arrsub).length) == ARR_OK)//Ҫ��Ҫ����
	{ 
		sta = expand_list(arrlit,(*arrsub).capacity);//���� 
		if (sta != ARR_OK) return sta;//����ʧ��,sta refer to FUNC expand_list()
	}
	//arrlit�� index������ (*arrsub).length������ 
	if ( arr_move(arrlit,index,(*arrsub).length) == ARR_MOVE_FAIL)
		return ARR_MOVE_FAIL;//�ڴ��ƶ�ʧ��
	//arrsub���ݸ��Ƶ� arrlit�� index��ʼ��
	if ( memcpy((*arrlit).arr + index, (*arrsub).arr, (*arrsub).length * sizeof(void*)) == (void*)0 )
		return ARR_MOVE_FAIL;//����ʧ��
		
	(*arrlit).length += (*arrsub).length;
	return ARR_OK;
}

/**
	Description: 
		���б�ĩβ׷��һ���б� 
	Arguments:
		ArrayList* arrlit_tail:	�����ӵ� arrlit β�� 
	Returns:
		1: success
		-5:�б�δ��ʼ�� 
		else: refer to FUNC expand_list()
*/
c8 add_list_lots(ArrayList* arrlit,ArrayList* arrlit_tail){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
		
	if ( ifNeed_expand(arrlit, (*arrlit_tail).length) == ARR_OK ){
		//ʣ������������������
		sta = expand_list(arrlit,(*arrlit_tail).capacity);
		if (sta != ARR_OK) return sta;//����ʧ��
		//���ݳɹ� 
	}
	if ( memcpy(&(((*arrlit).arr)[(*arrlit).length]), (*arrlit_tail).arr, (*arrlit_tail).length * sizeof(void*)) == (void*)0)//�������� 
		return ARR_MOVE_FAIL;//����ʧ�� 
	(*arrlit).length += (*arrlit_tail).length;
	return ARR_OK;
}

/**
	Description: 
		���ٶ�̬�������б� 
	Arguments:
		nothing
	Returns:
		none
*/
void free_arr(ArrayList* arrlit){
	if((*arrlit).ifInital == 1)
		SD_FREE((*arrlit).arr);//�ͷ�����ռ�
	SD_FREE(arrlit);//�ͷŽṹ�� 
}

/**
	Description: 
		���б����п��� 
	Arguments:
		ArrayList** new_arr: �б�ָ��ĵ�ַ 
	Returns:
		1: success
		-5: �б�δ��ʼ��
		else: refer to FUNC  CreateArrayList() and expand_list()
*/
c8 copy_arr(ArrayList* arrlit,ArrayList** new_arr){
	c8 sta;

	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	if (*new_arr == arrlit) return ARR_OK;//������ͬ 
	
	sta = CreateArrayList(new_arr,(*arrlit).length);
	if (sta != ARR_OK) return sta;//��̬�б�����ʧ�ܣ�sta refer to FUNC CreateArrayList() 

	sta = add_list_lots(*new_arr,arrlit);//�������� 
	if (sta != ARR_OK){
		free_arr(*new_arr);
		return sta;//��������ʧ�� 
	}
	
	(**new_arr).length = (*arrlit).length;
	
	return ARR_OK;
}

/**
	Description: 
		�����б���ԭ�б��ᱻ�޸� 
	Arguments:
		nothing
	Returns:
		1: success
		-5: �б�δ��ʼ�� 
*/
c8 reverse_list(ArrayList* arrlit){
	void* temp;
	int n = (int)floor((*arrlit).length / 2.0);//ѭ���Ĵ���������ȡ�� 
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
		�����ڴ���������б���ԭ�б����ᱻ�޸ģ� 
	Arguments:
		ArrayList** arrcopy:	��������б����б�ָ��ĵ�ַ 
	Returns:
		1: success;
		5: δ��ʼ��
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
	if (sta != ARR_OK) return sta;//��̬�б�����ʧ�ܣ�sta refer to FUNC CreateArrayList() 

	for(i=0;i<l;i++){
		(*temp).arr[i] = (*arrlit).arr[l - i -1];
	}
	(*temp).length += l;
	*arrcopy = temp;
	
	return ARR_OK;
}

/**
	Description: 
		ѡȡ�б���ĳһ���֣��������б����أ�ԭ�б����� 
	Arguments:
		ArrayList** arrnew: ������б����б�ָ��ĵ�ַ
		int start:	���±�start��ʼ��ȡ��������һλ���ɸ���-1ΪĩԪ�� 
		int count:	Ҫ��ȡ�ĸ�����������start��ʼ��ĩβ��count������ʣ����������Ҳȡ��ĩβ 
	Returns:
		1: success
		-5:	�б�δ��ʼ��
		-1:	�±겻�Ϸ�
		2:	���鸴��ʧ��
		else: refer to FUNC  CreateArrayList()
*/
c8 slice_list_copy(ArrayList* arrlit,ArrayList** arrnew,int start,int count){
	c8 sta;
	ArrayList* temp;//������ʱ������ʹ arrnewΪ arrlit�ĵ�ַ 
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	start = index_format(arrlit->length,start);
	if (start == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;
	
	if (count == 0) return ARR_OK;
	if (count > (*arrlit).length - start || count < 0)
		count = (*arrlit).length - start;//count��������ʣ���������Ǹ��������ȡʣ���ȫ�� 

	sta = CreateArrayList(&temp,count);
	if (sta != ARR_OK) return sta;//��̬�б�����ʧ�ܣ�sta refer to FUNC CreateArrayList() 

	if (memcpy((*temp).arr, (*arrlit).arr + start, sizeof(void*)*count ) == (void*)0 )
		return ARR_MOVE_FAIL;//��������ʧ��
		
	(*temp).length += count;
	*arrnew = temp;
	return ARR_OK; 
}

/**
	Description: 
		ɾ���б��еĲ���Ԫ�أ�ԭ�б��ᱻ�޸� 
	Arguments:
		int start:	��ʼλ��������λ���ɸ���-1ΪĩԪ��
		int count:	Ҫɾ���ĸ��� ����������ʣ���������Ǹ��������ȡʣ���ȫ�� 
	Returns:
		1: success
		-5: �б�δ��ʼ��
		-1:	�±겻�Ϸ�
		2:	�����ڴ��ƶ�ʧ�� 
*/
c8 delete_list(ArrayList* arrlit,int start,int count){
	c8 sta;
	if ((*arrlit).ifInital == 0)
		return ARR_UN_INIT;
	
	start = index_format(arrlit->length,start);
	if (start == ARR_WRONG_INDEX) return ARR_WRONG_INDEX;
	
	if (count == 0) return ARR_OK;
	if (count > (*arrlit).length - start || count < 0)
		count = (*arrlit).length - start;//count��������ʣ���������Ǹ��������ȡʣ���ȫ�� 

	if (arr_move(arrlit,start+count,-count) == ARR_MOVE_FAIL)
		return ARR_MOVE_FAIL;
		
	(*arrlit).length -= count;
	return ARR_OK;
}

/**
	Description: 
		����б������������� 
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
