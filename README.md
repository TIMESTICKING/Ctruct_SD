
<h3 align="center">纯C语言的多种数据结构</h3>


---

<p align="left"> 这是一个由纯C编写的多种数据结构项目，项目起初是用于学习，后可拓展到嵌入式编程领域。我感觉还是用于学习比较好，因为它的适用场景并不多。
    <br> 
</p>

## 📝 Table of Contents

- [About](#about)
- [Topology](#topology)
- [Take a glance](#take_a_glance)
- [Getting Started](#getting_started)
- [APIs](#APIs)
- [Acknowledgments](#acknowledgement)

## 🧐 About <a name = "about"></a>

项目采用结构体来***模拟面向对象***的编程方式，但受语言限制，“方法”仍需传入“类”自身。同时下标采用了负数表示法，例如-1表示最后一个元素。<br>
项目包含的数据结构可以存储***任意类型***的数据，因为存数据的指针是`void`类型。同时也支持静态和动态初始化。<br>
数据结构有，可***自动扩展长度***的`ArrayList`、双向链表`LinkedList`、双向循环链表`CircleList`、环形队列`CircleQueue`、***任意叉***树`Tree`、栈`Stack`、字典（基于<a href="https://troydhanson.github.io/uthash/">uthash</a>）`Dictionary`。 <br>
设计模式有，迭代器`Iterator`。

## 🔭 Topology <a name = "topology"></a>

各结构的“继承”关系如下
![image](https://github.com/TIMESTICKING/Ctruct_SD/blob/master/images/Ctruct_SD.png)

## 👀 Take a glance <a name = "take_a_glance"></a>

这里将简单展示三个例子，分别是`ArrayList`, `CircleList`以及`Dictionary`

1、第一个例子是ArrayList，展示了向数组添加3个数字，注意到数组长度只被初始化了为1，然后逆序了数组，并输出了它的样子。随后删除了它最后一个元素，并输出了样子。最后打印了数组的基本信息。
```
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
	int_arr->FREE(int_arr); // because you've malloced it
}

>. output
int_arr now looks like-------
get: 13
get: 4
get: 1

delete last element of int_arr
int_arr now looks like-------
get: 13
get: 4
======ArrayList:int_arr======
=>arraylist=>ifinitial: 1
=>arraylist=>length:    2
=>arraylist=>capacity:  10
=======================
```

2、第二个例子展示了`CircleList`。首先初始化了`CircleList`和`Tree_node`，然后添加了两句话，打印了`CircleList`的基本信息；然后删除了最后一个元素再打印基本信息；再往头部添加了一句话打印基本信息；最后输出整个循环链表的存储值。

***值得一提的是`CircleList`是基于`LinkedList`的，而后者又是基于`Tree`的。它们的共同点都是具有“节点”的特质，故接收节点需要用类型`Tree_node`来处理。<br>
说到这了就顺带再介绍一下`ArrayList`是这里顺序存储结构中的基类型，即`CircleQueue`和`Stack`是基于它的，或说“继承”它的。***

同时打印循环链表是需要用变量来控制打印次数多，如代码中的`t`，否则它将循环打印下去。
```
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

>. output
======CircleLinkedList_SD:circleList_def======
=>CircleLinkedList_SD=>ifinitial:       1
=>LinkedList_SD=>ifinitial:     1
=>LinkedList_SD=>head node:     0x55804270
=>LinkedList_SD=>tail node:     0x558042c0
=>Tree=>ifinitial:      1
=>Tree=>count:  2
=======================
======CircleLinkedList_SD:circleList_def======
=>CircleLinkedList_SD=>ifinitial:       1
=>LinkedList_SD=>ifinitial:     1
=>LinkedList_SD=>head node:     0x55804270
=>LinkedList_SD=>tail node:     0x55804270
=>Tree=>ifinitial:      1
=>Tree=>count:  1
=======================
======CircleLinkedList_SD:circleList_def======
=>CircleLinkedList_SD=>ifinitial:       1
=>LinkedList_SD=>ifinitial:     1
=>LinkedList_SD=>head node:     0x558042c0
=>LinkedList_SD=>tail node:     0x55804270
=>Tree=>ifinitial:      1
=>Tree=>count:  2
=======================
data is: I'm the newer
data is: string alpha
data is: I'm the newer
data is: string alpha
data is: I'm the newer
data is: string alpha
data is: I'm the newer
data is: string alpha
data is: I'm the newer
data is: string alpha
```

3、第三个例子展示了`Dictionary`。首先存了2个键对值，再分别取出他们。如果你不确定某个key是否存在，建议您使用`res3`的例子对其进行判断。
```
void test_dict(void){
    Dictionary mydict;
    
    InitDictionary(&mydict);
    mydict.name = "dict1";
    mydict.ADD_EDIT_dict(&mydict,"number",INT_new(3)); //keys and values
    mydict.ADD_EDIT_dict(&mydict,"string","hello my baby~");
    
    int* res;
    res = (int*)mydict.GET_dict(&mydict, "number");
    SD_PRINT("res is: %d", *res);

	// you'd better check the existence of the key if u'r not sure
	void* res3 = mydict.GET_dict(&mydict, "string");
	if (res3)
		SD_PRINT("res3 is: %s", (char*)res3);
}

>. output 
res is: 3
res3 is: hello my baby~
```

## 🏁 Getting Started <a name = "getting_started"></a>

所有数据结构的样例都在`main.c`中存在，API可能不全，往后将在[这里](#APIs)列出。您可修改`main.c`文件来熟悉各个数据结构，亦可阅读它们的源码。

### 编译并运行这个项目
```
mkdir build
cd build/
cmake ..
make
../bin/datastruct
```

## 🚀 APIs <a name = "APIs"></a>

visit API document [here](#https://timesticking.github.io/Ctruct_SD/).


## 🎉 Acknowledgements <a name = "acknowledgement"></a>

- If you find this repo helps, a 🌟 will be the best support! Thank you!
- Please cite this repo if you utilize it in your projects. Thank you!
