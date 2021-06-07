#include "ds_globalVars.h"

/**
	Description: 
		判断下标合法性并格式化下标 ，尤其是负数时 
	Arguments:
		int ind: 下标，可负。-1为末元素 
	Returns:
		-1:	ARR_WRONG_INDEX	不合法 
		X:	X为正下标 
*/
int index_format(int totalLength,int ind)
{
	if (ind > totalLength - 1 || ind + totalLength < 0)
		return ARR_WRONG_INDEX;
	if (ind >= 0){
		return ind;
	}else{
		return totalLength + ind;
	}
}

/**
	Description: 
		创建int类型的数 
	Returns:
		地址 
*/
int* INT_new(int number){
	int *t = (int*)SD_MALLOC(sizeof(int));
	*t = number;
	return t;
}
