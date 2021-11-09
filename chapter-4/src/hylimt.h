#ifndef HYLIMT_H_
#define HYLIMT_H_

#include <iostream>
#include <string>

// 常见类模板
// ================================================
template <typename T>
class BankUser
{
private:
    T m_Amount;

public:
    BankUser() = default;
    BankUser(int val) : m_Amount(val){};
    ~BankUser() {}
    T &Deposit(const T &partialAmount) const;
};

template <typename T>
T &BankUser<T>::Deposit(const T &partialAmount) const
{
    m_Amount += partialAmount;
    return m_Amount;
}
// ================================================

// 常见函数模板
// ================================================

template <typename T>
T &add(const T &a, const T &b)
{
    return a + b;
}

template <typename T>
T &reduce(const T &a, const T &b)
{
    return a - b;
}

template <typename T>
T &multi(const T &a, const T &b)
{
    return a * b;
}

template <typename T>
T &remove(const T &a, const T &b)
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

// ================================================


// 可变参数模板
// ================================================

template<typename ... T>
struct FreeData
{
};


template<size_t idx,typename T>
struct GetHelper;

template<typename ... T>
struct HYTuple
{
    HYTuple()=delete;
};

template<typename T,typename ... Rest>
struct HYTuple
{
    HYTuple(const T& first,const Rest& ... rest):m_First(first),m_Rest(rest...){}

    T m_First;
    HYTuple<Rest ...> m_Rest;

    template<size_t idx>
    auto get()
    {
        return GetHelper<idx,HYTuple<T,Rest...>>::get(*this);
    }
};

template<typename T,typename ... Rest>
struct GetHelper<0,HYTuple<T,Rest ...>>
{
    static T get(HYTuple<T,Rest ...>& data)
    {
        return data.m_First;
    }    
};

template<size_t idx,typename T,typename ... Rest>
struct GetHelper<idx,HYTuple<T,Rest ...>>
{
    static auto get(HYTuple<T,Rest ...>& data)
    {
        return GetHelper<idx-1,HYTuple<Rest ...>>::get(data.m_Rest);
    }
};



// ================================================

//模板函数 template function

// 模板类 template class

#endif