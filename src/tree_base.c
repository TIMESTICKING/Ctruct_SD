#include <stdio.h>
#include "tree_base.h"
#include <stdlib.h>

/**
	Description: 
		��̬��ʼ���� ��ͬʱҲ��̬��ʼ����ͷ�ڵ� 
	Arguments:
		u32_ds head_node_branch_num��ͷ�ڵ�ķֲ��� 
	Returns:
		1: success
*/
c8 InitTree(Tree *tree){
	tree->head = NULL_node;
	tree->count = 0;
	tree->ifinitial = 1;
	tree->name = "tree_def";
	tree->EDIT_Data_node = put_in_data_node;
	tree->EDIT_branch = add_node_tree;
	tree->DELETE_branch = delete_node_tree;
	tree->COUNT = count_tree;
	tree->GET_BRANCH_node = get_branch_node;
	tree->PRINT = print_tree;
	tree->FREE = free_tree;
	tree->SET_head = set_head_tree;
	
	return ARR_OK;
}

/**
	Description: 
		��̬������ ��ͬʱҲ��̬��ʼ����ͷ�ڵ� 
	Arguments:
		u32_ds head_node_branch_num��ͷ�ڵ�ķֲ���
	Returns:
		1: success
		3: �ڴ�����ʧ�� 
*/
c8 CreateTree(Tree **tree){
	*tree = (Tree*)SD_MALLOC(sizeof(Tree)); 
	if (*tree == (Tree*)0)
		return ARR_MALLOC_FAIL;
		
	return InitTree(*tree);
}

/**
	Description: 
		��̬��ʼ���ڵ� 
	Arguments:
		u32_ds branch_num�� �ڵ��֧���� 
	Returns:
		1��success
		3���ڴ�����ʧ�� 
*/
c8 InitNode(Tree_node *node,u32_ds branch_num){
	u32_ds i;
	node->branches = (Tree_node**)SD_MALLOC(sizeof(Tree_node*) * branch_num);
	if (node->branches == (Tree_node**)0)
		return ARR_MALLOC_FAIL;
	
	for(i=0;i<branch_num;i++){
		(node->branches)[i] = NULL_node;
	}
	node->EDIT_Data_node = put_in_data_node;
	node->GET_BRANCH_node = get_branch_node;
	node->EDIT_branch = add_node;
	node->DELETE_branch = delete_node_tree;
	node->FREE_node= free_node;
	node->PRINT_node = print_treeNode;
	node->ele_addr = NULL_void;
	node->branch_num = branch_num;
	node->ifinitial = 1;
	
	return ARR_OK;
}

/**
	Description: 
		��̬�����ڵ� 
	Arguments:
		u32_ds branch_num���ڵ��֧���� 
	Returns:
		1��success
		3���ڴ�����ʧ�� 
*/
c8 CreateNode(Tree_node **node,u32_ds branch_num){
	*node = (Tree_node*)SD_MALLOC(sizeof(Tree_node));
	if (*node == NULL_node)
		return ARR_MALLOC_FAIL;
	
	if (InitNode(*node,branch_num) == ARR_MALLOC_FAIL){
		SD_FREE(*node);
		return ARR_MALLOC_FAIL;
	}
	return ARR_OK;
}

/**
	Description: 
		���ڵ�������ݵ�ָ�� 
	Arguments:
		void *ele�����ݵ�ַ 
	Returns:
		-5��δ��ʼ���ڵ�
		1��success 
*/
c8 put_in_data_node(Tree_node *node,void *ele){
	if (node->ifinitial != 1)
		return ARR_UN_INIT;
	
	node->ele_addr = ele;
	return ARR_OK;
}

/**
	Description: 
		edit branch of the node points to at ind
	Arguments:
		u32_ds ind���ڵ�������±�
		Tree_node *node_ele���½ڵ�ĵ�ַ 
	Returns:
		-5��δ��ʼ��
		-1���±겻�Ϸ�
		1��success and count++
		11 success but no count++
*/
c8 add_node(Tree_node *node,u32_ds ind,Tree_node *node_ele){
	if (node->ifinitial != 1)
		return ARR_UN_INIT;
	if (ind > node->branch_num - 1)
		return ARR_WRONG_INDEX;

	Tree_node* temp = (node->branches)[ind];
	(node->branches)[ind] = node_ele;
	if (temp == NULL_node)
		return ARR_OK;

	return 11;
}

/**
	Description: 
		��a�ڵ��ind������b�ڵ㣬���Ľڵ�������� 
	Arguments:
		u32_ds ind���ڵ�������±�
		Tree_node *node_ele���½ڵ�ĵ�ַ 
	Returns:
		-5��δ��ʼ��
		-1���±겻�Ϸ�
		1��success 
*/
c8 add_node_tree(Tree *tree,Tree_node *node,u32_ds ind,Tree_node *node_ele){
	c8 sta;
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;

	sta = add_node(node,ind,node_ele);
	if (sta == ARR_OK)	tree->count++;
	else if (sta == 11)	{}
	else return sta;
	
	return ARR_OK;
}

void* delete_node_tree(Tree *tree,Tree_node *node,u32_ds ind){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;

	if ((node->branches)[ind] == NULL_node)
		return (void*)ARR_OK;

	Tree_node_pointer node_t = (node->branches)[ind];
	if (node_t->ifinitial != 1)
		return ARR_UN_INIT;

	(node->branches)[ind] = NULL_node;
	void* ele = node_t->ele_addr;
	tree->count--;
	free_node(node_t);

	return ele;
}

/**
	Description: 
		���Ľڵ���� 
	Arguments:
		nothing 
	Returns:
		-5��δ��ʼ��
		X������ 
*/
u32_ds count_tree(Tree *tree){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;
	return tree->count;
}

/**
	Description: 
		��ȡ�ڵ�ĵ�ind��ڵ� 
	Arguments:
		u32_ds ind����ind��ڵ�������±� 
	Returns:
		-5��δ��ʼ��
		x��Ŀ�ꡤ�ڵ� 
*/
Tree_node* get_branch_node(Tree_node *node,u32_ds ind){
	if (node->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;
		
	return (node->branches)[ind];
}

/**
	Description: 
		����ͷ�ڵ� 
	Returns:
		-5��δ��ʼ�� 
*/
c8 set_head_tree(Tree *tree,Tree_node *head){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;
	tree->head = head;
    return ARR_OK;
}



/**
	Description: 
		�ͷŽڵ� 
*/
void free_node(Tree_node *node){
	if (node->ifinitial == 1)
		SD_FREE(node->branches);
	SD_FREE(node);
}

static c8 DFSnode(Tree_node *node){
	u32_ds i,num;
	if (node == NULL_node || node->ifinitial != 1)
		return ARR_UN_INIT;

	num = node->branch_num;
	//��ǽڵ㱻���ʹ��� 
	node->ifinitial = 2;
	for(i=0;i<num;i++){
		//����ÿ����֧
		DFSnode((node->branches)[i]); 
	}
	//���ϴ˽ڵ�
	SD_FREE(node->branches);
	SD_FREE(node);
    
    return ARR_OK;
}

/**
	Description: 
		ʹ��������ȱ������ݹ麯���ķ�ʽ�ͷ�ÿ���ڵ� 
	Returns:

*/
c8 free_tree(Tree *tree){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;
		
	DFSnode(tree->head);//������ȱ��� 
	tree->ifinitial = 0;
	SD_FREE(tree);
    
    return ARR_OK;
}

void print_node_main(Tree_node *node){
	u32_ds i;
	SD_PRINT("=>node=>ifinitial:	%d",node->ifinitial);
	SD_PRINT("=>node=>branch_num:	%d",node->branch_num);
	for(i=0;i<node->branch_num;i++){
		SD_PRINT("=>node=>branch[%d]:	%#x",i,(node->branches)[i]);
	}
}

void print_treeNode(Tree_node *node){
	SD_PRINT_HEAD("Tree_node","node");
	print_node_main(node);
	SD_PRINT_END;
}

void print_tree_main(Tree *tree){
	SD_PRINT("=>Tree=>ifinitial:	%d",tree->ifinitial);
	SD_PRINT("=>Tree=>count:	%d",tree->count);
}

void print_tree(Tree *tree){
	SD_PRINT_HEAD("Tree",tree->name);
	print_tree_main(tree);
	SD_PRINT_END;
}
