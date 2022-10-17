<h3 align="center">Circular List</h3>

---

Circular List is based on the [LinkedList](linkedlist.md), and is a chain storage structure.

It contains two properties, and the first one is maintained by the program. Negative numbers of index are supported.
```clike
	LinkedList_SD* linkList;
	char *name;
```

# create or initialize
```clike
	CircleList *clist;
	CreateCircleList(&clist);
	clist->name="clist";//rename it

    // or

	CircleList clist;
	InitCircleList(&clist);
	clist.name="clist";//rename it
```

# functions

#### c8 INSERT_ele_atTail(struct cList*,void*ele)
#### c8 INSERT_ele_atHead(struct cList*,void*ele)
#### Tree_node* GET_tail_llist(struct cList*)
#### Tree_node* GET_head_llist(struct cList*)
#### c8 DEL_byAddr_clist(struct cList*,Tree_node*addr)
#### c8 DEL_byInd_clist(struct cList*,int ind)
#### u32_ds COUNT(struct cList*)
#### c8 IF_ELEaddr_exsit_clist(struct cList*,void* ele)
#### void PRINT(struct cList*)
#### void FREE(struct cList*)

All those are similar to the `LinkedList` functions, check it out [here](linkedlist.md).
