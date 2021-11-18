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

## :four: map 库

## :five: string库
