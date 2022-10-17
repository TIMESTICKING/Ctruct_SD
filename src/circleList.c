#include <stdio.h>
#include "circleList.h"


/**
	Description: 
		��̬��ʼ��ѭ������ 
	Arguments:
		nothing 
	Returns:
		1��success 
*/
c8 InitCircleList(CircleList *clist){
	CreateLinkedList_SD(&(clist->linkList));
	clist->name = "circleList_def";
	clist->ifinitial = 1;
	
	clist->INSERT_ele_atTail = add_ele_atTail_clist;
	clist->INSERT_ele_atHead = add_ele_atHead_clist;
	clist->FREE = free_clist;
	clist->GET_tail_llist = get_tail_clist;
	clist->GET_head_llist = get_head_clist;
	clist->PRINT = print_clist;
	clist->DEL_byAddr_clist = del_byAddr_clist;
	clist->DEL_byInd_clist = delete_byInd_clist;
	clist->COUNT = get_count_clist;
	clist->IF_ELEaddr_exsit_clist = if_eleAddr_exsit_clist;
	
	return ARR_OK;
}

/**
	Description: 
		��̬��ʼ��ѭ������ 
	Arguments:
		nothing 
	Returns:
		1��success 
*/
c8 CreateCircleList(CircleList **clist){
	*clist = (CircleList*)SD_MALLOC(sizeof(CircleList));
	if (*clist == (CircleList*)0)	return ARR_MALLOC_FAIL;
	
	return InitCircleList(*clist);
}

static void head_tail_connect(CircleList *clist){
	Tree_node *tail,*head;
	head = get_headNode_llist(clist->linkList);
	tail = get_tailNode_llist(clist->linkList);
	(head->branches)[PREV_LLIST] = tail;
	(tail->branches)[NEXT_LLIST] = head;
}

/**
	Description: 
		β�� 
	Arguments:
		ele��Ԫ�ص�ַ 
	Returns:
		-5��δ��ʼ��
		1��success 
		3���ڴ�����ʧ��
*/
c8 add_ele_atTail_clist(CircleList *clist,void *ele){
	c8 sta;
	if (clist->ifinitial != 1)
		return ARR_UN_INIT;
		
	sta = add_ele_atTail(clist->linkList,ele);
	if (sta != ARR_OK)	return sta;
	
	//ͷβ����
	head_tail_connect(clist);
	
	return ARR_OK;
}

/**
	Description: 
		ͷ�� 
	Arguments:
		ele��Ԫ�ص�ַ 
	Returns:
		-5��δ��ʼ��
		1��success 
		3���ڴ�����ʧ��
*/
c8 add_ele_atHead_clist(CircleList *clist,void *ele){
	c8 sta;
	if (clist->ifinitial != 1)
		return ARR_UN_INIT;
		
	sta = add_ele_atHead(clist->linkList,ele);
	if (sta != ARR_OK)	return sta;
	
	//ͷβ����
	head_tail_connect(clist);
	
	return ARR_OK;
}

/**
	Description: 
		����ѭ������ 
*/
void free_clist(CircleList *clist){
	if (clist->ifinitial != 1)
		free_llist(clist->linkList);
	SD_FREE(clist);
} 

/**
	Description: 
		��ȡͷ�ڵ� 
	Returns:
		-5��δ��ʼ�� 
*/
Tree_node* get_head_clist(CircleList *clist){
	return get_headNode_llist(clist->linkList);
}

/**
	Description: 
		��ȡβ�ڵ� 
	Returns:
		-5��δ��ʼ�� 
*/
Tree_node* get_tail_clist(CircleList *clist){
	return get_tailNode_llist(clist->linkList);
}

/**
	Description: 
		Ԫ�ص�ַ�Ƿ���������� 
	Arguments:
		ele��Ԫ��ָ�� 
	Returns:
		-5��δ��ʼ��
		1����������
		0������ 		 
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
		���ݵ�ַɾ���ڵ� 
	Arguments:
		addr���ڵ��ַ 
	Returns:
		-5��δ��ʼ��
		1��success 
*/
c8 del_byAddr_clist(CircleList *clist,Tree_node *addr){
	Tree_node *prev,*next;
	LinkedList_SD *llist = clist->linkList;
	if (clist->ifinitial != 1 || addr->ifinitial != 1)	return ARR_UN_INIT;	
	
    (llist->tree)->count--;
	prev = (addr->branches)[PREV_LLIST];
	next = (addr->branches)[NEXT_LLIST];
	free_node(addr);//�ͷŽڵ� 
    if (llist->tail == addr && (llist->tree)->head == addr){
		//���˽ڵ�
		llist->tail = NULL_node;
        (llist->tree)->head = NULL_node;
		return ARR_OK;
	}
	//����prev��next
	add_node(prev,NEXT_LLIST,next);
	add_node(next,PREV_LLIST,prev);
	if (addr == llist->tail){
		//ɾ���Ľڵ���β�ڵ�
		llist->tail = prev; 
	}else if (addr == (llist->tree)->head){
		//ɾ���Ľڵ���ͷ�ڵ�
		(llist->tree)->head = next;
	}
	
	return ARR_OK;
}

/**
	Description: 
		�����±�ɾ���ڵ� 
	Arguments:
		ind���±꣬�ɸ���-1Ϊĩβ 
	Returns:
		-5��δ��ʼ��
		1��success 
*/
c8 delete_byInd_clist(CircleList *clist,int ind){
	Tree_node *res;
	if(clist->ifinitial != 1)
		return ARR_UN_INIT;
	
	res = runthrough_llist(clist->linkList,ind);//���ҵ�ַ
	if (res == NULL_node)	return ARR_EMPTY_CLIST;
	
	return del_byAddr_clist(clist,res);
}

/**
	Description: 
		������������ 
	Arguments:
		nothing
	Returns:
		-5��δ��ʼ��
		x������ 
*/
u32_ds get_count_clist(CircleList *clist){
	if (clist->ifinitial != 1)	return ARR_UN_INIT;
	
    return ((clist->linkList)->tree)->count;
}

void print_clist_main(CircleList *clist){
	SD_PRINT("=>CircleLinkedList_SD=>ifinitial:	%d",clist->ifinitial);
	print_llist_main(clist->linkList);
}

void print_clist(CircleList *clist){
	SD_PRINT_HEAD("CircleLinkedList_SD",clist->name);
	print_clist_main(clist);
	SD_PRINT_END;
}




