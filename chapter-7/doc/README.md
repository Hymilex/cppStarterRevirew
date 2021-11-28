# C++ 的 array 等常见数据结构库

<h2>
目录
</h2>

- [C++ 的 array 等常见数据结构库](#c-的-array-等常见数据结构库)
	- [:one: array 库](#one-array-库)
		- [概述](#概述)
		- [头文件](#头文件)
		- [创建容器](#创建容器)
		- [元素访问](#元素访问)
		- [常用方法](#常用方法)
	- [:two: vector 库](#two-vector-库)
		- [概述](#概述-1)
		- [头文件](#头文件-1)
		- [创建](#创建)
		- [访问](#访问)
		- [常用方法和属性](#常用方法和属性)
		- [vector 和 array区别](#vector-和-array区别)
			- [共同点](#共同点)
			- [不同点](#不同点)
	- [:three: set 库](#three-set-库)
	- [:four: map 库](#four-map-库)
		- [简介](#简介)
		- [功能](#功能)
		- [代码展示](#代码展示)
	- [:five: deque库](#five-deque库)
		- [简介](#简介-1)
		- [常规操作](#常规操作)
			- [Capacity](#capacity)
			- [Element access](#element-access)
			- [Modifiers](#modifiers)
	- [:six: queue库](#six-queue库)
		- [简介](#简介-2)
		- [常规操作](#常规操作-1)
		- [区别](#区别)
	- [:seven: forward_list库](#seven-forward_list库)
		- [简介](#简介-3)
	- [:eight:list库](#eightlist库)
		- [简介](#简介-4)
	- [:nine:stack库](#ninestack库)
		- [简介](#简介-5)
		- [操作](#操作)


## :one: array 库

---

### 概述

C++ 标准模版库 std::array 是对 C 语言原生定长数组的容器化封装，于 C++ 11 被加入到 STL 中。


### 头文件

> #include <array>

### 创建容器

```C++
array<int, 3> arrInt = {1, 2, 3, };
array<double, 3> arrDouble = {1.0, 2.0, 3.0, };
array<string, 3> arrStr = {std::string("a"), "b", "c", };
array<int*, 3> arrPointer = {NULL, NULL, NULL, };
```

### 元素访问

```C++
array<int, 3> arr = {1, 2, 3, };

// 下标访问
cout << arr[0] << endl;
cout << arr.at(0) << endl;

// 迭代器
for (int *iter = arr.begin(); iter != arr.end(); iter++) {
    cout << *iter << endl;
}

// forEach 迭代
for (int n : arr) {
    cout << n << endl;
}

```

### 常用方法


| :smile:方法 | :book:解释             |
| :---------- | :--------------------- |
| at          | 下标访问（带边界检查） |
| operator[]  | 下标访问（无边界检查） |
| front       | 访问首位元素           |
| back        | 访问末位元素           |
| data        | 获取底层 C 数组指针    |
| size        | 获取容器容量           |
| fill        | 填充容器元素           |
| empty       | 检查容器是否为空       |

```C++
#include <experimental/array>
#include <iostream>
#include <type_traits>

int main()
{
    auto arr = std::experimental::make_array(1, 2, 3, 4, 5);
    bool is_array_of_5_ints = std::is_same<decltype(arr), std::array<int, 5>>::value;
    std::cout << "Returns an array of five ints? ";
    std::cout << std::boolalpha << is_array_of_5_ints << '\n';
}

```

参考:
https://zihengcat.github.io/2020/05/01/cpp-stl-concise-tutorial-array/



## :two: vector 库

---

### 概述

std::vector 是封装动态数组的顺序容器。连续存储元素，这意味着不仅可通过迭代器，还能用指向元素的常规指针访问元素。这意味着指向 vector 元素的指针能传递给任何期待指向数组元素的指针的函数。

vector 的存储是自动管理的，按需扩张收缩。 vector 通常占用多于静态数组的空间，因为要分配更多内存以管理将来的增长。

vector 所用的方式不在每次插入元素时，而只在额外内存耗尽时重分配。分配的内存总量可用 capacity() 函数查询。可通过调用 shrink_to_fit() 返回多出的内存给系统。

### 头文件

> #include <vector>


### 创建

```C++
std::vector<int> age = {1,2,3,4};
std::vector<double> price = {2.3,1.5,4.9};
std::vector<Cat> cats = {Cat(),Cat(),Cat()};
```


### 访问

访问和array基本一致。


### 常用方法和属性

常用方法和array基本一致。

```C++

#include <iostream>
#include <vector>
 
int main()
{
    // 创建含有整数的 vector
    std::vector<int> v = {7, 5, 16, 8};
 
    // 添加二个整数到 vector
    v.push_back(25);
    v.push_back(13);
    v.emplace_back(22);
    // 迭代并打印 vector 的值
    for(int n : v) {
        std::cout << n << '\n';
    }
}

```

1、emplace_back和push_back区别?

push_back传入一个事先存在的元素对象，调用的是拷贝或移动构造来生成这个新压入的元素对象：construct(\*des, class_name&|&& x)） emplace_back：多个事先存在的对象，调用示义：construct(*des, other_type &x|&&x, type_name &|&&,...) emplace_back传参不定，编译器需要在调用时才生成具体的实现，push_back只是emplace_back的两个偏移化版本！ 

push_back只能用类中的拷贝或移动构造，而emplace_back还可以是类中的其他多参数的构造函数，这是优点也是缺点（代码翻倍）&&在普通函数中作为参数时，是万能引用，并不是右值引用，在函数体中会使用forward完美转发，调用时是复制或移动和你传的值有关，你传左值它就用左值版本，传右值就用右值版本，心里要有数。如果一个类没有上诉的拷贝或移动构造，则不能用于STL容器中，如果没有相应参数类型的构造实现，emplace_back编译不过，找不到它需要的对应构造函数.. move和copy构造唯一区别：move时，指针属性只是简单的拷贝指针，而copy中，指针属性被拷贝的同时，它所指的具体内容也还需要深度copy下去...我们在实现类的两个构造时特别要注意这一点，move中要将旧对象的指针属性置nullptr，这意味着相应的对象不再适合使用了（它必须是临时对象的原因！转移后，内部的指针属性失效！） move和copy的性能对比：正如上说，move只是指针优化，如果类本身没有指针属性，则它不需要move，我们也不必强制move不可，copy和move在内置类型和简单类型（指无指针属性、即构造时不需要new）没区别


### vector 和 array区别

#### 共同点

- 都和数组相似，都可以使用标准数组的表示方法来访问每个元素（array和vector都对下标运算符[ ]进行了重载）

- 三者的存储都是连续的，可以进行随机访问

#### 不同点

- 数组是不安全的，array和vector是比较安全的（有效的避免越界等问题）
- array对象和数组存储在相同的内存区域（栈）中，vector对象存储在自由存储区（堆）
- array可以将一个对象赋值给另一个array对象，但是数组不行
- vector属于变长的容器，即可以根据数据的插入和删除重新构造容器容量；但是array和数组属于定长容器
- vector和array提供了更好的数据访问机制，即可以使用front()和back()以及at()（at()可以避免a[-1]访问越界的问题）访问方式，使得访问更加安全。而数组只能通过下标访问，在写程序中很容易出现越界的错误
- vector和array提供了更好的遍历机制，即有正向迭代器和反向迭代器
- vector和array提供了size()和Empty()，而数组只能通过sizeof()/strlen()以及遍历计数来获取大小和是否为空
- vector和array提供了两个容器对象的内容交换，即swap()的机制，而数组对于交换只能通过遍历的方式逐个交换元素
- array提供了初始化所有成员的方法fill（）
- 由于vector的动态内存变化的机制，在插入和删除时，需要考虑迭代的是否有效问题
- vector和array在声明变量后，在声明周期完成后，会自动地释放其所占用的内存。对于数组如果用new[ ]/malloc申请的空间，必须用对应的delete[ ]和free来释放内存


## :three: set 库

---

> 集合是遵循严格的弱排序来存储唯一元素的容器。set在插入元素后会对元素进行默认弱排序。



```C++
#include <set>
#include <iostream>
#include <string>

int main()
{
	using namespace std;
	std::set<std::string> setOfNumbers;
	// Lets insert four elements
	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");
	setOfNumbers.insert("first");
	// Only 3 elements will be inserted
	std::cout << "Set Size = " << setOfNumbers.size() << std::endl;
	// Iterate through all the elements in a set and display the value.
	std::set<std::string>::iterator it;
	for (it = setOfNumbers.begin(); it != setOfNumbers.end(); ++it)
	{
		std::cout << " " << *it<<std::endl;
	}
	std::cout << "\n";
	std::cout << "find :" << *setOfNumbers.find("third") << endl;
	return 0;
}

```

## :four: map 库

---

### 简介

Map是STL的一个关联容器，它提供一对一（其中第一个可以称为关键字，每个关键字只能在map中出现一次，第二个可能称为该关键字的值）的数据 处理能力，由于这个特性，它完成有可能在我们处理一对一数据的时候，在编程上提供快速通道。这里说下map内部数据的组织，map内部自建一颗红黑树(一 种非严格意义上的平衡二叉树)，这颗树具有对数据自动排序的功能，所以在map内部所有的数据都是有序的。

> map是一类关联式容器。它的特点是增加和删除节点对迭代器的影响很小，除了那个操作节点，对其他的节点都没有什么影响。对于迭代器来说，可以修改实值，而不能修改key。


### 功能

自动建立Key－value的对应。key 和 value可以是任意你需要的类型。

根据key值快速查找记录，查找的复杂度基本是Log(N)，如果有1000个记录，最多查找10次，1,000,000个记录，最多查找20次。

### 代码展示

```C++

#include <map>
#include <string>
struct Student
{
public:
	std::string name;
public:
	Student() {}
	~Student() {}
	void learn()
	{
		std::cout << name << " is learning at present.\n";
	}
private:
	size_t phoneNumber;
};
struct Teacher
{
public:
	std::string subject;
	std::string name;
	size_t phoneNumber;
public:
	Teacher() {}
	Teacher(const Teacher& t)
	{
		(*this).subject = t.subject;
		(*this).name = t.name;
		(*this).phoneNumber = t.phoneNumber;
	}
	Teacher(const Teacher* t)
	{
		this->subject = t->subject;
		this->name = t->name;
		this->phoneNumber = t->phoneNumber;
	}

	void teachKnowledge()
	{
		std::cout << "teach " << subject << "now . \n";
	}
};

void printHelloWorld()
{
	const char* hello_world_str = "hello world!";
	printf("[ %s ].\n", hello_world_str);
}

void mapTest()
{
	using TeacherStudentMap = std::map<const ::Student*, std::set<const ::Teacher*>>;
	TeacherStudentMap forwardYearMap, lastYearMap;
	auto insertTeacherStudentMap = [](TeacherStudentMap& teacherStudentMap,const Student* student,const Teacher* teacher) {\
		// 指向键等于 key 的元素的迭代器。若找不到这种元素，则返回尾后（见 end() ）迭代器。
		if (teacherStudentMap.find(student) == teacherStudentMap.end())
		{
			teacherStudentMap[student] = std::set<const Teacher*>({teacher});
		}
		else
		{
			teacherStudentMap[student].insert(teacher);
		}
	};
	using LearnMap = std::map<const Student*, void(*)()>;
	using TeachMap = std::map<const Teacher*, void(*)()>;
	auto insertLearnTeachMap = [](LearnMap& learnMap, const Student* student)
	{
		if (learnMap.find(student) == learnMap.end())
		{
			// insert智能添加新的key value对
			//learnMap[student] = printHelloWorld;  // C++11 可以使用
			learnMap.insert({student,printHelloWorld}); // C++17起引入
		}
		else
		{
			// [] 可以覆盖key对应的value
			learnMap[student] = printHelloWorld;
		}
	};

	LearnMap learn_map;
	const Student student;
	insertLearnTeachMap(learn_map, &student);
	learn_map[&student]();	  // 访问map节点方式1
	learn_map.at(&student)(); // 访问map节点方式2
}

```
- 参考:

    https://blog.csdn.net/qq_28351609/article/details/84630535

## :five: deque库

---

### 简介

std::deque （ double-ended queue ，**双端队列**）是有下标顺序容器，它允许在其首尾两端快速插入及删除。另外，在 deque 任一端插入或删除不会非法化指向其余元素的指针或引用。

与 std::vector 相反， deque 的元素不是相接存储的：典型实现用单独分配的固定大小数组的序列，外加额外的登记，这表示下标访问必须进行二次指针解引用，与之相比 vector 的下标访问只进行一次。


deque 的存储按需自动扩展及收缩。扩张 deque 比扩张 std::vector 更优，因为它不涉及到复制既存元素到新内存位置。另一方面， deque 典型地拥有较大的最小内存开销；只保有一个元素的 deque 必须分配其整个内部数组（例如 64 位 libstdc++ 上为对象大小 8 倍； 64 位 libc++ 上为对象大小 16 倍或 4096 字节的较大者）。


### 常规操作

#### Capacity

| 方法          | 解释                                             |
| ------------- | ------------------------------------------------ |
| empty         | 检查是否为空, 若容器为空则为 true ，否则为 false |
| size          | 返回容纳的元素数                                 |
| max_size      | 返回可以容纳的最大元素数                         |
| shrink_to_fit | 通过释放未使用的内存减少内存的使用               |

#### Element access

| 方法       | 解释                                                                      |
| ---------- | ------------------------------------------------------------------------- |
| at         | 访问指定元素,同时进行越界检查;若 !(pos < size()) 则抛出 std::out_of_range |
| operator[] | 访问指定元素                                                              |
| front      | 返回第一个元素                                                            |
| end        | 返回最后一个元素                                                          |


```C++

#include <iostream>
#include <deque>
 
int main()
{
    std::deque<int> data = { 1, 2, 4, 5, 5, 6 };
 
    // Set element 1
    data.at(1) = 88;
 
    // Read element 2
    std::cout << "Element at index 2 has value " << data.at(2) << '\n';
 
    std::cout << "data size = " << data.size() << '\n';
 
    try {
        // Set element 6
        data.at(6) = 666;
    } catch (std::out_of_range const& exc) {
        std::cout << exc.what() << '\n';
    }
 
    // Print final values
    std::cout << "data:";
    for (int elem : data)
        std::cout << " " << elem;
    std::cout << '\n';
}


```


#### Modifiers

| 方法          | 解释                   |
| ------------- | ---------------------- |
| clear         | 清除内容               |
| insert        | 插入元素               |
| emplace       | 原位构造元素           |
| erase         | 擦除元素               |
| push_back     | 将元素添加到容器末尾   |
| emplace_back  | 在容器末尾就地构造元素 |
| pop_back      | 移除末元素             |
| push_front    | 插入元素到容器起始     |
| emplace_front | 在容器头部原位构造元素 |
| pop_front     | 移除首元素             |



```C++

#include <deque>
void dequeTest()
{
	struct Candidate {
		int boxIndex;
		float score;
	};
	auto cmp = [](const Candidate bsI, const Candidate bsJ) {return bsI.score < bsJ.score; };
	// decltype是判断cmp的数据类型
	std::priority_queue<Candidate, std::deque<Candidate>, decltype(cmp)> candidatePriorityQueue(cmp);
}

```



## :six: queue库

---


### 简介

std::queue 类是容器适配器，它给予程序员队列的功能——尤其是 FIFO （先进先出）数据结构。

类模板表现为底层容器的包装器——只提供特定的函数集合。 queue 在底层容器尾端推入元素，从首端弹出元素。


### 常规操作

| 方法 | 解释                                            |
| ---- | ----------------------------------------------- |
| push | 向队列尾部插入元素                              |
| pop  | 从 queue 移除前端元素。等效地调用 c.pop_front() |


### 区别

deque是双向队列,queue是单向的。


## :seven: forward_list库

### 简介

std::forward_list 是支持从容器中的**任何位置** | **快速插入** |和 | **移除元素** |的容器。

不支持快速随机访问。它实现为**单链表**，且实质上与其在 C 中实现相比无任何开销。与 std::list 相比，此容器在不需要双向迭代时提供更有效地利用空间的存储。




## :eight:list库


### 简介

std::list是一个容器，它支持从容器中的任何地方插入和删除元素的恒定时间。不支持快速随机访问。它通常被实现为一个| **双向链表** |。与std::forward_list相比，此容器提供双向迭代功能，但 | **空间效率较低** |。



```C++
#ifndef ImagePool_hpp
#define ImagePool_hpp

#include <list>
#include <map>
#include "core/NonCopyable.hpp"
#include "backend/opencl/core/runtime/OpenCLWrapper.hpp"
namespace MNN {
namespace OpenCL {

class ImagePool : public NonCopyable {
public:
    ImagePool(cl::Context& context) : mContext(context) {
    }

    cl::Image* alloc(int w, int h, cl_channel_type type, bool seperate = false);
    void recycle(cl::Image* image, bool release = false);
    void clear();

    struct Node {
        int w;
        int h;
        std::shared_ptr<cl::Image> image;
    };

private:
    std::map<cl::Image*, std::shared_ptr<Node>> mAllImage;
    std::list<std::shared_ptr<Node>> mFreeList; // 一个包含共享指针节点的List

    cl::Context& mContext;
};

} // namespace OpenCL
} // namespace MNN
#endif /* ImagePool_hpp */


```



## :nine:stack库

---

### 简介

std::stack 类是容器适配器，它给予程序员栈的功能——特别是 FILO （先进后出）数据结构。

该类模板表现为底层容器的包装器——只提供特定函数集合。栈从被称作栈顶的容器尾部推弹元素。


### 操作

是数据结构中最为简单的数据结构。详细可访问:

1、https://zh.cppreference.com/w/cpp/container/stack

2、https://www.cplusplus.com/reference/stack/stack/



