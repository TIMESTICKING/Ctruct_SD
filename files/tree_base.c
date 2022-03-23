#include <stdio.h>
#include "tree_base.h"
#include <stdlib.h>

/**
	Description: 
		静态初始化树 ，同时也静态初始化了头节点 
	Arguments:
		u32_ds head_node_branch_num：头节点的分叉数 
	Returns:
		1: success
*/
c8 InitTree(Tree *tree){
	tree->head = NULL_node;
	tree->count = 0;
	tree->ifinitial = 1;
	tree->name = "tree_def";
	tree->EDIT_Data_node = put_in_data_node;
	tree->ADD_node = add_node_tree;
	tree->COUNT_tree = count_tree;
	tree->GET_BRANCH_node = get_branch_node;
	tree->PRINT_tree = print_tree;
	tree->FREE_tree = free_tree;
	tree->SET_head = set_head_tree;
	
	return ARR_OK;
}

/**
	Description: 
		动态创建树 ，同时也静态初始化了头节点 
	Arguments:
		u32_ds head_node_branch_num：头节点的分叉数
	Returns:
		1: success
		3: 内存申请失败 
*/
c8 CreateTree(Tree **tree){
	*tree = (Tree*)SD_MALLOC(sizeof(Tree)); 
	if (*tree == (Tree*)0)
		return ARR_MALLOC_FAIL;
		
	return InitTree(*tree);
}

/**
	Description: 
		静态初始化节点 
	Arguments:
		u32_ds branch_num： 节点分支数量 
	Returns:
		1：success
		3：内存申请失败 
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
	node->ADD_node = add_node;
	node->FREE_node= free_node;
	node->PRINT_node = print_treeNode;
	node->ele_addr = NULL_void;
	node->branch_num = branch_num;
	node->ifinitial = 1;
	
	return ARR_OK;
}

/**
	Description: 
		动态创建节点 
	Arguments:
		u32_ds branch_num：节点分支数量 
	Returns:
		1：success
		3：内存申请失败 
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
		往节点放入数据的指针 
	Arguments:
		void *ele：数据地址 
	Returns:
		-5：未初始化节点
		1：success 
*/
c8 put_in_data_node(Tree_node *node,void *ele){
	if (node->ifinitial != 1)
		return ARR_UN_INIT;
	
	node->ele_addr = ele;
	return ARR_OK;
}

/**
	Description: 
		在a节点的ind处插入b节点 
	Arguments:
		u32_ds ind：节点数组的下标
		Tree_node *node_ele：新节点的地址 
	Returns:
		-5：未初始化
		-1：下标不合法
		1：success 
*/
c8 add_node(Tree_node *node,u32_ds ind,Tree_node *node_ele){
	if (node->ifinitial != 1)
		return ARR_UN_INIT;
	if (ind > node->branch_num - 1)
		return ARR_WRONG_INDEX;

	(node->branches)[ind] = node_ele;
	
	return ARR_OK;
}

/**
	Description: 
		在a节点的ind处插入b节点，树的节点个数自增 
	Arguments:
		u32_ds ind：节点数组的下标
		Tree_node *node_ele：新节点的地址 
	Returns:
		-5：未初始化
		-1：下标不合法
		1：success 
*/
c8 add_node_tree(Tree *tree,Tree_node *node,u32_ds ind,Tree_node *node_ele){
	c8 sta;
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;

	sta = add_node(node,ind,node_ele);
	if (sta != ARR_OK)	return sta;
	tree->count++;
	
	return ARR_OK;
}

/**
	Description: 
		树的节点个数 
	Arguments:
		nothing 
	Returns:
		-5：未初始化
		X：个数 
*/
u32_ds count_tree(Tree *tree){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;
	return tree->count;
}

/**
	Description: 
		获取节点的第ind叉节点 
	Arguments:
		u32_ds ind：第ind叉节点的数组下标 
	Returns:
		-5：未初始化
		x：目标·节点 
*/
Tree_node* get_branch_node(Tree_node *node,u32_ds ind){
	if (node->ifinitial != 1)
		return (Tree_node*)ARR_UN_INIT;
		
	return (node->branches)[ind];
}

/**
	Description: 
		设置头节点 
	Returns:
		-5：未初始化 
*/
c8 set_head_tree(Tree *tree,Tree_node *head){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;
	tree->head = head;
    return ARR_OK;
}



/**
	Description: 
		释放节点 
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
	//标记节点被访问过了 
	node->ifinitial = 2;
	for(i=0;i<num;i++){
		//遍历每个分支
		DFSnode((node->branches)[i]); 
	}
	//报废此节点
	SD_FREE(node->branches);
	SD_FREE(node);
    
    return ARR_OK;
}

/**
	Description: 
		使用深度优先遍历，递归函数的方式释放每个节点 
	Returns:

*/
c8 free_tree(Tree *tree){
	if (tree->ifinitial != 1)
		return ARR_UN_INIT;
		
	DFSnode(tree->head);//深度优先遍历 
	tree->ifinitial = 0;
//	SD_FREE(tree);
    
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
