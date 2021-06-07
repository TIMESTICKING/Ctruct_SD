#include "circleList.h"


/**
	Description: 
		静态初始化循环链表 
	Arguments:
		nothing 
	Returns:
		1：success 
*/
c8 InitCircleList(CircleList *clist){
	InitLinkedList(&(clist->linkList));	
	clist->name = "circleList_def";
	clist->ifinitial = 1;
	
	clist->INSERT_ele_atTail = add_ele_atTail_clist;
	clist->INSERT_ele_atHead = add_ele_atHead_clist;
	clist->FREE_clist = free_clist;
	clist->GET_tail_llist = get_tail_clist;
	clist->GET_head_llist = get_head_clist;
	clist->PRINT_clist = print_clist;
	clist->DEL_byAddr_clist = del_byAddr_clist;
	clist->DEL_byInd_clist = delete_byInd_clist;
	clist->GET_COUNT_clist = get_count_clist;
	clist->IF_ELEaddr_exsit_clist = if_eleAddr_exsit_clist;
	
	return ARR_OK;
}

/**
	Description: 
		动态初始化循环链表 
	Arguments:
		nothing 
	Returns:
		1：success 
*/
c8 CreateCircleList(CircleList **clist){
	*clist = (CircleList*)SD_MALLOC(sizeof(CircleList));
	if (*clist == (CircleList*)0)	return ARR_MALLOC_FAIL;
	
	return InitCircleList(*clist);
}

static void head_tail_connect(CircleList *clist){
	Tree_node *tail,*head;
	head = get_headNode_llist(&(clist->linkList));
	tail = get_tailNode_llist(&(clist->linkList));
	(head->branches)[PREVIEW_LLIST] = tail;
	(tail->branches)[NEXT_LLIST] = head;
}

/**
	Description: 
		尾插 
	Arguments:
		ele：元素地址 
	Returns:
		-5：未初始化
		1：success 
		3：内存申请失败
*/
c8 add_ele_atTail_clist(CircleList *clist,void *ele){
	c8 sta;
	if (clist->ifinitial != 1)
		return ARR_UN_INIT;
		
	sta = add_ele_atTail(&(clist->linkList),ele);
	if (sta != ARR_OK)	return sta;
	
	//头尾相连
	head_tail_connect(clist);
	
	return ARR_OK;
}

/**
	Description: 
		头插 
	Arguments:
		ele：元素地址 
	Returns:
		-5：未初始化
		1：success 
		3：内存申请失败
*/
c8 add_ele_atHead_clist(CircleList *clist,void *ele){
	c8 sta;
	if (clist->ifinitial != 1)
		return ARR_UN_INIT;
		
	sta = add_ele_atHead(&(clist->linkList),ele);
	if (sta != ARR_OK)	return sta;
	
	//头尾相连
	head_tail_connect(clist);
	
	return ARR_OK;
}

/**
	Description: 
		销毁循环链表 
*/
void free_clist(CircleList *clist){
	if (clist->ifinitial != 1)
		free_llist(&(clist->linkList));
	SD_FREE(clist);
} 

/**
	Description: 
		获取头节点 
	Returns:
		-5：未初始化 
*/
Tree_node* get_head_clist(CircleList *clist){
	return get_headNode_llist(&(clist->linkList));
}

/**
	Description: 
		获取尾节点 
	Returns:
		-5：未初始化 
*/
Tree_node* get_tail_clist(CircleList *clist){
	return get_tailNode_llist(&(clist->linkList));
}

/**
	Description: 
		元素地址是否存在于链表 
	Arguments:
		ele：元素指针 
	Returns:
		-5：未初始化
		1：在链表中
		0：不在 		 
*/
c8 if_eleAddr_exsit_clist(CircleList *clist,void *ele){
	Tree_node *n;
	u32_ds i=0;
	u32_ds length = get_count_clist(clist);
	if (clist->ifinitial != 1)
		return ARR_UN_INIT;

	for(n=get_head_clist(clist);i<length;n=get_branch_node(n,NEXT_LLIST),i++){
		if (n->ele_addr == ele)
			return ARR_OK;
	}
	return ARR_FALSE;
}


/**
	Description: 
		根据地址删除节点 
	Arguments:
		addr：节点地址 
	Returns:
		-5：未初始化
		1：success 
*/
c8 del_byAddr_clist(CircleList *clist,Tree_node *addr){
	Tree_node *prev,*next;
	LinkedList *llist = &(clist->linkList);
	if (clist->ifinitial != 1 || addr->ifinitial != 1)	return ARR_UN_INIT;	
	
	(llist->tree).count--;
	prev = (addr->branches)[PREVIEW_LLIST];
	next = (addr->branches)[NEXT_LLIST];
	free_node(addr);//释放节点 
	if (llist->tail == addr && (llist->tree).head == addr){
		//仅此节点
		llist->tail = NULL_node;
		(llist->tree).head = NULL_node;
		return ARR_OK;
	}
	//连接prev和next
	add_node(prev,NEXT_LLIST,next);
	add_node(next,PREVIEW_LLIST,prev);
	if (addr == llist->tail){
		//删除的节点是尾节点
		llist->tail = prev; 
	}else if (addr == (llist->tree).head){
		//删除的节点是头节点
		(llist->tree).head = next; 
	}
	
	return ARR_OK;
}

/**
	Description: 
		根据下标删除节点 
	Arguments:
		ind：下标，可负，-1为末尾 
	Returns:
		-5：未初始化
		1：success 
*/
c8 delete_byInd_clist(CircleList *clist,int ind){
	Tree_node *res;
	if(clist->ifinitial != 1)
		return ARR_UN_INIT;
	
	res = runthrough_llist(&(clist->linkList),ind);//查找地址
	if (res == NULL_node)	return ARR_EMPTY_CLIST;
	
	return del_byAddr_clist(clist,res);
}

/**
	Description: 
		返回链表长度 
	Arguments:
		nothing
	Returns:
		-5：未初始化
		x：长度 
*/
u32_ds get_count_clist(CircleList *clist){
	if (clist->ifinitial != 1)	return ARR_UN_INIT;
	
	return ((clist->linkList).tree).count;
}

void print_clist_main(CircleList *clist){
	SD_PRINT("=>CircleLinkedList=>ifinitial:	%d",clist->ifinitial);
	print_llist_main(&(clist->linkList));
}

void print_clist(CircleList *clist){
	SD_PRINT_HEAD("CircleLinkedList",clist->name);
	print_clist_main(clist);
	SD_PRINT_END;
}




