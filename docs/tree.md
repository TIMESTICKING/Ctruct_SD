<h3 align="center">Arbitrary Branches Tree</h3>

---

<p align="left">Arbitrary Branches Tree is based on C array.</p>

It contains two C structs, `struct trees` and `struct tree_n`. The former one maintains the whole tree structure and the latter one represents the nodes of the tree.

`struct tree_n` has three properties (below). The first one is a C array, it works with the third one `branch_num`, and together they represents the number of the branches of this node has and the next node address of each branch links to. The second one `ele_addr` records the element of this node restores.
```clike
	Tree_node_pointer *branches;
	void*	ele_addr; 
    u32_ds	branch_num;
```

---

`struct tree_n` has three properties (below). And you should only care about the second one, the others are maintained by the program.
```clike
	Tree_node *head;
	char	*name;
	u32_ds	count;
```

# create or initialize

### for tree structure
```clike
    Tree tree;
    InitTree(&tree);
    tree.name = "tree1";//rename it

    // or

    Tree* tree;
    CreateTree(&tree);
    tree->name = "tree1";//rename it
```

### for tree-node structure
```clike
	Tree_node *a;
    CreateNode(&a,3); //this node has 3 branches

    //or 

    Tree_node a;
    InitNode(&a,3); //this node has 3 branches
```

### combine them above
a quick look of how to combine the nodes together to complete the tree.
```clike
	Tree tree;
	Tree_node *a,*b,*c,*d,*e,*f,*g;
	
	InitTree(&tree);
	
	CreateNode(&a,3);
	a->EDIT_Data_node(a,INT_new(1)); // store an element into a node
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
	
	tree.EDIT_branch(&tree,a,0,c); //the first branch of 'a' node is pointing to the node 'c', and 'a' has 3 branches
	tree.EDIT_branch(&tree,a,0,c);
	tree.EDIT_branch(&tree,a,1,d);
	tree.EDIT_branch(&tree,a,2,f);
	tree.EDIT_branch(&tree,c,0,a);
	tree.EDIT_branch(&tree,c,1,d);
	tree.EDIT_branch(&tree,c,2,b);
	tree.EDIT_branch(&tree,b,0,c);
	tree.EDIT_branch(&tree,b,1,e);
	tree.EDIT_branch(&tree,e,0,b); //the first branch of 'e' node is pointing to the node 'b', and 'e' only has 1 branch
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

	tree.head = a;  //complete the tree, the root of the tree is now 'a' node.
	
	tree.FREE(&tree);
```
output is like
```clike
======Tree:tree_def======
=>Tree=>ifinitial:      1
=>Tree=>count:  14
=======================
======Tree:tree_def======
=>Tree=>ifinitial:      1
=>Tree=>count:  13
=======================
======Tree:tree_def======
=>Tree=>ifinitial:      1
=>Tree=>count:  14
=======================
```


# functions

#### c8 EDIT_Data_node(struct tree_n*,void* ele)

- can be called from both type of `struct trees` and `struct tree_n`

Given a tree node, modify the pointer of the element of it.

Success if it returns `ARR_OK`.

#### Tree_node_pointer GET_BRANCH_node(struct tree_n*,u32_ds ind)

- can be called from both type of `struct trees` and `struct tree_n`

Get a tree node which `ind`th branch linked to.
```clike
// because node 'a' has 3 branches (shown in above), now obtain the node that the third branch points to.
Tree_node_pointer node = tree.GET_BRANCH_node(a, 2);
```

Return the address of the node.

#### c8 EDIT_branch(struct trees *tree,Tree_node_pointer node,u32_ds ind,Tree_node_pointer node_ele)

Give a node `node`, point or re-point the `ind`th branch to the new node `node_ele`.

Success if it returns `ARR_OK`.

#### void* DELETE_branch(struct trees *tree,Tree_node_pointer node,u32_ds ind)

Give a node `node`, delete the `ind`th branch of the node.

return the element address you set in the deleted node *not the pointer of the deleted node*.

#### void FREE_node(struct tree_n*)

Free the memory of the `tree_n`, be careful to take care of your own element. You need to free it by yourself.

#### void PRINT_node(struct tree_n*)

Print the status or the infomations of the node.

#### c8 SET_head(struct trees*,Tree_node*)

Set the root node of the tree, because `DFS` algorithm in `FREE(struct trees*)` relies on it.

#### u32_ds COUNT(struct trees*)

Get the node number in the tree.

#### void PRINT(struct trees*)

Print the status or the infomations of the tree.

#### c8 FREE(struct trees*)

Free the memory of the tree, be careful to take care of your own elements. You need to free them by yourself.
