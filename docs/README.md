
<h3 align="center">Ctruct: A variety of  data structures in pure C</h3>

---

<p align="left"> 这是一个由纯C编写的多种数据结构项目，项目起初是用于学习，后可拓展到嵌入式编程领域。我感觉还是用于学习比较好，因为它的适用场景并不多。
    <br> 
    This is a variety of data structures written in pure C project, the project was originally used for learning, and then can be extended to the embedded programming field. I think it's better to use it for study because it seems doesn't apply to many scenarios.
</p>
<p>
visit github project <a href="https://github.com/TIMESTICKING/Ctruct_SD">here</a>
</p>

## 📝 Table of Contents

- [About](#about)
- [Topology](#topology)
- [Return Values](#return)

## 🧐 About <a name = "about"></a>

项目采用结构体来**模拟面向对象**的编程方式，但受语言限制，“方法”仍需传入“类”自身。同时下标采用了负数表示法，例如-1表示最后一个元素。<br>
项目包含的数据结构可以存储**任意类型**的数据，因为存数据的指针是`void*`类型。同时也支持静态和动态初始化。<br>
数据结构有，可**自动扩展长度**的`ArrayList`、双向链表`LinkedList`、双向循环链表`CircularList`、环形队列`CircularQueue`、**任意叉**树`Tree`、栈`Stack`、字典（基于<a href="https://troydhanson.github.io/uthash/">uthash</a>）`Dictionary`。 <br>
设计模式有，迭代器`Iterator`。<br>

在`main.c`文件中查看示例。

---

The project uses C struct to **simulate object-oriented** programming, but due to language limitations, "methods" still need to be passed into "classes" themselves. The subscript also uses negative notation, such as -1 for the last element.<br>
The project contains a data structure that can store **any type** of data because the pointer to the data is of type `void`. Static and dynamic initialization are also supported.<br>
Data structures include **Auto-increment** `ArrayList`, Bi-directional `LinkedList`, Bi-directional `CircularList`, `CircularQueue`, **Arbitrary** `Tree`, `Stack`, `Dictionary` (based on <a href="https://troydhanson.github.io/uthash/">uthash</a>).<br>
The design patterns are Iterator.<br>

See the examples in the `main.c` file.

## 🔭 Topology <a name = "topology"></a>

各结构的“继承”关系如下<br>
![image](./images/Ctruct_SD.png)

## Return Values <a name = "return"></a>

```clike
#define ARR_OK			1
#define ARR_UN_INIT		-5
#define ARR_WRONG_INDEX	-1
#define ARR_MALLOC_FAIL	3
#define ARR_MOVE_FAIL	2
#define ARR_INPUT_SAME	-2
#define ARR_FALSE		0
#define ARR_EMPTY_CLIST	-3

#define NULL_void	((void*)0)
#define	NULL_node	(Tree_node*)0
```
