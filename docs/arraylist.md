<h3 align="center">Auto Increment ArrayList</h3>

---

<p align="left">ArrayList is based on C array, and is a sequential storage structure.</p>

It contains four properties. But you should only care about the first two, the other two are maintained by the program.
```clike
	char *name;
	void* (*arr);
	int length;
	int capacity;
```

# create or initialize
```clike
	ArrayList *int_arr;
    CreateArrayList(&int_arr,1);
    int_arr->name = "int_arr"; //rename it

    // or

    ArrayList int_arr;
    InitArrayList(&int_arr,1);
    int_arr.name = "int_arr"; //rename it
```

# functions

#### void* GET_arr(struct arraylist*,int ind)

Get an element from `arraylist` at index `ind`, like:
```clike
	int *buff;
    buff = (int*)(int_arr->GET_arr(int_arr,-1));
```

#### c8 ADD_one(struct arraylist*,void* ele_addr);

Add the pointer `ele_addr` of an element at the tail of the `arraylist`. Like
```clike
int_arr->ADD_one(int_arr,INT_new(1));
```

Success if it returns `ARR_OK`.

#### c8 ADD_lots(struct arraylist*,struct arraylist* arrlit_tail);

Add the pointer `arrlit_tail` of an arraylist at the tail of the `arraylist`.

Success if it returns `ARR_OK`.

#### c8 EDIT_arr(struct arraylist*,int index,void* ele_addr);

Change the element you saved in the `arraylist` at the index of `index` by new element address `ele_addr`.

Success if it returns `ARR_OK`.

#### c8 INSERT_one(struct arraylist*,int index,void* ele_addr);

*Kinda similar with the ADD_one(...), my bad...*

Insert the pointer `ele_addr` of an element at the index of `index` into the `arraylist`.

Success if it returns `ARR_OK`.

#### c8 INSERT_lots(struct arraylist*,int index,ArrayList* arrsub);

*Kinda similar with the ADD_lots(...), my bad...*

Insert the pointer `arrsub` of an arraylist at the index of `index` into the `arraylist`.

Success if it returns `ARR_OK`.

#### c8 COPY_arr(struct arraylist*,struct arraylist** new_arr);

Make a duplicate of the `arraylist` given an address `new_arr` of the pointer of the new arraylist. Like
```clike
	ArrayList* copyarr;
	int_arr->COPY_arr(int_arr, &copyarr);
	copyarr->PRINT(copyarr);
```

Success if it returns `ARR_OK`.

#### int COUNT(struct arraylist*);

Get the element number of `arraylist`.

#### c8 REVERSE_arr(struct arraylist*);

In-place reverse the `arraylist`.

Success if it returns `ARR_OK`.

#### c8 REVERSE_arr_copy(struct arraylist*,struct arraylist** arrcopy);

Reverse the `arraylist` and make a copy to the `arrcopy`.
```clike
	ArrayList* copyarr;
	int_arr->REVERSE_arr_copy(int_arr, &copyarr);
	copyarr->PRINT(copyarr);
```
Success if it returns `ARR_OK`.

#### void FREE(struct arraylist*);

Free the memory of the `arraylist` if it was created instead of initialized.

#### c8 SLICE_arr_copy(struct arraylist*,struct arraylist** arrnew,int start,int count);

Obtain a specific duplicated part, from index of `start` with `count` number of elements,  of the `arraylist` to the `arrnew`.

Success if it returns `ARR_OK`.

#### c8 DEL_arr(struct arraylist*,int start,int count);

In-place delete a specific part, from index of `start` with `count` number of elements,  of the `arraylist`.

Success if it returns `ARR_OK`.

#### void PRINT(struct arraylist*);

Print the status of the `arraylist`. Outputs are like
```clike
======ArrayList:int_arr======
=>arraylist=>ifinitial: 1
=>arraylist=>length:    2
=>arraylist=>capacity:  10
=======================
```

#### void CLEAR_arr(struct arraylist*);

Clear the elements in the `arraylist` but not wipe them out in the memory. It simply set the length of the `arraylist` to `0`.

