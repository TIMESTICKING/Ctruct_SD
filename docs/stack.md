<h3 align="center">Stack</h3>

---

<p align="left">Stack is based on ArrayList, and is a sequential storage structure.</p>

It contains two properties. The structure of the first one should refer to [ArrayList](arraylist.md).
```clike
	ArrayList* sta_arr;
	char *name;
```

# create or initialize
```clike
    Stacks sa;
    InitStacks(&sa);
	sa.name = "sa";//rename it

    // or

    Stacks* sa;
    CreateStacks(&sa);
	sa->name = "sa";//rename it
```

# functions

#### c8 INSERT_sta(struct stacks*,void* ele)

Push an element into the stack. Like
```clike
    sa.INSERT_sta(&sa,INT_new(5));
```
Success if it returns `ARR_OK`.

#### int COUNT(struct stacks*)

Get the number of the elements in the stack.

#### void* POP_sta(struct stacks*)

Pop out the element and return its address. Like
```clike
int *buff;
buff = sa.POP_sta(&sa);
```

#### void FREE(struct stacks*)

Free the memory of the stack if it was created instead of initialized.

#### void PRINT(struct stacks*)

Print the status of the stack.
