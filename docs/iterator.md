<h3 align="center">Iterator</h3>

---

Iterator now only supports for [ArrayList](arraylist.md).
```clike
	LinkedList_SD* linkList;
	char *name;
```

# Iteration types
```clike
	ITERTYPE_REVERSE_4ARRAY=1,
	ITERTYPE_POSI_SEQ_4ARRAY,
	ITERTYPE_2DIVSION_4ARRAY
```

# Iteration directions
```clike
	ITERDIREC_LEFT=-1,
	ITERDIREC_INIT,
	ITERDIREC_RIGHT
```

# usage
```clike
ArrayList arr;
InitArrayList(&arr, 5);

arr.name = "arr1";
arr.ADD_one(&arr,INT_new(1));
arr.ADD_one(&arr,INT_new(5));
arr.ADD_one(&arr,INT_new(6));
arr.ADD_one(&arr,INT_new(8));
arr.ADD_one(&arr,INT_new(12));
arr.ADD_one(&arr,INT_new(124));

// output the array in positive sequence
SD_PRINT("===output the array in positive sequence");
ITER_4ARRAY iter_posi;
InitITER_4array(&iter_posi, &arr, ITERTYPE_POSI_SEQ_4ARRAY);
FOR_ITER(iter_posi){
    printf("%d ", GI(iter_posi, int*));
}
LN	LN

// output the array in negative sequence
ITER_4ARRAY iter_rev;
SD_PRINT("===output the array in negative sequence");
InitITER_4array(&iter_rev, &arr, ITERTYPE_REVERSE_4ARRAY);
FOR_ITER(iter_rev){
    printf("%d ", GI(iter_rev, int*));
}
LN	LN
    
// Binary search array
ITER_4ARRAY iter;
SD_PRINT("===Binary search array");
InitITER_4array(&iter, &arr, ITERTYPE_2DIVSION_4ARRAY);
ITERDIREC_para_init(dir);
int aim = 124;
FOR_ITER(iter, dir){
    int* buff = iter.next(&iter, dir);
    ITERDIREC_para_judge(dir, *buff, aim);
}
if (ITERDIREC_para_ifFind(dir))
    printf("find %d at index %d\n", aim, iter.pos);	
```
outputs are like
```clike
===output the array in positive sequence
1 5 6 8 12 124

===output the array in negative sequence
124 12 8 6 5 1 

===Binary search array
find 124 at index 5
```