#ifndef __CIRCLELIST_H__
#define __CIRCLELIST_H__

#include "linkedList.h"

typedef struct cList {
	LinkedList linkList;
	char *name;
	c8 (*INSERT_ele_atTail)(struct cList*,void*);
	c8 (*INSERT_ele_atHead)(struct cList*,void*);
	void (*FREE_clist)(struct cList*);
	Tree_node* (*GET_tail_llist)(struct cList*);
	Tree_node* (*GET_head_llist)(struct cList*);
	void (*PRINT_clist)(struct cList*);
	c8 (*DEL_byAddr_clist)(struct cList*,Tree_node*);
	c8 (*DEL_byInd_clist)(struct cList*,int);
	u32_ds (*GET_COUNT_clist)(struct cList*);
	c8 (*IF_ELEaddr_exsit_clist)(struct cList*,void*);
	c8 ifinitial;
}CircleList;

c8 InitCircleList(CircleList *clist);
c8 CreateCircleList(CircleList **clist);
c8 add_ele_atTail_clist(CircleList *clist,void *ele);
c8 add_ele_atHead_clist(CircleList *clist,void *ele);
void free_clist(CircleList *clist);
Tree_node* get_head_clist(CircleList *clist);
Tree_node* get_tail_clist(CircleList *clist);
void print_clist_main(CircleList *clist);
void print_clist(CircleList *clist);
c8 del_byAddr_clist(CircleList *clist,Tree_node *addr);
c8 delete_byInd_clist(CircleList *clist,int ind); 
u32_ds get_count_clist(CircleList *clist);
c8 if_eleAddr_exsit_clist(CircleList *clist,void *ele); 

static void head_tail_connect(CircleList *clist);

#endif




