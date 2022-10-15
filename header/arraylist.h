#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include "ds_globalVars.h"

#define	EXPEND_SPACE(x)	(0.09 * x + 9.09)

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef struct arraylist {
	char *name;
	void* (*arr);
	int length;//��ǰ����װ������ 
	int capacity;//������ 
	//�෽�� 
	void* (*GET_arr)(struct arraylist*,int);
	c8 (*ADD_one)(struct arraylist*,void*);
	c8 (*ADD_lots)(struct arraylist*,struct arraylist*);
	c8 (*EDIT_arr)(struct arraylist*,int,void*);
	c8 (*INSERT_one)(struct arraylist*,int,void*);
	c8 (*INSERT_lots)(struct arraylist*,int,struct arraylist*);
	c8 (*COPY_arr)(struct arraylist*,struct arraylist**);
	int (*COUNT)(struct arraylist*);
	c8 (*REVERSE_arr)(struct arraylist*);
	c8 (*REVERSE_arr_copy)(struct arraylist*,struct arraylist**);
	void (*FREE)(struct arraylist*);
	c8 (*SLICE_arr_copy)(struct arraylist*,struct arraylist**,int,int);
	c8 (*DEL_arr)(struct arraylist*,int,int);
	void (*PRINT)(struct arraylist*);
	void (*CLEAR_arr)(struct arraylist*);
	c8 ifInital;//�ýṹ���Ƿ񱻳�ʼ����yes�� 1 
}ArrayList;



void* get_list(ArrayList* arrlit,int ind);
c8 InitArrayList(ArrayList* arrlit,u32_ds cap);
c8 CreateArrayList(ArrayList** arrlit_pointer,u32_ds cap);
c8 add_list(ArrayList* arrlit,void* ele_addr);
c8 add_list_lots(ArrayList* arrlit,ArrayList* arrlit_tail);
c8 edit_list(ArrayList* arrlit,int index,void* ele_addr);
c8 insert_at_list_one(ArrayList* arrlit,int index,void* ele_addr);
c8 insert_at_list_lots(ArrayList* arrlit,int index,ArrayList* arrsub);
c8 copy_arr(ArrayList* arrlit,ArrayList** new_arr);
int count_list(ArrayList* arrlit);
c8 reverse_list(ArrayList* arrlit);
c8 reverse_list_copy(ArrayList* arrlit,ArrayList** arrcopy);
void free_arr(ArrayList* arrlit);
c8 slice_list_copy(ArrayList* arrlit,ArrayList** arrnew,int start,int count);
c8 delete_list(ArrayList* arrlit,int start,int count);
void clear_arr(ArrayList *arrlit);
void print_arr_main(ArrayList *arrlit);
void print_arl(ArrayList *arrlit);

static c8 expand_list(ArrayList* arrlit,int expend_length);
static c8 ifNeed_expand(ArrayList* arrlit,int moree);
static c8 arr_move(ArrayList* arrlit,int ind,int step);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif


