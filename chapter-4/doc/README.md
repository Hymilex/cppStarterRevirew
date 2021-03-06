# C++ 头文件高级

---

<h2>目录</h2>

- [C++ 头文件高级](#c-头文件高级)
  - [:one: 常规头文件](#one-常规头文件)
    - [理论](#理论)
      - [**pragma once** vs. **ifndef**](#pragma-once-vs-ifndef)
        - [定义](#定义)
        - [特性](#特性)
      - [宏](#宏)
        - [宏定义场景](#宏定义场景)
        - [可变参数宏](#可变参数宏)
      - [typedef](#typedef)
        - [基本语法](#基本语法)
        - [typedef 和 define](#typedef-和-define)
          - [用途](#用途)
          - [陷阱](#陷阱)
        - [c++11中提倡写法](#c11中提倡写法)
        - [总结](#总结)
    - [实践](#实践)
  - [:two: template头文件](#two-template头文件)
    - [理论 + 实践](#理论--实践)
      - [Basic Class Template](#basic-class-template)
      - [Function Template](#function-template)
      - [Variadic template data structures](#variadic-template-data-structures)
        - [可变模板参数定义](#可变模板参数定义)
        - [可变模板参数函数](#可变模板参数函数)
          - [递归函数方式展开参数包](#递归函数方式展开参数包)
          - [逗号表达式展开参数包](#逗号表达式展开参数包)
        - [可变模板参数类](#可变模板参数类)
          - [模版偏特化和递归方式来展开参数包](#模版偏特化和递归方式来展开参数包)
          - [继承](#继承)
      - [Alias template](#alias-template)
      - [Explicit instantiation](#explicit-instantiation)
  - [:three: cc文件调用](#three-cc文件调用)


## :one: 常规头文件

---

### 理论


#### **pragma once** vs. **ifndef**

##### 定义
> 为了避免同一个头文件被包含（include）多次，C/C++中有两种宏实现方式：一种是#ifndef方式；另一种是#pragma once方式。

##### 特性

 **#ifndef**的方式受C/C++语言标准支持。它不仅可以保证同一个文件不会被包含多次，也能保证内容完全相同的两个文件（或者代码片段）不会被不小心同时包含。
 缺点就是如果不同头文件中的宏名不小心“撞车”，可能就会导致你看到头文件明明存在，但编译器却硬说找不到声明的状况——这种情况有时非常让人郁闷。
 由于编译器每次都需要打开头文件才能判定是否有重复定义，因此在编译大型项目时，ifndef会使得编译时间相对较长，因此一些编译器逐渐开始支持#pragma once的方式。

简单说,如果宏定义重复,使用此种方式则无法正常运行。

```C++
// test1.h
#pragma once
#define PI 3.14

// test2.h
#pragma once
#define PI 3.1415926

```



**#pragma once** 一般由编译器提供保证：同一个文件不会被包含多次。注意这里所说的“同一个文件”是指物理上的一个文件，而不是指内容相同的两个文件。

你无法对一个头文件中的一段代码作pragma once声明，而只能针对文件。

优点是你不必再担心宏名冲突了，当然也就不会出现宏名冲突引发的奇怪问题。大型项目的编译速度也因此提高了一些。

缺点就是如果某个头文件有多份拷贝，本方法不能保证他们不被重复包含。当然，相比宏名冲突引发的“找不到声明”的问题，这种重复包含很容易被发现并修正。
另外，这种方式不支持跨平台！

简单说,如果宏定义重复,使用此种方式可以正常编译通过和运行,但是宏定义多次出现和声明,则会使用最新声明的进行函数调用。

```C++

// test3.h
#ifndef _TEST_3_H_
#define _TEST_3_H_

#define PI 3.14

#endif


// test4.h
#ifndef _TEST_4_H_
#define _TEST_4_H_

#define PI 3.1415926

#endif

```

#### 宏

> 宏只是对程序的文本起作用。宏并不是函数、语句,也不是类型定义。


##### 宏定义场景

1、定义常数

```C++
#pragma once

#define ZEROS 0
#define PI 3.1415926
#define FLASE false
#define TRUE true

```

2、定义变量

```C++
#pragma once

#ifndef DEBUG_MODE
#define DEBUG_MODE 1
#endif

```

3、包含头文件

```C++

#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define MNN_BUILD_FOR_IOS
#endif
#endif

```


4、定义条件变量

```C++

#pragma once

#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <sys/time.h>
#endif



#ifdef MNN_USE_LOGCAT
#include <android/log.h>
#define MNN_ERROR(format, ...) __android_log_print(ANDROID_LOG_ERROR, "MNNJNI", format, ##__VA_ARGS__)
#define MNN_PRINT(format, ...) __android_log_print(ANDROID_LOG_INFO, "MNNJNI", format, ##__VA_ARGS__)
#else
#define MNN_PRINT(format, ...) printf(format, ##__VA_ARGS__)
#define MNN_ERROR(format, ...) printf(format, ##__VA_ARGS__)
#endif


#ifdef DEBUG
#define MNN_ASSERT(x)                                            \
    {                                                            \
        int res = (x);                                           \
        if (!res) {                                              \
            MNN_ERROR("Error for %s, %d\n", __FILE__, __LINE__); \
            assert(res);                                         \
        }                                                        \
    }
#else
#define MNN_ASSERT(x)                                            \
    {                                                            \
        int res = (x);                                           \
        if (!res) {                                              \
            MNN_ERROR("Error for %d\n", __LINE__); \
        }                                                        \
    }
#endif

```


5、宏定义函数

```c++

#if defined(_MSC_VER)
#if defined(BUILDING_MNN_DLL)
#define MNN_PUBLIC __declspec(dllexport)
#elif defined(USING_MNN_DLL)
#define MNN_PUBLIC __declspec(dllimport)
#else
#define MNN_PUBLIC
#endif
#else
#define MNN_PUBLIC __attribute__((visibility("default")))
#endif


#ifdef __cplusplus
extern "C"{
#endif


#ifdef __cplusplus
}
#endif 

```

##### 可变参数宏

1、**\_\_VA_ARGS\_\_** 宏
**\_\_VA_ARGS\_\_** 宏用来表示可变参数的内容，简单来说就是将左边宏中 … 的内容原样抄写在右边__VA_ARGS__ 所在的位置。如下例代码:

```C++
#include <stdio.h>
#define debug(...) printf(__VA_ARGS__)
int main(void)
{
    int year = 2018；
    debug("this year is %d\n", year);  //效果同printf("this year is %d\n", year);
}

```

2、可变参数别称
另外，通过一些语法，你可以给可变参数起一个名字，而不是使用__VA_ARGS__ ，如下例中的args：

```C++
#include <stdio.h>
#define debug(format, args...) printf(format, args)
int main(void)
{
    int year = 2018；
    debug("this year is %d\n", year);  //效果同printf("this year is %d\n", year);
}
```
3、无参传入情况
与可变参数函数不同的是，可变参数宏中的可变参数必须至少有一个参数传入，不然会报错，为了解决这个问题，需要一个特殊的“##”操作，如果可变参数被忽略或为空，“##”操作将使预处理器(preprocessor)去除掉它前面的那个逗号。如下例所示:

```C++
#include <stdio.h>
#define debug(format, args...) printf(format, ##args)
int main(void)
{
    int year = 2018；
    debug("hello, world");  //只有format参数，没有args可变参数
}
```

4、宏连接符 **\#\#**
举个例子：宏定义为#define XNAME(n) x##n，代码为：XNAME(4)，则在预编译时，宏发现XNAME(4)与XNAME(n)匹配，则令 n 为 4，然后将右边的n的内容也变为4，然后将整个XNAME(4)替换为 x##n，亦即 x4，故最终结果为 XNAME(4) 变为 x4。如下例所示:

```C++
#include <stdio.h>
#define XNAME(n) x##n
#define PRINT_XN(n) printf("x" #n " = %d\n", x##n);
int main(void)
{
    int XNAME(1) = 14; // becomes int x1 = 14;
    int XNAME(2) = 20; // becomes int x2 = 20;
    PRINT_XN(1);       // becomes printf("x1 = %d\n", x1);
    PRINT_XN(2);       // becomes printf("x2 = %d\n", x2);
    return 0;
}
```



#### typedef

##### 基本语法


##### typedef 和 define

从以上的概念便也能基本清楚，typedef只是为了增加可读性而为标识符另起的新名称(仅仅只是个别名)，而#define原本在C中是为了定义常量,到了C++，const、enum、inline的出现使它也渐渐成为了起别名的工具。有时很容易搞不清楚与typedef两者到底该用哪个好，如#define INT int这样的语句，用typedef一样可以完成，用哪个好呢？我主张用typedef，因为在早期的许多C编译器中这条语句是非法的，只是现今的编译器又做了扩充。为了尽可能地兼容，一般都遵循#define定义“可读”的常量以及一些宏语句的任务，而typedef则常用来定义关键字、冗长的类型的别名。

宏定义只是简单的字符串代换(原地扩展)，而typedef则不是原地扩展，它的新名字具有一定的封装性，以致于新命名的标识符具有更易定义变量的功能。

- \#define 归预处理器管,没有参加编译，在预处理的时候就被替换掉了;typedef 归编译器管,参加编译和链接,typedef是重命名，可以为枚举结构体等等重新命名，提高代码整洁。
- typedef是有作用域的，而#define不管怎么写都是全局的

###### 用途

1、定义一种类型的别名，而不只是简单的宏替换。可以用作同时声明指针型的多个对象。

```C++
typedef   char*   PCHAR;     //   一般用大写
PCHAR   pa,   pb;                 //   可行，同时声明了两个指向字符变量的指针

// char   *pa,   *pb;
// 也可行，但相对来说没有用typedef的形式直观，尤其在需要大量指针的地方，typedef的方式更省事。
```

2、用在旧的C代码中（具体多旧没有查），帮助struct。以前的代码中，声明struct新对象时，必须要带上struct，即形式为：   struct   结构名。

```C++

struct   Vec2
{
        int   x;
        int   y;
};

struct Vec2 p1;  // normal c type

Vec2 p2; // C++ 结构名   对象名

typedef struct Vec3d{
  double x;
  double y;
  double z;
}Point3d;

Point3d p3;

```

3、用typedef来定义与平台无关的类型。

```C++
// 在目标平台一上，让它表示最高精度的类型为：
#ifdef __platform_v1
typedef long double REAL;  
#elif __platform_v2
typedef double REAL;  
#else
typedef float REAL;
#endif

```

4、为复杂的声明定义一个新的简单的别名。方法是：在原来的声明里逐步用别名替换一部分复杂声明，如此循环，把带变量名的部分留到最后替换，得到的就是原声明的最简化版。

```C++
// 原声明：int   *(*a[5])(int,   char*);
typedef int *(*pFun)(int,   char*);  
pFun a[5];

// void   (*b[10])   (void   (*)());
typedef   void   (*pFunParam)(); // 变量名为b，先替换右边部分括号里的，pFunParam为别名一：
typedef   void   (*pFunx)(pFunParam); // 再替换左边的变量b，pFunx为别名二：
pFunx   b[10];

//原声明：doube(*)()   (*e)[9];  
typedef   double(*pFuny)(); // 变量名为e，先替换左边部分，pFuny为别名一
typedef   pFuny   (*pFunParamy)[9]; //再替换右边的变量e，pFunParamy为别名二
pFunParamy   e;  

```
理解复杂声明可用的“右左法则”：从变量名看起，先往右，再往左，碰到一个圆括号就调转阅读的方向；括号内分析完就跳出括号，还是按先右后左的顺序，如此循环，直到整个声明分析完。举例：
```C++
int (*func)(int *p);
```
首先找到变量名func，外面有一对圆括号，而且左边是一个\*号，这说明func是一个指针；然后跳出这个圆括号，先看右边，又遇到圆括号，这说明<span>(\*func)</span>是一个函数，所以func是一个指向这类函数的指针，即函数指针，这类函数具有int\*类型的形参，返回值类型是int。
```
int   (*func[5])(int   *);
```

func右边是一个\[\]运算符，说明func是具有5个元素的数组；func的左边有一个*，说明func的元素是指针（注意这里的\*不是修饰func，而是修饰func[5]的，原因是\[\]运算符优先级比\*高，func先跟[]结合）。跳出这个括号，看右边，又遇到圆括号，说明func数组的元素是函数类型的指针，它指向的函数具有int*类型的形参，返回值类型为int。
也可以记住2个模式：
```C++
type   (*)(....)函数指针  
type   (*)[]数组指针  
```


###### 陷阱

1、typedef是定义了一种类型的新别名，不同于宏，它不是简单的字符串替换。

```
typedef   char*   PSTR;
int   mystrcmp(const   PSTR,   const   PSTR);
```

2、typedef在语法上是一个存储类的关键字（如auto、extern、mutable、static、register等一样）

##### c++11中提倡写法

```C++

using HYM_INT = int;

```


##### 总结
分析前面的分析差不多了，一句话，能不用宏的就坚决不用。用以下替代:
- typedef
- enum
- const integer
- constexpr
- template programming


### 实践

```C++

#ifndef HYLIM_H_
#define HYLIM_H_

namespace HySp
{
    enum Season{SPRING=0,SUMMER,AUTUMN,WINTER};
    
    enum
    {
        INFO =0,
        WARNING=1,
        ERROR=2
    };

    struct Vec2
    {
        float x,y;
        Vec2()=delete;
        Vec2(int mx,int my):x(mx),y(my){}
        Vec2& operator+(const Vec2& other)
        {
            this->x = this->x + other.x;
            this->y = this->y + other.y;
            return *this;
        }
    };
    
    class Student
    {
    private:
    Season m_season=Season::WINTER;
    public:
        Student()=default;
        Student(Season s):m_season(s){}
        ~Student(){}
    };
    
}

#endif

```


## :two: template头文件

---

**classes**、**functions**和**variables**都可以被模板化。模板是带有泛参数的一段代码,当参数被具体化时,它会变成确定的**class**、**function**或者是 **variable**。参数可以是类型、值或者它们本身。一个广为人知的模板是 **std::vector**,当参数具体化时,它就会成为一个确定的容器。



### 理论 + 实践

#### Basic Class Template

最常见的是类模板是在编译期间将模板参数替代为数据类型,使代码复用。当类被声明时,用户将指定确定的数据类型。

```C++
template <typename T>
class BankUser
{
private:
    T m_Amount; 
public: 
    BankUser()=default;
    BankUser(int val):m_Amount(val){};
    ~BankUser(){}
    T& Deposit(const T& partialAmount) const;
};

template <typename T>
T& BankUser<T>::Deposit(const T& partialAmount)const
{
    m_Amount+=partialAmount;
    return m_Amount;
}
```

#### Function Template

模板应用在函数上也具有同样的效果。

```C++

template <typename T>
T& add(const T& a,const T& b)
{
    return a + b;
}

template <typename T>
T& reduce(const T& a,const T& b)
{
    return a - b;
}

template <typename T>
T& multi(const T& a,const T& b)
{
    return a * b;
}

template <typename T>
T& remove(const T& a,const T& b)
{
    return a / (b + 1e-5);
}

template <typename T1, typename T2>
struct HYPair
{
    T1 first;
    T2 second;
};

template <typename T1, typename T2>
HYPair<T1, T2> make_HYPair(T1 t1, T2 t2)
{
    return HYPair<T1, T2>{t1, t2};
}


```

#### Variadic template data structures

C++11的新特性--可变模版参数（variadic templates）是C++11新增的最强大的特性之一，它对参数进行了高度泛化，它能表示0到任意个数、任意类型的参数。相比C++98/03，类模版和函数模版中只能含固定数量的模版参数，可变模版参数无疑是一个巨大的改进。然而由于可变模版参数比较抽象，使用起来需要一定的技巧，所以它也是C++11中最难理解和掌握的特性之一。虽然掌握可变模版参数有一定难度，但是它却是C++11中最有意思的一个特性。


##### 可变模板参数定义

可变参数模板和普通模板的语义是一样的，只是写法上稍有区别，声明可变参数模板时需要在**typename**或**class**后面带上省略号“...”。

```C++

template <class... T>
void f(T... args);

```

上面可变模板参数的定义中,省略号的作用有两个:

1、声明一个参数包 **T... args**,这个参数包可以包含0到任意个模板参数;

2、在模板定义的右边,可以将参数包展开成一个一个独立的参数。

上面的参数args前面有省略号，所以它就是一个可变模版参数，我们把带省略号的参数称为“参数包”，它里面包含了0到N（N>=0）个模版参数。我们无法直接获取参数包args中的每个参数的，只能通过展开参数包的方式来获取参数包中的每个参数，这是使用可变模版参数的一个主要特点，也是最大的难点，即如何展开可变模版参数。

##### 可变模板参数函数

```C++

#include <iostream>
template<class... T>
void f(T... args)
{
    // 打印变参的个数
    std::cout << sizeof...(args) << std::endl;
}

f();        //0
f(1, 2);    //2
f(1, 2.5, "");    //3

```
这个例子只是简单的将可变模版参数的个数打印出来,如果我们需要将参数包中的每个参数打印出来的话就需要通过一些方法了。

展开可变模版参数函数的方法一般有两种：一种是**通过递归函数来展开参数包**，另外一种是**通过逗号表达式来展开参数包**。下面来看看如何用这两种方法来展开参数包。

###### 递归函数方式展开参数包

```C++

#include <iostream>
using namespace std;
//递归终止函数
void print()
{
   cout << "empty" << endl;
}
//展开函数
template <class T, class ... Args>
void print(T head, Args... rest)
{
   cout << "parameter " << head << endl;
   print(rest...);
}

// 或者
template <class T>
void print(T t)
{
   cout <<"parameter" << t << endl;
}
template <class T, class ... Args>
void print(T head, Args... rest)
{
   cout << "parameter " << head << endl;
   print<T>(rest...);
}



int main(void)
{
   print(1,2,3,4);
   return 0;
}

```

上例会输出每一个参数，直到为空时输出empty。展开参数包的函数有两个，一个是递归函数，另外一个是递归终止函数，参数包Args...在展开的过程中递归调用自己，每调用一次参数包中的参数就会少一个，直到所有的参数都展开为止，当没有参数时，则调用非模板函数print终止递归过程。

<div align=center>
<img src="../assets/chapter4-1.png">
</div>

上面的递归终止函数还可以写成这样，当参数包展开到最后一个参数时递归为止。


```C++

template<typename T>
T sum(T t)
{
    return t;
}
template<typename T, typename ... Types>
T sum (T first, Types ... rest)
{
    return first + sum<T>(rest...);
}

sum(1,2,3,4); //10

```

###### 逗号表达式展开参数包

递归函数展开参数包是一种标准做法，也比较好理解，但也有一个缺点，就是必须要一个重载的递归终止函数，即必须要有一个同名的终止函数来终止递归，这样可能会感觉稍有不便。有没有一种更简单的方式呢？其实还有一种方法可以不通过递归方式来展开参数包，这种方式需要借助逗号表达式和初始化列表。比如前面print的例子可以改成这样：

```C++

template <class T>
void printarg(T t)
{
   cout << t << endl;
}

template <class ...Args>
void expand(Args... args)
{
   int arr[] = {(printarg(args), 0)...};
}

expand(1,2,3,4);

```

这个例子将分别打印出1,2,3,4四个数字。这种展开参数包的方式，不需要通过递归终止函数，是直接在expand函数体中展开的。**printarg**不是一个递归终止函数，只是一个处理参数包中每一个参数的函数。这种就地展开参数包的方式实现的关键是逗号表达式。我们知道逗号表达式会按顺序执行逗号前面的表达式，比如：

```C++

d = (a = b, c); 

```


这个表达式会按顺序执行：b会先赋值给a，接着括号中的逗号表达式返回c的值，因此d将等于c。

**expand**函数中的逗号表达式: **(printarg(args), 0)**，也是按照这个执行顺序，先执行**printarg(args)**,再得到逗号表达式的结果0。

同时还用到了C++11的另外一个特性——初始化列表，通过初始化列表来初始化一个变长数组, **{(printarg(args), 0)...}** 将会展开成<strong>((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0), etc... )</strong>,最终会创建一个元素值都为0的数组**int arr[sizeof...(Args)]**。由于是逗号表达式，在创建数组的过程中会先执行逗号表达式前面的部分**printarg(args)** 打印出参数，也就是说在构造int数组的过程中就将参数包展开了，这个数组的目的纯粹是为了在数组构造的过程展开参数包。

##### 可变模板参数类

可变参数模板类是一个带可变模板参数的模板类，比如C++11中的元祖std::tuple就是一个可变模板类，它的定义如下:

```C++

template< class... Types >
class tuple;

```

这个可变参数模板类可以携带任意类型任意个数的模板参数:

```C++

std::tuple<> tp;        //可变参数模板的模板参数个数可以为0个，所以该定义也是合法的：
std::tuple<int> tp1 = std::make_tuple(1);
std::tuple<int, double> tp2 = std::make_tuple(1, 2.5);
std::tuple<int, double, string> tp3 = std::make_tuple(1, 2.5, "");

```

可变参数模板类的参数包展开的方式和可变参数模板函数的展开方式不同，可变参数模板类的参数包展开需要**通过模板特化**和**继承**方式去展开，展开方式比可变参数模板函数要复杂。


###### 模版偏特化和递归方式来展开参数包


可变参数模板类的展开一般需要定义两到三个类，包括类声明和偏特化的模板类。如下方式定义了一个基本的可变参数模板类,作用是在编译期计算出参数包中参数类型的size之和:


```C++

// 前向声明
template<typename... Args>
struct SumSizeOf;

template<typename First,typename ...Rest>
struct SumSizeOf<First, Rest...>
{
	enum { value = SumSizeOf<First>::value +  SumSizeOf<Rest...>::value, };
};

// 展开到0时
template<>struct SumSizeOf<> { enum { value = 0, }; };

template<typename Last>
struct SumSizeOf<Last>
{
	enum {
		value = sizeof(Last),
	};
};
// 改进 version 1
template<typename First,typename Last>
struct SumSizeOf<First, Last>
{
	enum {value = sizeof(First) + sizeof(Last),};
};




// 可以使用std::integral_constant来消除枚举定义value。利用std::integral_constant可以获得编译期常量的特性
template<typename First, typename... Args>
struct SumSizeOf;


//基本定义
template<typename First, typename... Rest>
struct SumSizeOf<First, Rest...> : std::integral_constant<int, SumSizeOf<First>::value + SumSizeOf<Rest...>::value>
{
};

//递归终止
template<typename Last>
struct SumSizeOf<Last> : std::integral_constant<int, sizeof(Last)>
{
};



```


###### 继承

```C++

//整型序列的定义
template<int...>
struct IndexSeq{};

//继承方式，开始展开参数包
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

// 模板特化，终止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};

int main()
{
    using T = MakeIndexes<3>::type;
    cout <<typeid(T).name() << endl;
    return 0;
}

```

其中MakeIndexes的作用是为了生成一个可变参数模板类的整数序列，最终输出的类型是：struct IndexSeq<0,1,2>。MakeIndexes继承于自身的一个特化的模板类，这个特化的模板类同时也在展开参数包，这个展开过程是通过继承发起的，直到遇到特化的终止条件展开过程才结束。


如果不希望通过继承方式去生成整形序列，则可以通过下面的方式生成：

```C++

template<int N, int... Indexes>
struct MakeIndexes3
{
    using type = typename MakeIndexes3<N - 1, N - 1, Indexes...>::type;
};

template<int... Indexes>
struct MakeIndexes3<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};

```



参考:
0、https://www.cnblogs.com/qicosmos/p/4325949.html
 
1、https://www.helloworld.net/p/7580029278

2、https://mocuishle0.github.io/post/c11-xin-te-zheng-ke-bian-can-shu-mo-ban-variadic-template/

3、typename 和 class 区别:https://liam.page/2018/03/16/keywords-typename-and-class-in-Cxx/

4、https://juejin.cn/post/7025304532636663845

5、https://www.programminghunter.com/article/7407329494/

6、https://sg-first.gitbooks.io/cpp-template-tutorial/content/jie_te_hua_yu_pian_te_hua.html

#### Alias template

```C++
// 基本用法
template<typename T> using pointer = T*;

pointer<int> p = new int; // int* p = new int;

// 改进

template<typename T>
struct nonconst_pointer_helper {typedef T* type;};

template<typename T>
struct nonconst_pointer_helper<T const> {typedef T* type;};

template<typename T> using nonconst_pointer = nonconst_pointer_helper<T>::type;


```


#### Explicit instantiation

1、这里会涉及到一个问题:为什么模板仅仅在头文件中实现?

答案:为了防止出现链接异常。参考:https://blog.csdn.net/imred/article/details/80261632


```C++

#ifndef _FOO_H_
#define _FOO_H_
template<class T> void foo(T x)
{
}
#endif

// foo.cpp
template void foo(int);
template void foo(double);

// main.cpp
extern template void foo(double);

int main()
{
    foo(42);
    foo(3.21);
    return 0;
}

```

## :three: cc文件调用

---

