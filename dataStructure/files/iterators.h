#ifndef __ITERATORS_H__
#define __ITERATORS_H__

#include "ds_globalVars.h"
#include "arraylist.h"

#define FOR_ITER(instance,args...)	while(instance.hasNext(&instance,##args))
#define GET_ITER(instance,ele_type,args...)	*((ele_type)instance.next(&instance,##args))
#define GI	GET_ITER

#define ITERDIREC_para_init(p)	ENUM_ITERDIRECTION_4ARRAY p = ITERDIREC_INIT;
#define ITERDIREC_para_judge(p, res, aim)	if(res==aim){p=ITERDIREC_INIT;break;}\
											else if(res<aim)p=ITERDIREC_RIGHT;\
											else p=ITERDIREC_LEFT;
#define ITERDIREC_para_ifFind(para)		(para==ITERDIREC_INIT)


typedef enum itertype {
	ITERTYPE_REVERSE_4ARRAY=1,
	ITERTYPE_POSI_SEQ_4ARRAY,
	ITERTYPE_2DIVSION_4ARRAY
}ENUM_ITERTYPE_4ARRAY;

typedef enum iterDirection {
	ITERDIREC_LEFT=-1,
	ITERDIREC_INIT,
	ITERDIREC_RIGHT
}ENUM_ITERDIRECTION_4ARRAY;

typedef struct iter_4array {
	ArrayList* array;
	int pos;		// position index
	int *temp;		// 特别保留的数组 
	void* (*next)(struct iter_4array*, ...);
	c8 (*hasNext)(struct iter_4array*,...);
	
	c8 ifInital;//该结构体是否被初始化，yes； 1 
}ITER_4ARRAY;







c8 InitITER_4array(ITER_4ARRAY* iter, ArrayList* arr, ENUM_ITERTYPE_4ARRAY type);
c8 hasNext_4array(ITER_4ARRAY* iter);
void* next_4array(ITER_4ARRAY* iter,...);
void* next_reverse_4array(ITER_4ARRAY* iter,...);

c8 hasNext_2div_4array(ITER_4ARRAY* iter, int direction);
void* next_2divsion_4array(ITER_4ARRAY* iter, int direction);


#endif

