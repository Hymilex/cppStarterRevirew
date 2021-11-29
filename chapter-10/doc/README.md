
# C++ 的const、constexpr

<h2>
目录
</h2>

- [C++ 的const、constexpr](#c-的constconstexpr)
  - [:one: constexpr](#one-constexpr)
    - [用法](#用法)
    - [限制](#限制)
      - [对于变量](#对于变量)
      - [对于函数](#对于函数)
    - [优点](#优点)
    - [const和constexpr区别](#const和constexpr区别)
      - [共同点](#共同点)
      - [不同点](#不同点)
    - [static 和 const 结合使用](#static-和-const-结合使用)
    - [const 和 define 区别](#const-和-define-区别)
  - [:two: const](#two-const)

## :one: constexpr 


### 用法

即可修饰变量又可以是函数。

constexpr是C++11中新增的关键字，其语义是“常量表达式”，也就是在编译期可求值的表达式。最基础的常量表达式就是字面值或全局变量/函数的地址或sizeof等关键字返回的结果，而其它常量表达式都是由基础表达式通过各种确定的运算得到的。constexpr值可用于enum、switch、数组长度等场合。

constexpr所修饰的变量一定是编译期可求值的，所修饰的函数在其所有参数都是constexpr时，一定会返回constexpr。

constexpr还能用于修饰类的构造函数，即保证如果提供给该构造函数的参数都是constexpr，那么产生的对象中的所有成员都会是constexpr，该对象也就是constexpr对象了，可用于各种只能使用constexpr的场合。注意，constexpr构造函数必须有一个空的函数体，即所有成员变量的初始化都放到初始化列表中。



### 限制

#### 对于变量

要求其赋值必须是常量表达式，即在编译期间由编译器计算结果并赋值。因为是常量所以不能在声明后再赋值，必须是在声明的同时初始化，否则会编译错误。

#### 对于函数

如果其传入的参数可以在编译时期计算出来，那么这个函数就会产生编译时期的值，在函数被调用的地方替换成这个值。

但是，如果传入的参数如果不能在编译时期计算出来，那么constexpr修饰的函数就和普通函数一样,只能在运行时确定结果。

不过，这样子并不会有什么问题产生，我们不必因此而写两个版本，所以如果函数体适用于constexpr函数的条件，可以尽量加上constexpr。


### 优点

把运行时的工作部分计算工作交给了编译器来解决，提高了运行时的效率。

```C++

//变量的使用
constexpr int a=3;    //接下来使用a的时候，a就是const int类型
const int* num =&a;   //所以当声明一个a的指针的时候，也要用const int
constexpr int b;   //Error：default initialization，不能缺省初始化值
-----------------------------------------------------------------------------
//函数的使用
constexpr int addNum(int a,int b)  
{
    return a+b;
}

int main()
{
    int a,b;
    cin>>a>>b;  //这样子使用，在编译器无法得到其值，因为a、b是运行时确定的数值
    cout<<addNum(a,b)<<endl;  //正常输出，没有问题
    int c=3,d=4;    //c、d编译时期已经有值
    cout<<addNum(c,d)<<endl;  //编译时期就计算出了addNum(c,d)的值
}


```


###  const和constexpr区别

#### 共同点

两者都必须在声明的同时赋值，即初始化。

#### 不同点


constexpr：必须初始化为一个能确定地址的变量/常量值，比如全局变量、static局部变量。（这两者都处于静态存储区，属于静态分配：在程序编译期间分配固定的存储空间）


const：没有限制一定要明确地址。所以const必须赋值，但不一定要是确定的值。

```C++

int n;
cin>>n;

constexpr int i=1; //正确
constexpr int i=n; //error,在编译期间，n不是一个确定的值

const int j=n;  //正确
const int j； //error，必须初始化

```

实际上，const只是规定了不能改变值，即read-only，const常用于不需要改变值的访问。constexpr才是真正英文里的"const"，即常量的意思。

const可能在编译期得出结果，也可能在运行期。但是constexpr的变量一定要在编译期得到结果。所以constexpr可以用来定义数组大小，但是const不可以。


假如你将一个成员函数标记为constexpr，则顺带也将它标记为了const。如果你将一个变量标记为constexpr，则同样它是const的。但相反并不成立，一个const的变量或函数，并不是constexpr的。
语义上:
constexpr:告诉编译器我可以是编译期间可知的，尽情的优化我吧。
const:告诉程序员没人动得了我，放心的把我传出去；或者放心的把变量交给我，我啥也不动就瞅瞅。
语法上:
constexpr是一种比const 更严格的束缚, 它修饰的表达式本身在编译期间可知, 并且编译器会尽可能的 evaluate at compile time。

 在constexpr 出现之前, 可以在编译期初始化的const都是implicit constexpr. 直到c++ 11, constexpr才从const中细分出来成为一个关键字, 而 const从1983年 c++ 刚改名的时候就存在了... 如果你初学c++, 应当尽可能的, 合理的使用constexpr来帮助编译器优化代码。


参考:
1、https://juejin.cn/post/6844904149679603726


### static 和 const 结合使用

```C++

class Node{
    static int node_count; // 宣告式 (声明式)
};

int Node::node_count = 1; // 定义式

```

如果想要在类内或者结构体内初始化static成员,那么static成员类型必须是带有const修饰词的泛整型(或者列型)、或者是带有constexpr修饰词的字面常数型,而且初始值必须是常数运算式:

```C++

class Curious{
    public:
        static const int c1 = 7; // ok
        static int c2=11; //错误,类的静态成员不应该在类的内部初始化
        const int c3 = 12; // ok但不是静态成员
        static const int c4= sqrt(9); //错误,in-class初始列不是常数表达式
        static const float c5=7.f;//错误:此处不是泛整数类别,需要使用constexpr
};


template <>
struct FixedPointRawTypeTraits<std::int32_t> {
    typedef std::int32_t ScalarRawType;
    static constexpr int kLanes = 1;
};

template <>
struct FixedPointRawTypeTraits<std::int16_t> {
    typedef std::int16_t ScalarRawType;
    static constexpr int kLanes = 1;
};


```


const成员函数主要目的是防止成员函数修改对象的内容。即const成员函数不能修改成员变量的值，但可以访问成员变量。当方法成员函数时，该函数只能是const成员函数。

static成员函数主要目的是作为类作用域的全局函数。不能访问类的非静态数据成员。类的静态成员函数没有this指针，这导致：1、不能直接存取类的非静态成员变量，调用非静态成员函数2、不能被声明为virtual。


### const 和 define 区别

const 是由编译器进行处理，执行类型检查和作用域的检查；

define 是由预处理器进行处理，只做简单的文本替换工作而已。

参考:
1、https://www.youtube.com/watch?v=Dpob2KsYLWs

## :two: const

```C++

void const_test()
{
	const int * a = new int; // 无法改变指针地址所对应的值
	int const * b = new int; // 无法改变指针地址所对应的值
	int* const c = new int; // 无法改变指针指向的地址
}
class EntityConst
{
private:
	int m_X, m_Y;
	int* variable = new int[] {1,2};
public:
	int GetX() const
	{
		return m_X;
	}
	void SetX(int x)
	{
		m_X = x;
	}
	const int* const GetVaribale() const
	{
		return variable;
	}
};

void PrintConst(const EntityConst& entity)
{
	LOGMSG(entity.GetX());
}
void PrintConstTest(const EntityConst* entity)
{
	entity = nullptr;
}

```