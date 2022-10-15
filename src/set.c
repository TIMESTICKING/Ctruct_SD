#include "set.h"

/**
	Description: 
		��̬��ʼ������ 
	Arguments:
		u32_ds length����ϣ����ĳ���
	 	u32_ds numP��������������p������<=length������������ 
	Returns:
		0��numP������length
		3���ڴ�����ʧ��
		1��success 
*/
c8 InitHashset(Hashset *set,u32_ds length,u32_ds numP){
	void* *i;
	if (numP > length || numP == 0)	return ARR_FALSE;
	i = (void**)SD_MALLOC(sizeof(void*) * length);
	if (i == (void**)0)	return ARR_MALLOC_FAIL;
	set->hashList = i;
	set->length = length;
	set->name = "hashset_def";
	set->ifinitial = 1;
	
	return ARR_OK;
}

/**
	Description: 
		���� InitHashset()
*/
c8 CreateHashset(Hashset **set,u32_ds length,u32_ds numP){
	c8 sta;
	*set = (Hashset*)SD_MALLOC(sizeof(Hashset));
	if (*set == (Hashset*)0)	return ARR_MALLOC_FAIL;
	
	sta = InitHashset(*set,length,numP);
	if (sta != ARR_OK){
		SD_FREE(*set);
		return sta;
	}
	
	return ARR_OK;
}

/**
	Description: 
		��ϣ������ȡ����±꣬ind = n % p 
*/
u32_ds hashFunc(Hashset *set,u32_ds n){
	return n % set->numP;
}

c8 insert_hashList(Hashset *set,u32_ds ind,void* ele){
	if (set->ifinitial != 1)
		return ARR_UN_INIT;
		
	(set->hashList)[ind] = ele;
	return ARR_OK;
}

void* get_hashList(Hashset *set,u32_ds ind){
	if (set->ifinitial != 1)
		return (void*)ARR_UN_INIT;
	
	return (set->hashList)[ind];
}
