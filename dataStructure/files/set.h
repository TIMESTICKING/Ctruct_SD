#ifndef __SET_H__
#define __SET_H__

#include "ds_globalVars.h"


#ifdef __cplusplus
extern "C"{
#endif // __cplusplus


typedef struct set_ds {
	void* *hashList;
	char* name;
	u32_ds length;
	u32_ds numP;//������������p������<=length������������ 
	c8 ifinitial;
}Hashset;

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
c8 InitHashset(Hashset *set,u32_ds length,u32_ds numP);
c8 CreateHashset(Hashset **set,u32_ds length,u32_ds numP);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif













