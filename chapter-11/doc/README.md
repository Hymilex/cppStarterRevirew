# C++ 中的类成员初始化

<h2>
目录
</h2>

- [C++ 中的类成员初始化](#c-中的类成员初始化)
  - [:one: 初始化赋值](#one-初始化赋值)
  - [:two: default](#two-default)
  - [:three: delete](#three-delete)

## :one: 初始化赋值

---


```C++

class Animal
{
public:
	Animal() {}
	Animal(std::string name,uint32_t age,int16_t sex) :m_name(name), m_age(age), m_sex(sex) {}
	~Animal() {}

private:
	std::string m_name;
	uint32_t m_age;
	int16_t m_sex;
};


```


## :two: default

---

手动编写构造函数存在两个问题:

1. 程序员工作量变大 
2. 没有编译器自动生成的默认特殊构造函数效率高。


场景一:

default 函数特性仅用于类的特殊成员函数，且该特殊成员函数没有默认参数。、

既可以在类体里定义(inline),也可以在类体外(out-of-line)定义。

```C++

class X {
public:
    int f() = default: //错误， f()非特殊成员函数
    X(int) = default; //错误， 非特殊成员函数
    X(int i = 1) = default; // 错误， 含有默认参数
}
//能够支持default的，都是编译器能够在该情形下明确要做什么（构造函数一般是逐bit拷贝）


class X {
public:
    X() = default; // inline
    X(const X&); // 
    X& operator = (const X&);
    ~X() = default; // inline
}

X::X(const X&) = default; // out of line
X& X::operator = (const X&) = default; // out of line



#ifndef NonCopyable_hpp
#define NonCopyable_hpp

namespace MNN {
/** protocol class. used to delete assignment operator. */
class NonCopyable {
public:
    NonCopyable()                    = default;
    NonCopyable(const NonCopyable&)  = delete;
    NonCopyable(const NonCopyable&&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&&) = delete;
};
} // namespace MNN

#endif /* NonCopyable_hpp */


```

场景二:

虚析构函数中default的使用,大多存在多层继承:

```C++

// 虚析构函数
#ifndef MNN_COREMLPOOL_HPP
#define MNN_COREMLPOOL_HPP

#include "CoreMLCommonExecution.hpp"
#include "CoreMLBackend.hpp"

namespace MNN {

class CoreMLPool : public CoreMLCommonExecution {
public:
    CoreMLPool(Backend *b, const Op *op, const std::vector<Tensor *> &inputs, const std::vector<Tensor *> &outputs);
    ErrorCode onResize(const std::vector<Tensor *> &inputs, const std::vector<Tensor *> &outputs);
    virtual ~CoreMLPool() = default;
};
} // namespace MNN

#endif // MNN_COREMLPOOL_HPP


// 非虚析构函数
template <class T>
class CUDACreatorRegister {
public:
    CUDACreatorRegister(OpType type) {
        T *t = new T;
        CUDABackend::addCreator(type, t);
    }
    ~CUDACreatorRegister() = default;
};

```



## :three: delete

---

1、为了能够让程序员显式的禁用某个函数，C++11 标准引入了一个新特性："=delete"函数。程序员只需在函数声明后上“=delete;”，就可将该函数禁用。

2、"=delete"函数特性还可以用来禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象。

```C++

class Dog {
public:
	Dog() {}
	Dog(const char* name) = delete;
	Dog(const Dog&) = delete;  // 1-1 声明拷贝构造函数为 deleted 函数
	Dog& operator=(const Dog &) = delete; // 1-2 声明拷贝赋值操作符为 deleted 函数
	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
private:

};

void delete_test()
{
	Dog d1;
	Dog d2 = d1; // 尝试引用已经删除的函数
	Dog* d3 = new Dog; // 使用了未定义类型
	Dog* d4 = new Dog[10]; // 使用了未定义类型
	const char* name = "harry";
	Dog d5(name);

}



template <typename T>
class TopContainer {
public:
    TopContainer() = delete;
    TopContainer(int32_t k, int32_t rowSize) : mK(k) {
        mContainer.reserve(std::min(k, rowSize) + 1);
    }

    void startCollecting(const T* values) {
        mValues = values;
        mContainer.clear();
    }
    void push(int32_t a) {
        auto comparator = [this](int32_t a, int32_t b) { return compareFunc(a, b); };
        if (mContainer.size() <= mK) {
            mContainer.push_back(a);
            if (mContainer.size() == mK + 1) {
                std::make_heap(mContainer.begin(), mContainer.end(), comparator);
                std::pop_heap(mContainer.begin(), mContainer.end(), comparator);
            }
        } else if (comparator(a, mContainer.front())) {
            mContainer.back() = a;
            std::push_heap(mContainer.begin(), mContainer.end(), comparator);
            std::pop_heap(mContainer.begin(), mContainer.end(), comparator);
        }
    }

    const std::vector<int32_t>& sortedResult() {
        auto comparator = [this](int32_t a, int32_t b) { return compareFunc(a, b); };
        if (mContainer.size() <= mK) {
            std::sort(mContainer.begin(), mContainer.end(), comparator);
        } else {
            std::sort_heap(mContainer.begin(), mContainer.end() - 1, comparator);
            mContainer.resize(mK);
        }
        return mContainer;
    }

private:
    int32_t mK;
    std::vector<int32_t> mContainer;
    const T* mValues = nullptr;

    bool compareFunc(int32_t a, int32_t b) const {
        if (mValues[b] < mValues[a]) {
            return true;
        } else if (mValues[b] > mValues[a]) {
            return false;
        } else {
            return a < b;
        }
    }
};


```