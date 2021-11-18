# C++ 的 array 、string库

<h2>
目录
</h2>


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

## :four: map 库

## :five: string库
