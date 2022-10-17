#ifndef __LinkedList_SD_H__
#define __LinkedList_SD_H__

#include "tree_base.h"

#define PREV_LLIST		0
#define NEXT_LLIST		1

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef struct lList {
	Tree *tree;
	char *name;
	Tree_node *tail;
	c8 (*INSERT_ele_byAddr)(struct lList*,Tree_node*,u8_ds position,void *ele);
	c8 (*INSERT_ele_atInd)(struct lList*,int ind,void *ele);
	c8 (*INSERT_ele_atTail)(struct lList*,void*ele);
	c8 (*INSERT_ele_atHead)(struct lList*,void*ele);
	c8 (*ADD_llist_atHead)(struct lList*,struct lList* add_llist);
	c8 (*ADD_llist_atTail)(struct lList*,struct lList* add_llist);
	c8 (*ADD_llist_atInd)(struct lList*,int ind,struct lList* add_llist);
	c8 (*DEL_byAddr_llist)(struct lList*,Tree_node* node_del);
	c8 (*DEL_byInd_llist)(struct lList*,int ind);
	Tree_node* (*GET_tail_llist)(struct lList*);
	Tree_node* (*GET_head_llist)(struct lList*);
	Tree_node* (*GET_addr_byIndex)(struct lList*,int ind);
	c8 (*COPY_llist)(struct lList* llist,struct lList** new_llist);
	c8 (*REVERSE_llist)(struct lList*);
	u32_ds (*COUNT)(struct lList*);
	c8 (*IF_ELEaddr_exsit_llist)(struct lList*,void* ele);
	void (*FREE)(struct lList*);
	void (*PRINT)(struct lList*);
	c8	ifinitial;
}LinkedList_SD;
//��Tree_node�ڵ������У�0�±�Ϊǰ���ڵ� ��1Ϊ��� 



c8 InitLinkedList_SD(LinkedList_SD *llist);
c8 CreateLinkedList_SD(LinkedList_SD **llist);
c8 insert_ele_atMid(LinkedList_SD *llist,Tree_node *node,u8_ds position,void *ele);
c8 add_ele_atTail(LinkedList_SD *llist,void *ele);
c8 add_ele_atHead(LinkedList_SD *llist,void *ele);
c8 add_ele_byInd_llist(LinkedList_SD *llist,int ind,void *ele);
c8 insert_llist_atHead(LinkedList_SD *llist,LinkedList_SD *add_llist);
c8 insert_llist_atTail(LinkedList_SD *llist,LinkedList_SD *add_llist);
c8 insert_llist_byInd(LinkedList_SD *llist,int ind,LinkedList_SD *add_llist);
c8 delete_node_llist(LinkedList_SD *llist,Tree_node *node_del);
void print_llist_main(LinkedList_SD *llist);
void print_llist(LinkedList_SD *llist);
Tree_node* get_headNode_llist(LinkedList_SD *llist);
Tree_node* get_tailNode_llist(LinkedList_SD *llist);
Tree_node* getAddr_llist(LinkedList_SD *llist,int ind);
c8 delete_byInd_llist(LinkedList_SD *llist,int ind);
c8 reverse_llist(LinkedList_SD *llist);
u32_ds get_count_llist(LinkedList_SD *llist);
c8 copy_llist(LinkedList_SD *llist,LinkedList_SD **new_llist);
void free_llist(LinkedList_SD *llist);
c8 if_eleAddr_exsit_llist(LinkedList_SD *llist,void *ele);


static c8 add_ele_emptyList(LinkedList_SD *llist,void *ele);
Tree_node* runthrough_llist(LinkedList_SD *llist,int ind);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif


