#include <stdio.h>
#include "LinkedList_SD.h"

/**
	Description: 
		��̬��ʼ������ 
	Arguments:
		nothing 
	Returns:
		1��success 
*/
c8 InitLinkedList_SD(LinkedList_SD *llist){
	CreateTree(&(llist->tree));
	llist->ifinitial = 1;
	llist->name = "LinkedList_SD_def";
	llist->tail = NULL_node;
	llist->INSERT_ele_byAddr = insert_ele_atMid;
	llist->INSERT_ele_atInd = add_ele_byInd_llist;
	llist->INSERT_ele_atTail = add_ele_atTail;
	llist->INSERT_ele_atHead = add_ele_atHead;
	llist->DEL_byAddr_llist = delete_node_llist;
	llist->PRINT = print_llist;
	llist->GET_tail_llist = get_tailNode_llist;
	llist->GET_head_llist = get_headNode_llist;
	llist->GET_addr_byIndex = getAddr_llist;
	llist->DEL_byInd_llist = delete_byInd_llist;
	llist->ADD_llist_atHead = insert_llist_atHead;
	llist->ADD_llist_atTail = insert_llist_atTail;
	llist->ADD_llist_atInd = insert_llist_byInd;
	llist->COPY_llist = copy_llist;
	llist->REVERSE_llist = reverse_llist;
	llist->COUNT = get_count_llist;
	llist->IF_ELEaddr_exsit_llist = if_eleAddr_exsit_llist;
	llist->FREE = free_llist;
	
	return ARR_OK;
}

/**
	Description: 
		��̬�������� 
	Arguments:
		����ָ�� 
	Returns:
		3���ڴ�����ʧ��
		1��success 
*/
c8 CreateLinkedList_SD(LinkedList_SD **llist){
	*llist = (LinkedList_SD*)SD_MALLOC(sizeof(LinkedList_SD));
	if (*llist == (LinkedList_SD*)0)	return ARR_MALLOC_FAIL;
	
	return InitLinkedList_SD(*llist);
}

/**
	Description: 
		��ĳ�ڵ��ǰ�����̲�����Ԫ�أ��½ڵ�����ڲ�ʵ�� 
	Arguments:
		Tree_node *node���ڸýڵ����
		u8_ds position��PREVIEW_LLIST|NEXT_LLIST��ǰ��|���
		void *ele����Ԫ�ص�ַ 
	Returns:
		1��success
		-5��δ��ʼ��
		-1���±�position���� 
*/
c8 insert_ele_atMid(LinkedList_SD *llist,Tree_node *node,u8_ds position,void *ele){
	Tree_node *new_node;
	Tree_node *temp;
	c8 sta;
	if (node == NULL_node)
		return ARR_FALSE;
	if(llist->ifinitial != 1 || node->ifinitial != 1)
		return ARR_UN_INIT;
	if (position != 0 && position != 1)
		return ARR_WRONG_INDEX;
	
	//�����½ڵ�,����AB֮�����C
	//��position=1����A = node��ʲô������
	//��position=0����A = node.prev
	if (position == PREV_LLIST){
		node = (node->branches)[PREV_LLIST];
		if (node == NULL_node){
			//��Ҫͷ��
			return add_ele_atHead(llist,ele);
		}
	} 
	//����B��ַ
	temp = get_branch_node(node,1);//���A�ĺ�̽ڵ㣬��B
	if (temp == NULL_node){
		//��Ҫβ��
		return add_ele_atTail(llist,ele); 
	}
	sta = CreateNode(&new_node,2);//�����½ڵ�
	if (sta != ARR_OK)	return sta;//���ش���
	put_in_data_node(new_node,ele);//�������ݵ��½ڵ�
	//C�ڵ�ĺ��ָ��B
	add_node(new_node,1,temp);
	//��A�ĺ��ָ��C
	add_node(node,1,new_node);
	//��C��ǰ��ָ��A
	add_node(new_node,0,node);
	//��B��ǰ��ָ��C
	add_node(temp,0,new_node);
	//�ڵ�����+1
    (llist->tree)->count++;
	
	return ARR_OK;
}

/**
	Description: 
		������Ϊ��ʱ�Ĳ��뷽�� 
	Arguments:
		nothing 
	Returns:
		1��success
		3���ڴ�����ʧ��
		-5��δ��ʼ������ 
*/
static c8 add_ele_emptyList(LinkedList_SD *llist,void *ele){
	Tree_node *new_node;
	c8 sta;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;

	sta = CreateNode(&new_node,2);//�����½ڵ�
	if (sta != ARR_OK)	return sta;//���ش���
	put_in_data_node(new_node,ele);//�������ݵ��½ڵ�

    (llist->tree)->head = new_node;//ͷ�ڵ�ָ����
	llist->tail = new_node;//β�ڵ�ָ���� 
    (llist->tree)->count++;
	
	return ARR_OK;
}

/**
	Description: 
		������β��������Ԫ�� 
	Arguments:
		void *ele����Ԫ�صĵ�ַ 
	Returns:
		1��success
		3���ڴ�����ʧ��
		-5��δ��ʼ������ 
*/
c8 add_ele_atTail(LinkedList_SD *llist,void *ele){
	Tree_node *new_node;
	c8 sta;
	if (llist->tail == NULL_node)
		return add_ele_emptyList(llist,ele);
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
		
	sta = CreateNode(&new_node,2);//�����½ڵ�
	if (sta != ARR_OK)	return sta;//���ش���
	put_in_data_node(new_node,ele);//�������ݵ��½ڵ�
	
	add_node(llist->tail,NEXT_LLIST,new_node);//β�ڵ���ָ���½ڵ�
	add_node(new_node,PREV_LLIST,llist->tail);//�½ڵ�ǰ��ָ��β�ڵ�
	llist->tail = new_node;
    (llist->tree)->count++;
	
	return ARR_OK;
}

/**
	Description: 
		������ͷ��������Ԫ�� 
	Arguments:
		void *ele����Ԫ�صĵ�ַ 
	Returns:
		1��success
		3���ڴ�����ʧ��
		-5��δ��ʼ������ 
*/
c8 add_ele_atHead(LinkedList_SD *llist,void *ele){
	Tree_node *new_node;
	Tree_node *head;
	c8 sta;
    head = (llist->tree)->head;//ͷ�ڵ��ظ�ֵ���������
	if (head == NULL_node)
		return add_ele_emptyList(llist,ele);
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	sta = CreateNode(&new_node,2);//�����½ڵ�
	if (sta != ARR_OK)	return sta;//���ش���
	put_in_data_node(new_node,ele);//�������ݵ��½ڵ�
	
	add_node(head,PREV_LLIST,new_node);//ͷ�ڵ��ǰ��ָ���½ڵ�
	add_node(new_node,NEXT_LLIST,head);//�½ڵ�ǰ��ָ��β�ڵ�
    (llist->tree)->head = new_node;
    (llist->tree)->count++;
	
	return ARR_OK;
}

/**
	Description: 
		��ָ���±������Ԫ�� 
	Arguments:
		int ind���±꣬�ɸ���-1ΪĩԪ��
		void *ele��Ԫ��ָ�� 
	Returns:
		-5��δ��ʼ��
		0���±����
		1��success 
*/
c8 add_ele_byInd_llist(LinkedList_SD *llist,int ind,void *ele){
	Tree_node *temp;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;

	temp = runthrough_llist(llist,ind);
	return insert_ele_atMid(llist,temp,0,ele); 
}

/**
	Description: 
		��ͷ������������ 
	Arguments:
		LinkedList_SD *add_llist��Ҫ���뵽llistͷ�������� 
	Returns:
		-2�� add_llist��llist��ͬһ������������
		-5��δ��ʼ��
		1��success 
*/
c8 insert_llist_atHead(LinkedList_SD *llist,LinkedList_SD *add_llist){
    Tree_node *head = (llist->tree)->head;
	Tree_node *tail = add_llist->tail;
	if (llist == add_llist)
		return ARR_INPUT_SAME;
	if(llist->ifinitial != 1 || add_llist->ifinitial != 1)
		return ARR_UN_INIT;

	//ͷβ����
	add_node(tail,NEXT_LLIST,head);
	add_node(head,PREV_LLIST,tail);
	//ͷָ�븴λ
    (llist->tree)->head = (add_llist->tree)->head;
	//+count
    (llist->tree)->count += (add_llist->tree)->count;
	
	return ARR_OK;
}

/**
	Description: 
		��β������������ 
	Arguments:
		LinkedList_SD *add_llist��Ҫ���뵽llistβ�������� 
	Returns:
		-2�� add_llist��llist��ͬһ������������
		-5��δ��ʼ��
		1��success 
*/
c8 insert_llist_atTail(LinkedList_SD *llist,LinkedList_SD *add_llist){
    Tree_node *head = (add_llist->tree)->head;
	Tree_node *tail = llist->tail;
	if (llist == add_llist)
		return ARR_INPUT_SAME;
	if(llist->ifinitial != 1 || add_llist->ifinitial != 1)
		return ARR_UN_INIT;

	//ͷβ����
	add_node(tail,NEXT_LLIST,head);
	add_node(head,PREV_LLIST,tail);
	//βָ�븴λ
	llist->tail = add_llist->tail;
	//+count
    (llist->tree)->count += (add_llist->tree)->count;
	
	return ARR_OK;
}

/**
	Description: 
		��ind������������ 
	Arguments:
		int ind���±꣬�ɸ���-1ΪĩԪ��
		LinkedList_SD *add_llist��Ҫ��llist��ind������������� 
	Returns:
		-2�� add_llist��llist��ͬ������֧��
		-5��δ��ʼ��
		-1���±����
		1��success 
*/
c8 insert_llist_byInd(LinkedList_SD *llist,int ind,LinkedList_SD *add_llist){
	Tree_node *res;
	Tree_node *prev;
    Tree_node *head = (add_llist->tree)->head;
	Tree_node *tail = add_llist->tail;
	if (llist == add_llist)
		return ARR_INPUT_SAME;
	if(llist->ifinitial != 1 || add_llist->ifinitial != 1)
		return ARR_UN_INIT;

	res = runthrough_llist(llist,ind);
	if (res == NULL_node)	return ARR_WRONG_INDEX;
	
	prev = get_branch_node(res,PREV_LLIST);
	if (prev == NULL_node)	return insert_llist_atHead(llist,add_llist);//ִ��ͷ��
	//���ӵ�һ���ڵ� 
	add_node(prev,NEXT_LLIST,head);
	add_node(head,PREV_LLIST,prev);
	//���ӵڶ����ڵ�
	add_node(tail,NEXT_LLIST,res);
	add_node(res,PREV_LLIST,tail);
	//+count
    (llist->tree)->count += (add_llist->tree)->count;
	
	return ARR_OK;
}

/**
	Description: 
		ɾ��ĳ���ڵ� 
	Arguments:
		Tree_node *node_del��Ҫɾ���Ľڵ�ĵ�ַ 
	Returns:
		1��success
		-5��δ��ʼ�� 
*/
c8 delete_node_llist(LinkedList_SD *llist,Tree_node *node_del){
	Tree_node *next;
	Tree_node *prev;
	if(llist->ifinitial != 1 || node_del->ifinitial != 1)
		return ARR_UN_INIT;

	//ɾ���ڵ�ABC�е�B 
	//����B�ĺ�̣���C
	next = (node_del->branches)[NEXT_LLIST];
	//����B��ǰ������A
	prev = (node_del->branches)[PREV_LLIST];
	if (prev != NULL_node)
		//A�ĺ��ָ��C/null
		add_node(prev,NEXT_LLIST,next);
	else{
		//ɾ��ͷ�ڵ����� 
        (llist->tree)->head = next;
	}
	if (next != NULL_node)
		//C��ǰ��ָ��A/null
		add_node(next,PREV_LLIST,prev);
	else{
		//ɾ��β�ڵ�����
		llist->tail = prev; 
	}
	//�ڵ����--
    (llist->tree)->count--;
	//���ٽڵ�
	free_node(node_del);
	
	return ARR_OK;
}



/**
	Description: 
		��������ͷ�ڵ� 
	Arguments:
		nothing 
	Returns:
		-5��δ��ʼ�� 
*/
Tree_node* get_headNode_llist(LinkedList_SD *llist){
	if(llist->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;
    return (llist->tree)->head;
}

/**
	Description: 
		��������β�ڵ� 
	Arguments:
		nothing 
	Returns:
		-5��δ��ʼ�� 
*/
Tree_node* get_tailNode_llist(LinkedList_SD *llist){
	if(llist->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;
	return llist->tail;
}

/**
	Description: 
		�����±귵�ص�ַ 
*/
Tree_node* runthrough_llist(LinkedList_SD *llist,int ind){
	int i;
	Tree_node *n;
	
	if (ind>=0){
		//��ͷ������ 
		for(i=0,n=get_headNode_llist(llist);\
			i<ind && n!=NULL_node;\
			i++,n=(n->branches)[NEXT_LLIST]);
	}else{
		//��β��ǰ����
		for(i=-1,n=get_tailNode_llist(llist);\
			i>ind && n!=NULL_node;\
			i--,n=(n->branches)[PREV_LLIST]);
	}
	return n;
}

/**
	Description: 
		ĳ��Ԫ��ָ���Ƿ��������� 
	Arguments:
		ele��Ԫ�ص�ַ 
	Returns:
		-5��δ��ʼ��
		1����������
		0������ 
*/
c8 if_eleAddr_exsit_llist(LinkedList_SD *llist,void *ele){
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
		�����±귵�ؽڵ�ָ�룬�±�ɸ���-1ΪĩԪ�� 
	Arguments:
		int ind���±꣬�ɸ� 
	Returns:
		-5��δ��ʼ��
		X��ָ�� 
*/
Tree_node* getAddr_llist(LinkedList_SD *llist,int ind){
	if(llist->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;

	return runthrough_llist(llist,ind);	
}

/**
	Description: 
		�����±�ɾ���ڵ㣬�ɸ���-1ΪĩԪ�� 
	Arguments:
		nothing 
	Returns:
		-5��δ��ʼ��
		1��success 
*/
c8 delete_byInd_llist(LinkedList_SD *llist,int ind){
	Tree_node *res;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	res = runthrough_llist(llist,ind);//���ҵ�ַ
	if (res == NULL_node)	return ARR_WRONG_INDEX;
	
	return delete_node_llist(llist,res);
}

/**
	Description: 
		�������� 
	Returns:
		-5��δ��ʼ��
		1��success 
*/
c8 reverse_llist(LinkedList_SD *llist){
	Tree_node *temp,*node_t;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	temp = llist->tail;
    llist->tail = (llist->tree)->head;
    (llist->tree)->head = temp;
	
	//��ÿ���ڵ��prev��next�Ե�
    for(temp=(llist->tree)->head;temp!=NULL_node;temp=get_branch_node(temp,NEXT_LLIST)){
		node_t = (temp->branches)[0];
		(temp->branches)[0] = (temp->branches)[1];
		(temp->branches)[1] = node_t; 
	} 
	
	return ARR_OK;
}

/**
	Description: 
		������������ 
	Arguments:
		nothing 
	Returns:
		-5��δ��ʼ��
		x:	���� 
*/
u32_ds get_count_llist(LinkedList_SD *llist){
	if (llist->ifinitial != 1)	return ARR_UN_INIT;
	
    return (llist->tree)->count;
}

/**
	Description: 
		�������������˴洢��Ԫ�� 
	Arguments:
		nothing 
	Returns:
		-5��δ��ʼ��
		3���ڴ�����ʧ��
		1��success 
*/
c8 copy_llist(LinkedList_SD *llist,LinkedList_SD **new_llist){
	LinkedList_SD *newl;
	Tree_node *last = NULL_node;
	Tree_node *cur;
	Tree_node *newn;
    u32_ds n,length = (llist->tree)->count;
	c8 sta;
	if(llist->ifinitial != 1)
		return ARR_UN_INIT;
	
	sta = CreateLinkedList_SD(&newl);
	if (sta != ARR_OK)	return sta;
    (newl->tree)->count = length;
	//Ԥ������length-1�ĳ��ȵĶ��� 
	
    for(cur=(llist->tree)->head,n=0;cur!=NULL_node && n<length;cur=get_branch_node(cur,NEXT_LLIST),n++){
		sta = CreateNode(&newn,2);
		if (sta != ARR_OK){
			free_llist(newl);
			return sta;//�ڵ�����ʧ��
		}
		newn->ele_addr = cur->ele_addr;//Ԫ�ص�ַ��ֵ
		if (n!=0){
			//���ϸ��½ڵ��nextָ��ǰ���½ڵ�,�ѵ�ǰ��prevָ����һ�� 
			add_node(last,NEXT_LLIST,newn);
			add_node(newn,PREV_LLIST,last);
		}else{
            (newl->tree)->head = newn;//����ͷ�ڵ�
		}
		if (n == length-1){
			newl->tail = newn;//����β�ڵ� 
		}
		last = newn; 
	}
	*new_llist = newl;
	
	return ARR_OK;
}

void free_llist(LinkedList_SD *llist){
    if(llist->ifinitial == 1){
		free_tree(llist->tree);
    }
	SD_FREE(llist);
}

void print_llist_main(LinkedList_SD *llist){
	SD_PRINT("=>LinkedList_SD=>ifinitial:	%d",llist->ifinitial);
    SD_PRINT("=>LinkedList_SD=>head node:	%#x",(llist->tree)->head);
	SD_PRINT("=>LinkedList_SD=>tail node:	%#x",llist->tail);
	print_tree_main(llist->tree);
}

void print_llist(LinkedList_SD *llist){
	SD_PRINT_HEAD("LinkedList_SD",llist->name);
	print_llist_main(llist);
	SD_PRINT_END;
}
