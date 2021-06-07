#ifndef __ITERATORS_H__
#define __ITERATORS_H__

#include "ds_globalVars.h"
#include "arraylist.h"

#define FOR_ITER(ptr)	while(ptr.hasNext(&ptr))

typedef enum itertype {
	ITERTYPE_REVERSE_4ARRAY=1
}ENUM_ITERTYPE_4ARRAY;

typedef struct iter_4array {
	ArrayList* array;
	int pos;		// position index
	void* (*next)(struct iter_4array*);
	c8 (*hasNext)(struct iter_4array*);
	
	c8 ifInital;//该结构体是否被初始化，yes； 1 
}ITER_4ARRAY;







c8 InitITER_4array(ITER_4ARRAY* iter, ArrayList* arr, ENUM_ITERTYPE_4ARRAY type);
c8 hasNext_4array(ITER_4ARRAY* iter);
void* next_reverse_4array(ITER_4ARRAY* iter);


#endif

