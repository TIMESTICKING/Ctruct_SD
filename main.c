#include <stdio.h>
#include "all_dataStructure.h"

void test_array(void){
	ArrayList *int_arr;
	int i;
	int *buff;
	
	CreateArrayList(&int_arr,1);
	
	int_arr->name = "int_arr";
	int_arr->ADD_one(int_arr,INT_new(1));
	int_arr->ADD_one(int_arr,INT_new(4));
	int_arr->ADD_one(int_arr,INT_new(13));
	
	int_arr->REVERSE_arr(int_arr);

	printf("int_arr now looks like-------\n");
	for (i=0;i<int_arr->length;i++){
		buff = (int*)(int_arr->GET_arr(int_arr,i));
		printf("get: %d\n",*buff);
	}
	
	int_arr->DEL_arr(int_arr,-1,1);
	printf("\ndelete last element of int_arr\n");
	
	printf("int_arr now looks like-------\n");
	for (i=0;i<int_arr->length;i++){
		buff = (int*)(int_arr->GET_arr(int_arr,i));
		printf("get: %d\n",*buff);
	}
	
	int_arr->PRINT(int_arr); // output the infomation of this array

	ArrayList* copyarr;
	int_arr->COPY_arr(int_arr, &copyarr);
	copyarr->PRINT(copyarr);
	
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
	
	sa.INSERT_sta(&sa,INT_new(5));
	sa.INSERT_sta(&sa,&b);
	sa.INSERT_sta(&sa,&c);
	n = sa.COUNT(&sa);

	sa.PRINT(&sa);
	
	for(i = 0;i<n;i++){
		buff = sa.POP_sta(&sa);
		if (buff != NULL_void){
			buff = (int*)buff;
			printf("ele is %d\n",*buff);
			printf("stack number %d\n",sa.COUNT(&sa));
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
	
	cq.PRINT(&cq);
	cq2->PRINT(cq2);
	
	cq.ENQUEUE_cq(&cq,INT_new(3));
	cq.ENQUEUE_cq(&cq,&b);
	cq.ENQUEUE_cq(&cq,&a);
	cq.ENQUEUE_cq(&cq,&b);
	
	for(i=0;i<9;i++){
		buff = cq.DEQUEUE_cq(&cq);
		if (buff != NULL_void){
			printf("buff %d\n",*buff);
			cq.PRINT(&cq);
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
			cq2->PRINT(cq2);
		}else break;
	}
    
    cq2->FREE(cq2);
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
	
	tree.EDIT_branch(&tree,a,0,c);
	tree.EDIT_branch(&tree,a,0,c);
	tree.EDIT_branch(&tree,a,1,d);
	tree.EDIT_branch(&tree,a,2,f);
	tree.EDIT_branch(&tree,c,0,a);
	tree.EDIT_branch(&tree,c,1,d);
	tree.EDIT_branch(&tree,c,2,b);
	tree.EDIT_branch(&tree,b,0,c);
	tree.EDIT_branch(&tree,b,1,e);
	tree.EDIT_branch(&tree,e,0,b);
	tree.EDIT_branch(&tree,d,0,a);
	tree.EDIT_branch(&tree,d,1,c);
	tree.EDIT_branch(&tree,f,0,a);
	tree.EDIT_branch(&tree,f,1,g);
	tree.EDIT_branch(&tree,g,0,f);
	tree.PRINT(&tree);

	tree.DELETE_branch(&tree,c,2);
	tree.PRINT(&tree);

	tree.EDIT_branch(&tree,c,2,b);
	tree.PRINT(&tree);
	
	tree.head = a;
	
	tree.FREE(&tree);
}

void test_linkedList(void){
	LinkedList_SD llist,ant,*copyer;
	Tree_node *n;
	int a = 0;
	int b = 1;
	int c = 2;
	int *buff;
	c8 sta;
	
	InitLinkedList_SD(&llist);
	llist.name="list1";
	InitLinkedList_SD(&ant);
	ant.name="ant";
	
	llist.INSERT_ele_atTail(&llist,&a);
	llist.INSERT_ele_atTail(&llist,&b);
	llist.PRINT(&llist);
	
	
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

void testCircleList(void){
	CircleList *clist;
	int *buff;
	Tree_node *n;
	
	// init it, and put into something
	CreateCircleList(&clist);
	clist->INSERT_ele_atTail(clist, "string alpha");
	clist->INSERT_ele_atTail(clist, "string beta");
	clist->PRINT(clist);
	
	// delete the last element
	clist->DEL_byInd_clist(clist,-1);
	clist->PRINT(clist);
	
	// add something at head
	clist->INSERT_ele_atHead(clist, "I'm the newer");
	clist->PRINT(clist);
	
	int t; // bc it's circleList, it'll print forever, use t to handle the output times.
	for(n=get_head_clist(clist), t=0;n!=NULL_node && t<10;
			n=n->GET_BRANCH_node(n,NEXT_LLIST), t++){
		buff = (char*)(n->ele_addr);
		printf("data is: %s\n",buff);
	}
    
    clist->FREE(clist);
}

void test_iterators(void){
	ArrayList arr;
	InitArrayList(&arr, 5);
	
	arr.name = "arr1";
	arr.ADD_one(&arr,INT_new(1));
	arr.ADD_one(&arr,INT_new(5));
	arr.ADD_one(&arr,INT_new(6));
	arr.ADD_one(&arr,INT_new(8));
	arr.ADD_one(&arr,INT_new(12));
	arr.ADD_one(&arr,INT_new(124));
	
	// 正序输出数组 
	SD_PRINT("===正序输出数组");
	ITER_4ARRAY iter_posi;
	InitITER_4array(&iter_posi, &arr, ITERTYPE_POSI_SEQ_4ARRAY);
	FOR_ITER(iter_posi){
		printf("%d ", GI(iter_posi, int*));
	}
	LN	LN
	
	// 逆序输出数组 
	ITER_4ARRAY iter_rev;
	SD_PRINT("===逆序输出数组");
	InitITER_4array(&iter_rev, &arr, ITERTYPE_REVERSE_4ARRAY);
	FOR_ITER(iter_rev){
		printf("%d ", GI(iter_rev, int*));
	}
	LN	LN
		
	// 二分查找数组 
	ITER_4ARRAY iter;
	SD_PRINT("===二分查找数组");
	InitITER_4array(&iter, &arr, ITERTYPE_2DIVSION_4ARRAY);
	ITERDIREC_para_init(dir);
	int aim = 124;
	FOR_ITER(iter, dir){
		int* buff = iter.next(&iter, dir);
		ITERDIREC_para_judge(dir, *buff, aim);
	}
	if (ITERDIREC_para_ifFind(dir))
		printf("find %d at index %d\n", aim, iter.pos);	
}


void test_uthash(void){
    typedef struct {
        char* id;
        int field;
        UT_hash_handle hh;
    }HashStruct;
    
    HashStruct* global=NULL;
    
    HashStruct mynumber;
    mynumber.id = "first";
    mynumber.field = 6;
    
    HashStruct mynumber2;
    mynumber2.id = "first";
    mynumber2.field = 8;
    
    HASH_ADD_STR(global, id, &mynumber);
    HASH_ADD_STR(global, id, &mynumber2);
    HashStruct *res;
    HASH_FIND_STR(global, "first", res);
    printf("find number: %d\n", res->field);
}


void test_dict(void){
    Dictionary mydict;
    
    InitDictionary(&mydict);
    mydict.name = "dict1";
    mydict.ADD_EDIT_dict(&mydict,"number",INT_new(3)); //keys and values
    mydict.ADD_EDIT_dict(&mydict,"string","hello my baby~");
	mydict.ADD_EDIT_dict(&mydict,"number",INT_new(155));
    
    int* res;
    res = (int*)mydict.GET_dict(&mydict, "number");
    SD_PRINT("res is: %d", *res);

	// you'd better check the existence of the key if u'r not sure
	void* res3 = mydict.GET_dict(&mydict, "string");
	if (res3)
		SD_PRINT("res is: %s", (char*)res3);
}


int main(int argc, char *argv[])
{
//	test_stack();
	// test_array();
//	test_cirqueue();
//	
//	test_linkedList();
	test_tree();
	// testCircleList();
	// test_iterators();
//    test_uthash();
//    test_dict();
	return 0;
}


