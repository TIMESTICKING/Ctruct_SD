#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "tree_base.h"

#define PREVIEW_LLIST	0
#define NEXT_LLIST		1

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

typedef struct lList {
	Tree tree;
	char *name;
	Tree_node *tail;
	c8 (*INSERT_ele_byAddr)(struct lList*,Tree_node*,u8_ds,void*);
	c8 (*INSERT_ele_atInd)(struct lList*,int,void*);
	c8 (*INSERT_ele_atTail)(struct lList*,void*);
	c8 (*INSERT_ele_atHead)(struct lList*,void*);
	c8 (*ADD_llist_atHead)(struct lList*,struct lList*);
	c8 (*ADD_llist_atTail)(struct lList*,struct lList*);
	c8 (*ADD_llist_atInd)(struct lList*,int,struct lList*);
	c8 (*DEL_byAddr_llist)(struct lList*,Tree_node*);
	c8 (*DEL_byInd_llist)(struct lList*,int);
	Tree_node* (*GET_tail_llist)(struct lList*);
	Tree_node* (*GET_head_llist)(struct lList*);
	Tree_node* (*GET_addr_byIndex)(struct lList*,int);
	c8 (*COPY_llist)(struct lList*,struct lList**);
	c8 (*REVERSE_llist)(struct lList*);
	u32_ds (*GET_COUNT_llist)(struct lList*);
	c8 (*IF_ELEaddr_exsit_llist)(struct lList*,void*);
	void (*FREE_llist)(struct lList*);
	void (*PRINT_llist)(struct lList*);
	c8	ifinitial;
}LinkedList;
//��Tree_node�ڵ������У�0�±�Ϊǰ���ڵ� ��1Ϊ��� 



c8 InitLinkedList(LinkedList *llist);
c8 CreateLinkedList(LinkedList **llist);
c8 insert_ele_atMid(LinkedList *llist,Tree_node *node,u8_ds position,void *ele);
c8 add_ele_atTail(LinkedList *llist,void *ele);
c8 add_ele_atHead(LinkedList *llist,void *ele);
c8 add_ele_byInd_llist(LinkedList *llist,int ind,void *ele);
c8 insert_llist_atHead(LinkedList *llist,LinkedList *add_llist);
c8 insert_llist_atTail(LinkedList *llist,LinkedList *add_llist);
c8 insert_llist_byInd(LinkedList *llist,int ind,LinkedList *add_llist);
c8 delete_node_llist(LinkedList *llist,Tree_node *node_del);
void print_llist_main(LinkedList *llist);
void print_llist(LinkedList *llist);
Tree_node* get_headNode_llist(LinkedList *llist);
Tree_node* get_tailNode_llist(LinkedList *llist);
Tree_node* getAddr_llist(LinkedList *llist,int ind);
c8 delete_byInd_llist(LinkedList *llist,int ind);
c8 reverse_llist(LinkedList *llist);
u32_ds get_count_llist(LinkedList *llist);
c8 copy_llist(LinkedList *llist,LinkedList **new_llist);
void free_llist(LinkedList *llist);
c8 if_eleAddr_exsit_llist(LinkedList *llist,void *ele);


static c8 add_ele_emptyList(LinkedList *llist,void *ele);
Tree_node* runthrough_llist(LinkedList *llist,int ind);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif


