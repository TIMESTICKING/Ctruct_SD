#include <stdio.h>
#include "linkedList.h"

/**
	Description: 
		静态初始化链表 
	Arguments:
		nothing 
	Returns:
		1：success 
*/
c8 InitLinkedList(LinkedList *llist){
	InitTree(&(llist->tree));
	llist->ifinitial = 1;
	llist->name = "linkedlist_def";
	llist->tail = NULL_node;
	llist->INSERT_ele_byAddr = insert_ele_atMid;
	llist->INSERT_ele_atInd = add_ele_byInd_llist;
	llist->INSERT_ele_atTail = add_ele_atTail;
	llist->INSERT_ele_atHead = add_ele_atHead;
	llist->DEL_byAddr_llist = delete_node_llist;
	llist->PRINT_llist = print_llist;
	llist->GET_tail_llist = get_tailNode_llist;
	llist->GET_head_llist = get_headNode_llist;
	llist->GET_addr_byIndex = getAddr_llist;
	llist->DEL_byInd_llist = delete_byInd_llist;
	llist->ADD_llist_atHead = insert_llist_atHead;
	llist->ADD_llist_atTail = insert_llist_atTail;
	llist->ADD_llist_atInd = insert_llist_byInd;
	llist->COPY_llist = copy_llist;
	llist->REVERSE_llist = reverse_llist;
	llist->GET_COUNT_llist = get_count_llist;
	llist->IF_ELEaddr_exsit_llist = if_eleAddr_exsit_llist;
	llist->FREE_llist = free_llist;
	
	return ARR_OK;
}

/**
	Description: 
		动态创建链表 
	Arguments:
		二级指针 
	Returns:
		3：内存申请失败
		1：success 
*/
c8 CreateLinkedList(LinkedList **llist){
	*llist = (LinkedList*)SD_MALLOC(sizeof(LinkedList));
	if (*llist == (LinkedList*)0)	return ARR_MALLOC_FAIL;
	
	return InitLinkedList(*llist);
}

/**
	Description: 
		在某节点的前驱或后继插入新元素，新节点会在内部实现 
	Arguments:
		Tree_node *node：在该节点插入
		u8_ds position：PREVIEW_LLIST|NEXT_LLIST，前驱|后继
		void *ele：新元素地址 
	Returns:
		1：success
		-5：未初始化
		-1：下标position错误 
*/
c8 insert_ele_atMid(LinkedList *llist,Tree_node *node,u8_ds position,void *ele){
	Tree_node *new_node;
	Tree_node *temp;
	c8 sta;
	if (node == NULL_node)
		return ARR_FALSE;
	if(llist->ifinitial != 1 || node->ifinitial != 1)
		return ARR_UN_INIT;
	if (position != 0 && position != 1)
		return ARR_WRONG_INDEX;
	
	//插入新节点,如在AB之间插入C
	//若position=1，则A = node；什么都不做
	//若position=0，则A = node.prev
	if (position == PREVIEW_LLIST){
		node = (node->branches)[PREVIEW_LLIST];
		if (node == NULL_node){
			//需要头插
			return add_ele_atHead(llist,ele);
		}
	} 
	//保存B地址
	temp = get_branch_node(node,1);//获得A的后继节点，即B
	if (temp == NULL_node){
		//需要尾插
		return add_ele_atTail(llist,ele); 
	}
	sta = CreateNode(&new_node,2);//创建新节点
	if (sta != ARR_OK)	return sta;//返回错误
	put_in_data_node(new_node,ele);//存入数据到新节点
	//C节点的后继指向B
	add_node(new_node,1,temp);
	//把A的后继指向C
	add_node(node,1,new_node);
	//把C的前驱指向A
	add_node(new_node,0,node);
	//把B的前驱指向C
	add_node(temp,0,new_node);
	//节点数量+1
	(llist->tree).count++;
	
	return ARR_OK;
}

/**
	Description: 
		当链表为空时的插入方法 
	Arguments:
		nothing 
	Returns:
		1：success
		3：内存申请失败
		-5：未初始化链表 
*/
static c8 add_ele_emptyList(LinkedList *llist,void *ele){
	Tree_node *new_node;
	c8 sta;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;

	sta = CreateNode(&new_node,2);//创建新节点
	if (sta != ARR_OK)	return sta;//返回错误
	put_in_data_node(new_node,ele);//存入数据到新节点

	(llist->tree).head = new_node;//头节点指向它
	llist->tail = new_node;//尾节点指向它 
	(llist->tree).count++;
	
	return ARR_OK;
}

/**
	Description: 
		在链表尾部插入新元素 
	Arguments:
		void *ele：新元素的地址 
	Returns:
		1：success
		3：内存申请失败
		-5：未初始化链表 
*/
c8 add_ele_atTail(LinkedList *llist,void *ele){
	Tree_node *new_node;
	c8 sta;
	if (llist->tail == NULL_node)
		return add_ele_emptyList(llist,ele);
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
		
	sta = CreateNode(&new_node,2);//创建新节点
	if (sta != ARR_OK)	return sta;//返回错误
	put_in_data_node(new_node,ele);//存入数据到新节点
	
	add_node(llist->tail,NEXT_LLIST,new_node);//尾节点后继指向新节点
	add_node(new_node,PREVIEW_LLIST,llist->tail);//新节点前驱指向尾节点
	llist->tail = new_node;
	(llist->tree).count++;
	
	return ARR_OK;
}

/**
	Description: 
		在链表头部插入新元素 
	Arguments:
		void *ele：新元素的地址 
	Returns:
		1：success
		3：内存申请失败
		-5：未初始化链表 
*/
c8 add_ele_atHead(LinkedList *llist,void *ele){
	Tree_node *new_node;
	Tree_node *head;
	c8 sta;
	head = (llist->tree).head;//头节点重赋值，方便操作 
	if (head == NULL_node)
		return add_ele_emptyList(llist,ele);
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	sta = CreateNode(&new_node,2);//创建新节点
	if (sta != ARR_OK)	return sta;//返回错误
	put_in_data_node(new_node,ele);//存入数据到新节点
	
	add_node(head,PREVIEW_LLIST,new_node);//头节点的前驱指向新节点
	add_node(new_node,NEXT_LLIST,head);//新节点前驱指向尾节点
	(llist->tree).head = new_node;
	(llist->tree).count++;
	
	return ARR_OK;
}

/**
	Description: 
		在指定下标插入新元素 
	Arguments:
		int ind：下标，可负，-1为末元素
		void *ele：元素指针 
	Returns:
		-5：未初始化
		0：下标错误
		1：success 
*/
c8 add_ele_byInd_llist(LinkedList *llist,int ind,void *ele){
	Tree_node *temp;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;

	temp = runthrough_llist(llist,ind);
	return insert_ele_atMid(llist,temp,0,ele); 
}

/**
	Description: 
		在头部插入新链表 
	Arguments:
		LinkedList *add_llist：要插入到llist头部的链表 
	Returns:
		-2： add_llist和llist是同一个，不被允许
		-5：未初始化
		1：success 
*/
c8 insert_llist_atHead(LinkedList *llist,LinkedList *add_llist){
	Tree_node *head = (llist->tree).head;
	Tree_node *tail = add_llist->tail;
	if (llist == add_llist)
		return ARR_INPUT_SAME;
	if(llist->ifinitial != 1 || add_llist->ifinitial != 1)
		return ARR_UN_INIT;

	//头尾相连
	add_node(tail,NEXT_LLIST,head);
	add_node(head,PREVIEW_LLIST,tail);
	//头指针复位
	(llist->tree).head = (add_llist->tree).head;
	//+count
	(llist->tree).count += (add_llist->tree).count;
	
	return ARR_OK;
}

/**
	Description: 
		在尾部插入新链表 
	Arguments:
		LinkedList *add_llist：要插入到llist尾部的链表 
	Returns:
		-2： add_llist和llist是同一个，不被允许
		-5：未初始化
		1：success 
*/
c8 insert_llist_atTail(LinkedList *llist,LinkedList *add_llist){
	Tree_node *head = (add_llist->tree).head;
	Tree_node *tail = llist->tail;
	if (llist == add_llist)
		return ARR_INPUT_SAME;
	if(llist->ifinitial != 1 || add_llist->ifinitial != 1)
		return ARR_UN_INIT;

	//头尾相连
	add_node(tail,NEXT_LLIST,head);
	add_node(head,PREVIEW_LLIST,tail);
	//尾指针复位
	llist->tail = add_llist->tail;
	//+count
	(llist->tree).count += (add_llist->tree).count;
	
	return ARR_OK;
}

/**
	Description: 
		在ind处插入新链表 
	Arguments:
		int ind：下标，可负，-1为末元素
		LinkedList *add_llist：要在llist的ind处插入的新链表 
	Returns:
		-2： add_llist和llist相同，不被支持
		-5：未初始化
		-1：下标错误
		1：success 
*/
c8 insert_llist_byInd(LinkedList *llist,int ind,LinkedList *add_llist){
	Tree_node *res;
	Tree_node *prev;
	Tree_node *head = (add_llist->tree).head;
	Tree_node *tail = add_llist->tail;
	if (llist == add_llist)
		return ARR_INPUT_SAME;
	if(llist->ifinitial != 1 || add_llist->ifinitial != 1)
		return ARR_UN_INIT;

	res = runthrough_llist(llist,ind);
	if (res == NULL_node)	return ARR_WRONG_INDEX;
	
	prev = get_branch_node(res,PREVIEW_LLIST);
	if (prev == NULL_node)	return insert_llist_atHead(llist,add_llist);//执行头插
	//链接第一个节点 
	add_node(prev,NEXT_LLIST,head);
	add_node(head,PREVIEW_LLIST,prev);
	//链接第二个节点
	add_node(tail,NEXT_LLIST,res);
	add_node(res,PREVIEW_LLIST,tail);
	//+count
	(llist->tree).count += (add_llist->tree).count;
	
	return ARR_OK;
}

/**
	Description: 
		删除某个节点 
	Arguments:
		Tree_node *node_del：要删除的节点的地址 
	Returns:
		1：success
		-5：未初始化 
*/
c8 delete_node_llist(LinkedList *llist,Tree_node *node_del){
	Tree_node *next;
	Tree_node *prev;
	if(llist->ifinitial != 1 || node_del->ifinitial != 1)
		return ARR_UN_INIT;

	//删除节点ABC中的B 
	//保存B的后继，即C
	next = (node_del->branches)[NEXT_LLIST];
	//保存B的前驱，即A
	prev = (node_del->branches)[PREVIEW_LLIST];
	if (prev != NULL_node)
		//A的后继指向C/null
		add_node(prev,NEXT_LLIST,next);
	else{
		//删除头节点的情况 
		(llist->tree).head = next; 
	}
	if (next != NULL_node)
		//C的前驱指向A/null
		add_node(next,PREVIEW_LLIST,prev);
	else{
		//删除尾节点的情况
		llist->tail = prev; 
	}
	//节点个数--
	(llist->tree).count--;
	//销毁节点
	free_node(node_del);
	
	return ARR_OK;
}



/**
	Description: 
		返回链表头节点 
	Arguments:
		nothing 
	Returns:
		-5：未初始化 
*/
Tree_node* get_headNode_llist(LinkedList *llist){
	if(llist->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;
	return (llist->tree).head;
}

/**
	Description: 
		返回链表尾节点 
	Arguments:
		nothing 
	Returns:
		-5：未初始化 
*/
Tree_node* get_tailNode_llist(LinkedList *llist){
	if(llist->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;
	return llist->tail;
}

/**
	Description: 
		根据下标返回地址 
*/
Tree_node* runthrough_llist(LinkedList *llist,int ind){
	int i;
	Tree_node *n;
	
	if (ind>=0){
		//从头向后遍历 
		for(i=0,n=get_headNode_llist(llist);\
			i<ind && n!=NULL_node;\
			i++,n=(n->branches)[NEXT_LLIST]);
	}else{
		//从尾向前遍历
		for(i=-1,n=get_tailNode_llist(llist);\
			i>ind && n!=NULL_node;\
			i--,n=(n->branches)[PREVIEW_LLIST]);
	}
	return n;
}

/**
	Description: 
		某个元素指针是否在链表中 
	Arguments:
		ele：元素地址 
	Returns:
		-5：未初始化
		1：在链表中
		0：不在 
*/
c8 if_eleAddr_exsit_llist(LinkedList *llist,void *ele){
	Tree_node *n;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
		
	for(n=get_headNode_llist(llist);n!=NULL_node;n=get_branch_node(n,NEXT_LLIST)){
		if (n->ele_addr == ele)
			return ARR_OK;
	}
	return ARR_FALSE;
}


/**
	Description: 
		根据下标返回节点指针，下标可负，-1为末元素 
	Arguments:
		int ind：下标，可负 
	Returns:
		-5：未初始化
		X：指针 
*/
Tree_node* getAddr_llist(LinkedList *llist,int ind){
	if(llist->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;

	return runthrough_llist(llist,ind);	
}

/**
	Description: 
		根据下标删除节点，可负，-1为末元素 
	Arguments:
		nothing 
	Returns:
		-5：未初始化
		1：success 
*/
c8 delete_byInd_llist(LinkedList *llist,int ind){
	Tree_node *res;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	res = runthrough_llist(llist,ind);//查找地址
	if (res == NULL_node)	return ARR_WRONG_INDEX;
	
	return delete_node_llist(llist,res);
}

/**
	Description: 
		逆序链表 
	Returns:
		-5：未初始化
		1：success 
*/
c8 reverse_llist(LinkedList *llist){
	Tree_node *temp,*node_t;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	temp = llist->tail;
	llist->tail = (llist->tree).head;
	(llist->tree).head = temp;
	
	//把每个节点的prev和next对调
	for(temp=(llist->tree).head;temp!=NULL_node;temp=get_branch_node(temp,NEXT_LLIST)){
		node_t = (temp->branches)[0];
		(temp->branches)[0] = (temp->branches)[1];
		(temp->branches)[1] = node_t; 
	} 
	
	return ARR_OK;
}

/**
	Description: 
		返回链表长度 
	Arguments:
		nothing 
	Returns:
		-5：未初始化
		x:	长度 
*/
u32_ds get_count_llist(LinkedList *llist){
	if (llist->ifinitial != 1)	return ARR_UN_INIT;
	
	return (llist->tree).count;
}

/**
	Description: 
		拷贝链表，除了存储的元素 
	Arguments:
		nothing 
	Returns:
		-5：未初始化
		3：内存申请失败
		1：success 
*/
c8 copy_llist(LinkedList *llist,LinkedList **new_llist){
	LinkedList *newl;
	Tree_node *last = NULL_node;
	Tree_node *cur;
	Tree_node *newn;
	u32_ds n,length = (llist->tree).count;
	c8 sta;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	sta = CreateLinkedList(&newl);
	if (sta != ARR_OK)	return sta;
	(newl->tree).count = length;
	//预先申请length-1的长度的队列 
	
	for(cur=(llist->tree).head,n=0;cur!=NULL_node && n<length;cur=get_branch_node(cur,NEXT_LLIST),n++){
		sta = CreateNode(&newn,2);
		if (sta != ARR_OK){
			free_llist(newl);
			return sta;//节点申请失败
		}
		newn->ele_addr = cur->ele_addr;//元素地址赋值
		if (n!=0){
			//把上个新节点的next指向当前的新节点,把当前的prev指向上一个 
			add_node(last,NEXT_LLIST,newn);
			add_node(newn,PREVIEW_LLIST,last);
		}else{
			(newl->tree).head = newn;//设置头节点 
		}
		if (n == length-1){
			newl->tail = newn;//设置尾节点 
		}
		last = newn; 
	}
	*new_llist = newl;
	
	return ARR_OK;
}

void free_llist(LinkedList *llist){
	if(llist->ifinitial == 1)
		free_tree(&(llist->tree));
	SD_FREE(llist);
}

void print_llist_main(LinkedList *llist){
	SD_PRINT("=>linkedlist=>ifinitial:	%d",llist->ifinitial);
	SD_PRINT("=>linkedlist=>head node:	%#x",(llist->tree).head);
	SD_PRINT("=>linkedlist=>tail node:	%#x",llist->tail);
	print_tree_main(&(llist->tree));
}

void print_llist(LinkedList *llist){
	SD_PRINT_HEAD("LinkedList",llist->name);
	print_llist_main(llist);
	SD_PRINT_END;
}
