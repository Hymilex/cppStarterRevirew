# C++ 头文件基础 

<h2>目录</h2>

- [C++ 头文件基础](#c-头文件基础)
  - [:one: 标准头文件](#one-标准头文件)
    - [Standard C Header Lib](#standard-c-header-lib)
    - [Standard Cpp Header Lib](#standard-cpp-header-lib)
  - [:two: 自定义头文件](#two-自定义头文件)
  - [:three: 参考](#three-参考)


## :one: 标准头文件

---

> 以下是比较常见的C、C++的标准头文件。

### Standard C Header Lib

```C

//C
#include <assert.h>　　　　//设定插入点
#include <ctype.h>　　　　 //字符处理
#include <errno.h>　　　　 //定义错误码
#include <float.h>　　　　 //浮点数处理
#include <iso646.h>        //对应各种运算符的宏
#include <limits.h>　　　　//定义各种数据类型最值的常量
#include <locale.h>　　　　//定义本地化C函数
#include <math.h>　　　　　//定义数学函数
#include <setjmp.h>        //异常处理支持
#include <signal.h>        //信号机制支持
#include <stdarg.h>        //不定参数列表支持
#include <stddef.h>        //常用常量
#include <stdio.h>　　　　 //定义输入／输出函数
#include <stdlib.h>　　　　//定义杂项函数及内存分配函数
#include <string.h>　　　　//字符串处理
#include <time.h>　　　　　//定义关于时间的函数
#include <wchar.h>　　　　 //宽字符处理及输入／输出
#include <wctype.h>　　　　//宽字符分类

// 传统C++
#include <fstream.h>　　　 //改用<fstream>
#include <iomanip.h>　　　 //改用<iomainip>
#include <iostream.h>　　　//改用<iostream>
#include <strstrea.h>　　　//该类不再支持，改用<sstream>中的stringstream

```

### Standard Cpp Header Lib

```C++

// 标准C++　
#include <algorithm>　　　 //STL 通用算法
#include <bitset>　　　　　//STL 位集容器
#include <cctype>         //字符处理
#include <cerrno> 　　　　 //定义错误码
#include <cfloat>　　　　 //浮点数处理
#include <ciso646>         //对应各种运算符的宏
#include <climits> 　　　　//定义各种数据类型最值的常量
#include <clocale> 　　　　//定义本地化函数
#include <cmath> 　　　　　//定义数学函数
#include <complex>　　　　 //复数类
#include <csignal>         //信号机制支持
#include <csetjmp>         //异常处理支持
#include <cstdarg>         //不定参数列表支持
#include <cstddef>         //常用常量
#include <cstdio> 　　　　 //定义输入／输出函数
#include <cstdlib> 　　　　//定义杂项函数及内存分配函数
#include <cstring> 　　　　//字符串处理
#include <ctime> 　　　　　//定义关于时间的函数
#include <cwchar> 　　　　 //宽字符处理及输入／输出
#include <cwctype> 　　　　//宽字符分类
#include <deque>　　　　　 //STL 双端队列容器
#include <exception>　　　 //异常处理类
#include <fstream> 　　　 //文件输入／输出
#include <functional>　　　//STL 定义运算函数（代替运算符）
#include <limits> 　　　　 //定义各种数据类型最值常量
#include <list>　　　　　　//STL 线性列表容器
#include <locale>         //本地化特定信息
#include <map>　　　　　　 //STL 映射容器
#include <memory>         //STL通过分配器进行的内存分配
#include<new>            //动态内存分配
#include <numeric>         //STL常用的数字操作
#include <iomanip> 　　　 //参数化输入／输出
#include <ios>　　　　　　 //基本输入／输出支持
#include <iosfwd>　　　　　//输入／输出系统使用的前置声明
#include <iostream> 　　　//数据流输入／输出
#include <istream>　　　　 //基本输入流
#include <iterator>        //STL迭代器
#include <ostream>　　　　 //基本输出流
#include <queue>　　　　　 //STL 队列容器
#include <set>　　　　　　 //STL 集合容器
#include <sstream>　　　　 //基于字符串的流
#include <stack>　　　　　 //STL 堆栈容器
#include <stdexcept>　　　 //标准异常类
#include <streambuf>　　　 //底层输入／输出支持
#include <string>　　　　　//字符串类
#include <typeinfo>        //运行期间类型信息
#include <utility>　　　　 //STL 通用模板类
#include <valarray>        //对包含值的数组的操作
#include <vector>　　　　　//STL 动态数组容器

// C99增加的部分
#include <complex.h>　　 //复数处理
#include <fenv.h>　　　　//浮点环境
#include <inttypes.h>　　//整数格式转换
#include <stdbool.h>　　 //布尔环境
#include <stdint.h>　　　//整型环境
#include <tgmath.h>　　　//通用类型数学宏

```



## :two: 自定义头文件

---

1、C++文件的 **include** 包含顺序?

为了避免隐藏依赖,增强可读性头文件的顺序为:

① 当前 **cpp** 文件对应的 **.h** 文件

② C系统文件

③ C++系统文件

④ 其他库的 **.h** 文件

⑤ 本项目内的 **.h** 文件

有时，平台特定（system-specific）代码需要条件编译（conditional includes），这些代码可以放到其它 includes 之后。当然，您的平台特定代码也要够简练且独立：

```C++
#include "base/logging.h"

#ifdef LANG_CXX11
#include <initializer_list>
#else
#include "base/port.h"
#endif

```


2、项目内头文件应按照项目源代码目录树结构排列, 避免使用 UNIX 特殊的快捷目录 . (当前目录) 或 .. (上级目录)。

```C++
#include "../../test.h"     // 不推荐
#include "base/logging.h"   // 推荐
```

3、什么是 **#define** 保护?

所有头文件都应该使用 **#define** 来防止头文件被多重包含, 命名格式当是: **\<PROJECT\>\_\<PATH\>\_\<FILE\>\_H\_**。

为保证唯一性, 头文件的命名应该基于所在项目源代码树的全路径. 例如, 项目 foo 中的头文件 lzt/src/util/log.h 可按如下方式保护:

```C++
#ifndef LZT_UTIL_LOG_H_
#define LZT_UTIL_LOG_H_

#endif //LZT_UTIL_LOG_H_

```

4、什么是前置声明?

> 所谓「前置声明」（forward declaration）是类、函数和模板的纯粹声明，没伴随着其定义。尽可能地避免使用前置声明。使用 #include 包含需要的头文件即可。

5、内联函数的使用场景?

> 只有当函数只有 10 行甚至更少时才将其定义为内联函数。

一个较为合理的经验准则是, 不要内联超过 10 行的函数. 谨慎对待析构函数, 析构函数往往比其表面看起来要更长, 因为有隐含的成员和基类析构函数被调用!

另一个实用的经验准则: 内联那些包含循环或 switch 语句的函数常常是得不偿失 (除非在大多数情况下, 这些循环或 switch 语句从不被执行)。

有些函数即使声明为内联的也不一定会被编译器内联, 这点很重要; 比如虚函数和递归函数就不会被正常内联. 通常, 递归函数不应该声明成内联函数。


## :three: 参考

1、[Google开源项目风格指南](https://google-styleguide.readthedocs.io/zh_CN/latest/google-cpp-styleguide/headers.html)