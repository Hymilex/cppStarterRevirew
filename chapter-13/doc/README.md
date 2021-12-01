# C++ 中的implicit和explicit

<h2>
目录
</h2>



## :one: 简介

---

在编程过程中， 我们习惯上使用explicit或者implicit关键字实现构造函数的**显式**或者**隐式**显示。


explicit关键字：

只能修饰只有一个参数的构造函数，或者有多个参数，但是除第一个参数外其他的参数都有默认值。它的作用是表明构造函数是显式方式显示的。

implicit关键字:

与explicit对应，他表示隐式的进行数据转换。注：<strong>C++中不存在这个关键字，C#等编程语言中才有，此处仅仅是为了说明</strong>。


## :two: 作用

首先看一下以下代码:

```C++

class CxString  // 没有使用explicit关键字的类声明, 即默认为隐式声明  
{  
public:  
    char *_pstr;  
    int _size;  
    CxString(int size)  
    {  
        _size = size;                // string的预设大小  
        _pstr = malloc(size + 1);    // 分配string的内存  
        memset(_pstr, 0, size + 1);  
    }  
    CxString(const char *p)  
    {  
        int size = strlen(p);  
        _pstr = malloc(size + 1);    // 分配string的内存  
        strcpy(_pstr, p);            // 复制字符串  
        _size = strlen(_pstr);  
    }  
    // 析构函数这里不讨论, 省略...  
};  

    // 下面是调用:

    CxString string1(24);     // 这样是可以的, 为CxString预分配24字节的大小的内存  
    CxString string2 = 10;    // 这样是可以的, 为CxString预分配10字节的大小的内存  
    CxString string3;         // 这样是不行的, 因为没有默认构造函数, 错误为: “CxString”: 没有合适的默认构造函数可用  
    CxString string4("aaaa"); // 这样是可以的  
    CxString string5 = "bbb"; // 这样也是可以的, 调用的是CxString(const char *p)  
    CxString string6 = 'c';   // 这样也是可以的, 其实调用的是CxString(int size), 且size等于'c'的ascii码  
    string1 = 2;              // 这样也是可以的, 为CxString预分配2字节的大小的内存  
    string2 = 3;              // 这样也是可以的, 为CxString预分配3字节的大小的内存  
    string3 = string1;        // 这样也是可以的, 但是只是编译没问题, 如果析构函数里用free释放_pstr内存指针的时候可能会报错, 完整的代码必须重载运算符"=", 并在其中处理内存释放

```

上述代码的疑惑点就是: **CXString string2=10**,这句话为什么成立呢?这就是c++中,在编译时,会存在一个缺省的转换操作:

<strong>将该构造函数对应数据类型的数据转换为该类对象。也就是说 “CxString string2 = 10;” 这段代码, 编译器自动将整型转换为CxString类对象, 实际上等同于下面的操作:</strong>

```C++

CxString string2(10);  
或  
CxString temp(10);  
CxString string2 = temp; 

```

但是, 上面的代码中的_size代表的是字符串内存分配的大小，那么调用的第二句 “CxString string2 = 10;” 和第六句 “CxString string6 = ‘c’;” 就显得不伦不类，而且容易让人疑惑，可读性太低。



有什么办法阻止这种用法呢? 答案就是使用explicit关键字。

```C++

class CxString  // 使用关键字explicit的类声明, 显示转换  
{  
public:  
    char *_pstr;  
    int _size;  
    explicit CxString(int size)  
    {  
        _size = size;  
        // 代码同上, 省略...  
    }  
    CxString(const char *p)  
    {  
        // 代码同上, 省略...  
    }  
};  

    // 下面是调用:  

    CxString string1(24);     // 这样是可以的  
    CxString string2 = 10;    // 这样是不行的, 因为explicit关键字取消了隐式转换  
    CxString string3;         // 这样是不行的, 因为没有默认构造函数  
    CxString string4("aaaa"); // 这样是可以的  
    CxString string5 = "bbb"; // 这样也是可以的, 调用的是CxString(const char *p)  
    CxString string6 = 'c';   // 这样是不行的, 其实调用的是CxString(int size), 且size等于'c'的ascii码, 但explicit关键字取消了隐式转换  
    string1 = 2;              // 这样也是不行的, 因为取消了隐式转换  
    string2 = 3;              // 这样也是不行的, 因为取消了隐式转换  
    string3 = string1;        // 这样也是不行的, 因为取消了隐式转换, 除非类实现操作符"="的重载  

```

上面说过，explicit关键字只对有一个参数的类构造函数有效，如果类构造函数参数大于或等于两个时，是不会产生隐式转换的，所以explicit关键字也就无效了。

但是有一个例外，当除了第一个参数以外的其他参数都有默认值的时候，explicit关键字依然有效，此时，当调用构造函数时只传入一个参数，等效于只有一个参数的类构造函数。


```C++


class CxString  // 使用关键字explicit声明  
{  
public:  
    int _age;  
    int _size;  
    explicit CxString(int age, int size = 0)  
    {  
        _age = age;  
        _size = size;  
        // 代码同上, 省略...  
    }  
    CxString(const char *p)  
    {  
        // 代码同上, 省略...  
    }  
};  

    // 下面是调用:  

    CxString string1(24);     // 这样是可以的  
    CxString string2 = 10;    // 这样是不行的, 因为explicit关键字取消了隐式转换  
    CxString string3;         // 这样是不行的, 因为没有默认构造函数  
    string1 = 2;              // 这样也是不行的, 因为取消了隐式转换  
    string2 = 3;              // 这样也是不行的, 因为取消了隐式转换  
    string3 = string1;        // 这样也是不行的, 因为取消了隐式转换, 除非类实现操作符"="的重载  


```


总结:

(1)explicit关键字只需用于类内的单参数构造函数前面。由于无参数的构造函数和多参数的构造函数总是显示调用，这种情况在构造函数前加explicit无意义。

(2)如果想禁止类A对象被隐式转换为类B对象，可在类B中使用关键字explicit。

```C++

struct ViewBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_offset(int32_t offset) {
    fbb_.AddElement<int32_t>(View::VT_OFFSET, offset, 0);
  }
  void add_stride(flatbuffers::Offset<flatbuffers::Vector<int32_t>> stride) {
    fbb_.AddOffset(View::VT_STRIDE, stride);
  }
  explicit ViewBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ViewBuilder &operator=(const ViewBuilder &);
  flatbuffers::Offset<View> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<View>(end);
    return o;
  }
};

```