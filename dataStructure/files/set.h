#ifndef __SET_H__
#define __SET_H__

#include "ds_globalVars.h"

typedef struct set_ds {
	void* *hashList;
	char* name;
	u32_ds length;
	u32_ds numP;//除留余数法的p，必须<=length，建议是质数 
	c8 ifinitial;
}Hashset;


/**
	Description: 
		静态初始化集合 
	Arguments:
		u32_ds length：哈希数组的长度
	 	u32_ds numP：除留余数法的p，必须<=length，建议是质数 
	Returns:
		0：numP大于了length
		3：内存申请失败
		1：success 
*/
c8 InitHashset(Hashset *set,u32_ds length,u32_ds numP);
c8 CreateHashset(Hashset **set,u32_ds length,u32_ds numP);

#endif













