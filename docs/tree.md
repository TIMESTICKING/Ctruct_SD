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
	
	add_node_tree(&tree,a,0,c); //the first branch of 'a' node is pointing to the node 'c', and 'a' has 3 branches
	add_node_tree(&tree,a,1,d);
	add_node_tree(&tree,a,2,f);
	add_node_tree(&tree,c,0,a);
	add_node_tree(&tree,c,1,d);
	add_node_tree(&tree,c,2,b);
	add_node_tree(&tree,b,0,c);
	add_node_tree(&tree,b,1,e);
	add_node_tree(&tree,e,0,b); //the first branch of 'e' node is pointing to the node 'b', and 'e' only has 1 branch
	add_node_tree(&tree,d,0,a);
	add_node_tree(&tree,d,1,c);
	add_node_tree(&tree,f,0,a);
	add_node_tree(&tree,f,1,g);
	add_node_tree(&tree,g,0,f);
	
	tree.head = a;  //complete the tree, the head of the tree is now 'a' node.
	
	tree.FREE(&tree);
```

# functions