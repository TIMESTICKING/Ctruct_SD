#include <stdio.h>
#include "all_dataStructure.h"

void test_array(void){
	ArrayList *arr1;
	ArrayList *arr2;
	int a = 1;
	int b = 2;
	int c = 4;
	int d = 7;
	int i;
	int *buff;
	
	CreateArrayList(&arr1,1);
	CreateArrayList(&arr2,1);
	
	arr1->name = "arr1";
	arr1->ADD_one(arr1,&a);
	arr1->ADD_one(arr1,&c);	
	arr1->ADD_one(arr1,&d);
	
	arr1->REVERSE_arr(arr1);

	printf("arr1,print-------\n");
	for (i=0;i<arr1->length;i++){
		buff = (int*)(arr1->GET_arr(arr1,i));
		printf("get: %d\n",*buff);
	}
	
	arr1->DEL_arr(arr1,-1,1);
	printf("\ndel arr1 last ele\n");
	
	printf("arr1,print-------\n");
	for (i=0;i<arr1->length;i++){
		buff = (int*)(arr1->GET_arr(arr1,i));
		printf("get: %d\n",*buff);
	}
	
	arr1->PRINT_arr(arr1);
	
}

void test_stack(void){
	Stacks sa;
	Stacks *r;
	int a = 5;
	int b = 23;
	int c = 34;
	int *buff;
	int i;
	int n;
	
	InitStacks(&sa);
	sa.name = "sa";
	
	sa.INSERT_sta(&sa,&a);
	sa.INSERT_sta(&sa,&b);
	sa.INSERT_sta(&sa,&c);
	n = sa.COUNT_sta(&sa);

	sa.PRINT_sta(&sa);	
	
	for(i = 0;i<n;i++){
		buff = sa.POP_sta(&sa);
		if (buff != NULL_void){
			buff = (int*)buff;
			printf("ele is %d\n",*buff);
			printf("stack number %d\n",sa.COUNT_sta(&sa));
		}
	}
}

void test_cirqueue(){
	CirQueues cq;
	CirQueues *cq2;
	int a = 4;
	int b = 7;
	int *buff;
	int i;
	
	InitCirQueue(&cq,3);
	CreateCirQueue(&cq2,3);
	cq2->name = "cq2";
	cq.name = "cq1";
	
	cq.PRINT_cq(&cq);
	cq2->PRINT_cq(cq2);
	
	cq.ENQUEUE_cq(&cq,&a);
	cq.ENQUEUE_cq(&cq,&b);
	cq.ENQUEUE_cq(&cq,&a);
	cq.ENQUEUE_cq(&cq,&b);
	
	for(i=0;i<9;i++){
		buff = cq.DEQUEUE_cq(&cq);
		if (buff != NULL_void){
			printf("buff %d\n",*buff);
			cq.PRINT_cq(&cq);	
		}else break;
	}
	
	cq2->ENQUEUE_cq(cq2,&b);
	cq2->ENQUEUE_cq(cq2,&a);
	cq2->ENQUEUE_cq(cq2,&b);
	cq2->ENQUEUE_cq(cq2,&a);

	for(i=0;i<9;i++){
		buff = cq2->DEQUEUE_cq(cq2);
		if (buff != NULL_void){
			printf("buff %d\n",*buff);
			cq2->PRINT_cq(cq2);	
		}else break;
	}
}

void test_tree(void){
	Tree tree;
	Tree_node *a,*b,*c,*d,*e,*f,*g;
	
	InitTree(&tree);
	CreateNode(&a,3);
	a->EDIT_Data_node(a,INT_new(1));
	CreateNode(&b,2);
	a->EDIT_Data_node(b,INT_new(3));
	CreateNode(&c,3);
	a->EDIT_Data_node(c,INT_new(2));
	CreateNode(&d,2);
	a->EDIT_Data_node(d,INT_new(5));
	CreateNode(&e,1);
	a->EDIT_Data_node(e,INT_new(4));
	CreateNode(&f,2);
	a->EDIT_Data_node(f,INT_new(6));
	CreateNode(&g,1);
	a->EDIT_Data_node(g,INT_new(7));
	
	add_node_tree(&tree,a,0,c);
	add_node_tree(&tree,a,1,d);
	add_node_tree(&tree,a,2,f);
	add_node_tree(&tree,c,0,a);
	add_node_tree(&tree,c,1,d);
	add_node_tree(&tree,c,2,b);
	add_node_tree(&tree,b,0,c);
	add_node_tree(&tree,b,1,e);
	add_node_tree(&tree,e,0,b);
	add_node_tree(&tree,d,0,a);
	add_node_tree(&tree,d,1,c);
	add_node_tree(&tree,f,0,a);
	add_node_tree(&tree,f,1,g);
	add_node_tree(&tree,g,0,f);
	
	tree.head = a;
	
	tree.FREE_tree(&tree);
}

void test_linkedList(void){
	LinkedList llist,ant,*copyer;
	Tree_node *n;
	int a = 0;
	int b = 1;
	int c = 2;
	int *buff;
	c8 sta;
	
	InitLinkedList(&llist);
	llist.name="list1";
	InitLinkedList(&ant);
	ant.name="ant";
	
	llist.INSERT_ele_atTail(&llist,&a);
	llist.INSERT_ele_atTail(&llist,&b);
	llist.PRINT_llist(&llist);
	
	
	for(n = llist.GET_head_llist(&llist);n!=NULL_node;n = n->GET_BRANCH_node(n,NEXT_LLIST)){
		buff = (int*)n->ele_addr;
		printf("llist data is %d\n",*buff);
	}
	
	llist.DEL_byInd_llist(&llist,0);
	llist.DEL_byInd_llist(&llist,0);
	llist.DEL_byInd_llist(&llist,0);
	printf("del\n");
	
	for(n = llist.GET_head_llist(&llist);n!=NULL_node;n = n->GET_BRANCH_node(n,NEXT_LLIST)){
		buff = (int*)n->ele_addr;
		printf("llist data is %d\n",*buff);
	}
}

void testCircleLinkedList(void){
	CircleList *clist;
	int a = 3;
	int b = 2;
	int *buff;
	Tree_node *n;
	int c;
	c8 sta;
	
	CreateCircleList(&clist);
	clist->INSERT_ele_atTail(clist,&a);
	clist->INSERT_ele_atTail(clist,&b);
	clist->PRINT_clist(clist);
	
	
	clist->DEL_byInd_clist(clist,-1);
	clist->PRINT_clist(clist);
	
	if (clist->IF_ELEaddr_exsit_clist(clist,&a) != ARR_OK)
		clist->INSERT_ele_atTail(clist,&a);
	clist->PRINT_clist(clist);
	
	
	for(n=get_head_clist(clist),c=0;n!=NULL_node && c<10;n=n->GET_BRANCH_node(n,NEXT_LLIST),c++){
		buff = (int*)(n->ele_addr);
		printf("data is %d\n",*buff);
	}
}

void test_iterators(void){
	ArrayList arr;
	InitArrayList(&arr, 5);
	
	arr.name = "arr1";
	arr.ADD_one(&arr,INT_new(1));
	arr.ADD_one(&arr,INT_new(2));	
	arr.ADD_one(&arr,INT_new(3));
	arr.ADD_one(&arr,INT_new(4));
	arr.ADD_one(&arr,INT_new(5));
	
	ITER_4ARRAY iter;
	InitITER_4array(&iter, &arr, ITERTYPE_REVERSE_4ARRAY);
	
	FOR_ITER(iter){
		int* buff = iter.next(&iter);
		printf("%d\n", *buff);
	}
}


int main(int argc, char *argv[])
{
//	test_stack();
//	test_array();
//	test_cirqueue();	
//	
//	test_linkedList();
	//test_tree();
//	testCircleLinkedList();
	test_iterators();
	return 0;
}


