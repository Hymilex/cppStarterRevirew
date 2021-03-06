# C++ 堆栈变量的生命周期

<h2>目录
</h2>

- [C++ 堆栈变量的生命周期](#c-堆栈变量的生命周期)
  - [:one:概述](#one概述)
  - [:two:堆和栈的比较](#two堆和栈的比较)
    - [申请方式](#申请方式)
    - [申请后系统的响应](#申请后系统的响应)
    - [申请大小的限制](#申请大小的限制)
    - [申请效率的比较](#申请效率的比较)
    - [堆和栈中的存储内容](#堆和栈中的存储内容)
    - [存取效率的比较](#存取效率的比较)
  - [:three: 为什么栈比较快](#three-为什么栈比较快)
  - [:four:实战](#four实战)


## :one:概述

---

一个由 C/C++ 编译的程序占用的内存分为以下几个部分:

**栈区(stack)**

由编译器自动分配释放，存放为运行函数而分配的局部变量、函数参数、返回数据、返回地址等。其操作方式类似于数据结构中的栈。

**堆区(heap)**

一般由程序员分配释放， 若程序员不释放，程序结束时可能由 OS 回收 。分配方式类似于链表。

**静态区/全局区(static)**

存放全局变量、静态数据。初始化的数据放在一块区域，未初始化的数据放在相邻的另一块区域。程序结束后由系统释放。

**文字常量区**

常量字符串就是放在这里的。程序结束后由系统释放。

**程序代码区**

存放函数体（类成员函数和全局函数）的二进制代码。


## :two:堆和栈的比较

---

### 申请方式

**栈(stack)**

由系统自动分配。

**堆(heap)**

需要程序员自己申请,并指明大小,在C中使用**malloc**函数,在C++中使用的是**new**运算符。

### 申请后系统的响应

**栈(stack)**

只要栈的剩余空间大于所申请空间，系统将为程序提供内存，否则将报异常提示栈溢出。

**堆(heap)**

首先应该知道操作系统有一个记录空闲内存地址的链表，当系统收到程序的申请时，会遍历该链表，寻找第一个空间大于所申请空间的堆结点，然后将该结点从空闲结点链表中删除，并将该结点的空间分配给程序。

对于大多数系统，会在这块内存空间中的首地址处记录本次分配的大小，这样，代码中的 delete 语句才能正确的释放本内存空间。
由于找到的堆结点的大小不一定正好等于申请的大小，系统会自动的将多余的那部分重新放入空闲链表中。


### 申请大小的限制

**栈(stack)**

在Windows下，栈是向低地址扩展的数据结构，是一块连续的内存的区域。意思是栈顶的地址和栈的最大容量是系统预先规定好的，在Windows下，栈的大小是 2M （也有的说是 1M ，总之是一个编译时就确定的常数），如果申请的空间超过栈的剩余空间时，将提示overflow。因此，能从栈获得的空间较小。

**堆(heap)**

堆是向高地址扩展的数据结构，是不连续的内存区域。这是由于系统是用链表来存储的空闲内存地址的，自然是不连续的，而链表的遍历方向是由低地址向高地址。堆的大小受限于计算机系统中有效的虚拟内存。由此可见，堆获得的空间比较灵活，也比较大。


### 申请效率的比较

**栈(stack)**

栈由系统自动分配，速度较快。但程序员是无法控制的 。

**堆(heap)**

堆是由 new 分配的内存，一般速度比较慢，而且容易产生内存碎片 , 不过用起来方便 。

### 堆和栈中的存储内容

**栈(stack)**

在函数调用时，第一个进栈的是主函数中后的下一条指令（函数调用语句的下一条可执行语句）的地址，然后是函数的各个参数，在大多数的 C 编译器中，参数是由右往左入栈的，然后是函数中的局部变量。注意静态变量是不入栈的。

当本次函数调用结束后，局部变量先出栈，然后是参数，最后栈顶指针指向最开始存的地址，也就是主函数中的下一条指令，程序由该点继续运行。


**堆(heap)**

一般是在堆的头部用一个字节存放堆的大小。堆中的具体内容有程序员安排。


### 存取效率的比较

```C++
int main()
{
    char a = 1;
    // 是在运行时刻赋值的
    char c[] = /"12345678/";
    // 是在编译时确定的
    char *p  = /"12345678/";

    return 0;
}

```

第一种在读取时直接就把字符串中的元素读到寄存器 cl 中，而第二种则要先把指针值读到 edx 中，再根据 edx 读取字符，显然慢了。

综上，堆和栈的主要区别我们就明白:
使用栈就相当于在超市买东西,有什么只能买什么,买完就直接完事了。
使用堆就相当于去菜市场买菜,买完菜还得洗菜、切菜、做菜,然后才能吃菜。


## :three: 为什么栈比较快

在具体的C/C++编程框架中，这两个概念并不是并行的。栈是机器系统提供的数据结构，而堆栈是C/C++函数库提供的。
具体来说，现代计算机，都直接在代码底层支持栈的数据结构。这体现在，有专门的寄存器指向栈所在的地址，有专门的机器指令完成数据入栈出栈的操作。这种机制的特点是效率高，支持的数据有限，一般是整数，指针，浮点数等系统支持的数据类型，并不直接支持其他的数据结构。

和栈不同，堆的数据结构并不是由系统支持的，而是有函数库提供的。基本的malloc/realloc/free函数维护了一套内部的堆数据结构。当程序使用这些函数去获得新的内存空间时，这套函数首先试图从内部堆中寻找可用的内存空间，如果没有可以使用的内存空间，则试图利用系统调用来动态增加程序数据段的内存大小，新分配得到的空间首先被组织进内部堆中去，然后再以适当的形式返回给调用者。当程序释放分配的内存空间时，这片内存空间被返回内部堆结构中，可能会被适当的处理，比如和其他空间合并成更大的空闲空间。
使用这么复杂的机制有如下原因：

系统调用可能不支持任意大小的内存分配。有些系统的系统调用只支持固定大小及其倍数的内存请求（按页分配)；这样的话对于大量的小内存分类会造成浪费。
系统调用申请内存代价昂贵，涉及用户态和核心态的转换
没有管理的内存分配在大量复杂内存的分配释放下很容易造成内存碎片。
从这里我们可以看到，堆和栈相比，由于大量 new/delete 的使用，容易造成大量的内存碎片；由于没有专门的系统支持，效率很低；由于可能引发用户态和内核态的切换，内存的申请，代价变得更加昂贵。所以栈在程序中是应用最广泛的，就算是函数的调用也利用栈去完成，函数调用过程中的参数，返回地址，EBP和局部变量都采用栈的方式存放。

那么？我们应该荐尽量用栈，而不用堆吗？并不是的。
虽然栈有很多的好处，但是由于和堆相比不是那么灵活，且分配大量的内存空间，堆更加适合。

## :four:实战

```C++

class EntityLife
{
public:
	EntityLife() {
		std::cout << "Created EntityLife" << std::endl;
	}
	~EntityLife() {
		std::cout << "Destroyed EntityLife" << std::endl;
	}

private:

};

// 解决内存泄漏的类智能指针
class ScopePtr
{
private:
	EntityLife* m_Ptr;
public:
	ScopePtr(EntityLife* ptr) :m_Ptr(ptr)
	{}
	~ScopePtr()
	{
		delete m_Ptr;
	}
};

int main()
{
	EntityLife e_life; //当程序执行离开作用域时,内存自动释放
	EntityLife* e_ptr = new EntityLife(); // 当程序执行离开作用域时,内存不会自动释放,则会导致内存泄漏
	ScopePtr entity_sc_ptr = new EntityLife();
    delete e_ptr; // 使用delete进行释放后才算整个流程结束
    return 0;
}


```