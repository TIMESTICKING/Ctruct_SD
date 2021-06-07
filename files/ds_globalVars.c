#include "ds_globalVars.h"

/**
	Description: 
		�ж��±�Ϸ��Բ���ʽ���±� �������Ǹ���ʱ 
	Arguments:
		int ind: �±꣬�ɸ���-1ΪĩԪ�� 
	Returns:
		-1:	ARR_WRONG_INDEX	���Ϸ� 
		X:	XΪ���±� 
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
		����int���͵��� 
	Returns:
		��ַ 
*/
int* INT_new(int number){
	int *t = (int*)SD_MALLOC(sizeof(int));
	*t = number;
	return t;
}
