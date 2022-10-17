<h3 align="center">LinkedList</h3>

---

LinkedList is based on two branches **Tree**, and is a chain storage structure.

It contains three properties. The structure of the first and third one should refer to [Arbitrary Tree](tree.md). Negative numbers of index are supported.
```clike
	Tree *tree;
	char *name;
	Tree_node *tail;
```
You should know that `LinkedList` here is just a `Tree` with every node contains only two branches. One points to the previous node and other one points to the next node.

# create or initialize
```clike
    LinkedList_SD llist;
    InitLinkedList_SD(&llist);
	llist.name="list1";//rename it

    // or

    LinkedList_SD* llist;
    CreateLinkedList_SD(&llist);
	llist->name="list1";//rename it
```

# choose branch

Unlike in `Tree` I use integers to choose the specific branch. Here I did macros like
```clike
#define PREV_LLIST  	0
#define NEXT_LLIST      1
```
to choose the previous node or the next node.

# functions

#### c8 INSERT_ele_byAddr(struct lList*,Tree_node* node,u8_ds position,void *ele)

If you have a node pointer, which is the address of the `node`, and it's already in the LinkedList, then you can insert an element pointer `ele` before the `node` or after it by using `position` argument, corresponding the values of `PREV_LLIST` and `NEXT_LLIST`.

Success if it returns `ARR_OK`.

#### c8 INSERT_ele_atInd(struct lList*,int ind,void *ele)

Insert an element pointer `ele` at the index `ind`. 

Success if it returns `ARR_OK`.

#### c8 INSERT_ele_atTail(struct lList*,void*ele)

Insert an element pointer `ele` at the tail. Like
```clike
llist.INSERT_ele_atTail(&llist,INT_new(45));
```

Success if it returns `ARR_OK`.

#### c8 INSERT_ele_atHead(struct lList*,void*ele)

Insert an element pointer `ele` at the head. 

Success if it returns `ARR_OK`.

#### c8 ADD_llist_atHead(struct lList*,struct lList* add_llist)

Add a new LinkedList `add_llist` at the head. 

Success if it returns `ARR_OK`.

#### c8 ADD_llist_atTail(struct lList*,struct lList* add_llist)

Add a new LinkedList `add_llist` at the tail. 

Success if it returns `ARR_OK`.

#### c8 ADD_llist_atInd(struct lList*,int ind,struct lList* add_llist)

Add a new LinkedList `add_llist` at the index of `ind`. 

Success if it returns `ARR_OK`.

#### c8 DEL_byAddr_llist(struct lList*,Tree_node* node_del)

Detach the node `node_del` in the linkedlist. You need to free the memory of the element in the node by yourself.

Success if it returns `ARR_OK`.

#### c8 DEL_byInd_llist(struct lList*,int ind)

Detach the node at the index of `ind` in the linkedlist. You need to free the memory of the element in the node by yourself before this step. Like
```clike
llist.DEL_byInd_llist(&llist,0);
```

Success if it returns `ARR_OK`.

#### Tree_node* GET_tail_llist(struct lList*)

Get the last node in the linkedlist.

Return the pointer of the desired node.

#### Tree_node* GET_head_llist(struct lList*)

Get the first node in the linkedlist. Run through the whole list would be like
```clike
for(n = llist.GET_head_llist(&llist);n!=NULL_node;n = n->GET_BRANCH_node(n,NEXT_LLIST)){
		buff = (int*)n->ele_addr;
		printf("llist data is %d\n",*buff);
}
```
The code `n->GET_BRANCH_node()` is the part of the [Arbitrary Tree](tree.md)

Return the pointer of the desired node.

#### Tree_node* GET_addr_byIndex(struct lList*,int ind)

Get address, which is the pointer of a node by its index.

Return the pointer of the desired node.

#### c8 COPY_llist(struct lList* llist,struct lList** new_llist)

Copy every node in the `llist` into the new LinkedList `new_llist`. Nodes are new created, but elements inside of thems are the original one.

Success if it returns `ARR_OK`.

#### c8 REVERSE_llist(struct lList*)

In-place reverse the list.

Success if it returns `ARR_OK`.

#### u32_ds COUNT(struct lList*)

Get the elements number in the list.

#### c8 IF_ELEaddr_exsit_llist(struct lList*,void* ele)

If the element pointer is already in the list. **Not the node pointer.**

True if it returns `ARR_OK`.

#### void FREE(struct lList*)

Free the memory of the linkedlist and every node in it. Elements are not included.

#### void PRINT(struct lList*)

Print the status or the infomation of the linkedlist.
