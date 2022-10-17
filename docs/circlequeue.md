<h3 align="center">Circular Queue</h3>

---

<p align="left">Circular Queue (FIFO) is based on ArrayList, and is a sequential storage structure.</p>

It contains five properties. The structure of the second one should refer to [ArrayList](arraylist.md).
```clike
	char *name;
	ArrayList* cq_arr;
	int front;
	int rear;
	int size;
```

# create or initialize
```clike
    CirQueues cq;
    InitCirQueue(&cq,3); //give a size of 3
    cq.name = "cq1";//rename it

    // or

    CirQueues* cq;
    InitCirQueue(&cq,3); //give a size of 3
    cq->name = "cq1";//rename it
```

# functions

#### c8 ENQUEUE_cq(struct cirqueues*,void* ele)

Push an element `ele` into the queue given the pointer of the element. Like
```clike
cq.ENQUEUE_cq(&cq,INT_new(3));
```
Success if it returns `ARR_OK`. Also you need to be aware of if it's aleady full, it returns `ARR_FALSE` if it is.

#### void* DEQUEUE_cq(struct cirqueues*)

Pop an element out by returning its pointer of the queue. Also you need to be aware of if it's already empty, it returns `NULL_void` if it is. Like
```clike
void* buff = cq.DEQUEUE_cq(&cq);
if (buff != NULL_void)
    printf("buff %d\n",(int*)buff);
```
#### int COUNT(struct cirqueues*)

Get the number of elements that are already in the queue. It will not be bigger than the size of the queue.

#### void FREE(struct cirqueues*)

Free the memory of the queue if it was created instead of initialized.

#### void PRINT(struct cirqueues*)

Print the status of the queue.
