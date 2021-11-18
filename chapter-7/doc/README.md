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

## :three: set 库

## :four: map 库

## :five: string库
