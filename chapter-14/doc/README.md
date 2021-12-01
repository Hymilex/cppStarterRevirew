# C++ 操作符和操作符重载


<h2>
目录
</h2>

- [C++ 操作符和操作符重载](#c-操作符和操作符重载)
  - [:one: 常规操作符重载](#one-常规操作符重载)
  - [:two:模板类/结构体操作符重载](#two模板类结构体操作符重载)

## :one: 常规操作符重载

```C++

// 头文件定义宏
#define AI inline

// Allow scalars on the left or right of binary operators, and things like +=, &=, etc.
#define V template <int N, typename T> AI static SkNx<N,T>
    V operator+ (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) +  y; }
    V operator- (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) -  y; }
    V operator* (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) *  y; }
    V operator/ (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) /  y; }
    V operator& (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) &  y; }
    V operator| (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) |  y; }
    V operator^ (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) ^  y; }
    V operator==(T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) == y; }
    V operator!=(T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) != y; }
    V operator<=(T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) <= y; }
    V operator>=(T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) >= y; }
    V operator< (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) <  y; }
    V operator> (T x, const SkNx<N,T>& y) { return SkNx<N,T>(x) >  y; }

    V operator+ (const SkNx<N,T>& x, T y) { return x +  SkNx<N,T>(y); }
    V operator- (const SkNx<N,T>& x, T y) { return x -  SkNx<N,T>(y); }
    V operator* (const SkNx<N,T>& x, T y) { return x *  SkNx<N,T>(y); }
    V operator/ (const SkNx<N,T>& x, T y) { return x /  SkNx<N,T>(y); }
    V operator& (const SkNx<N,T>& x, T y) { return x &  SkNx<N,T>(y); }
    V operator| (const SkNx<N,T>& x, T y) { return x |  SkNx<N,T>(y); }
    V operator^ (const SkNx<N,T>& x, T y) { return x ^  SkNx<N,T>(y); }
    V operator==(const SkNx<N,T>& x, T y) { return x == SkNx<N,T>(y); }
    V operator!=(const SkNx<N,T>& x, T y) { return x != SkNx<N,T>(y); }
    V operator<=(const SkNx<N,T>& x, T y) { return x <= SkNx<N,T>(y); }
    V operator>=(const SkNx<N,T>& x, T y) { return x >= SkNx<N,T>(y); }
    V operator< (const SkNx<N,T>& x, T y) { return x <  SkNx<N,T>(y); }
    V operator> (const SkNx<N,T>& x, T y) { return x >  SkNx<N,T>(y); }

    V& operator<<=(SkNx<N,T>& x, int bits) { return (x = x << bits); }
    V& operator>>=(SkNx<N,T>& x, int bits) { return (x = x >> bits); }

    V& operator +=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x + y); }
    V& operator -=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x - y); }
    V& operator *=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x * y); }
    V& operator /=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x / y); }
    V& operator &=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x & y); }
    V& operator |=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x | y); }
    V& operator ^=(SkNx<N,T>& x, const SkNx<N,T>& y) { return (x = x ^ y); }

    V& operator +=(SkNx<N,T>& x, T y) { return (x = x + SkNx<N,T>(y)); }
    V& operator -=(SkNx<N,T>& x, T y) { return (x = x - SkNx<N,T>(y)); }
    V& operator *=(SkNx<N,T>& x, T y) { return (x = x * SkNx<N,T>(y)); }
    V& operator /=(SkNx<N,T>& x, T y) { return (x = x / SkNx<N,T>(y)); }
    V& operator &=(SkNx<N,T>& x, T y) { return (x = x & SkNx<N,T>(y)); }
    V& operator |=(SkNx<N,T>& x, T y) { return (x = x | SkNx<N,T>(y)); }
    V& operator ^=(SkNx<N,T>& x, T y) { return (x = x ^ SkNx<N,T>(y)); }
#undef V


```

标准流的重载:


```C++

//
//  TRTProfiler.hpp
//  MNN
//
//  Created by MNN on b'2020/08/10'.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#ifndef MNN_TRTProfiler_H
#define MNN_TRTProfiler_H

#include <MNN/MNNDefine.h>
#include <NvInfer.h>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ratio>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace MNN {

struct SimpleProfiler : public nvinfer1::IProfiler{
    struct Record{
        float time{0};
        int count{0};
    };

    virtual void reportLayerTime(const char* layerName, float ms)
    {
        mProfile[layerName].count++;
        mProfile[layerName].time += ms;
        if (std::find(mLayerNames.begin(), mLayerNames.end(), layerName) == mLayerNames.end())
        {
            mLayerNames.push_back(layerName);
        }
    }

    SimpleProfiler(const char* name, const std::vector<SimpleProfiler>& srcProfilers = std::vector<SimpleProfiler>())
        : mName(name)
    {
        for (const auto& srcProfiler : srcProfilers)
        {
            for (const auto& rec : srcProfiler.mProfile)
            {
                auto it = mProfile.find(rec.first);
                if (it == mProfile.end())
                {
                    mProfile.insert(rec);
                }
                else
                {
                    it->second.time += rec.second.time;
                    it->second.count += rec.second.count;
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const SimpleProfiler& value){
        out << "========== " << value.mName << " profile ==========" << std::endl;
        float totalTime = 0;
        std::string layerNameStr = "TensorRT layer name";
        int maxLayerNameLength = std::max(static_cast<int>(layerNameStr.size()), 70);
        for (const auto& elem : value.mProfile)
        {
            totalTime += elem.second.time;
            maxLayerNameLength = std::max(maxLayerNameLength, static_cast<int>(elem.first.size()));
        }

        auto old_settings = out.flags();
        auto old_precision = out.precision();
        // Output header
        {
            out << std::setw(maxLayerNameLength) << layerNameStr << " ";
            out << std::setw(12) << "Runtime, "
                << "%"
                << " ";
            out << std::setw(12) << "Invocations"
                << " ";
            out << std::setw(12) << "Runtime, ms" << std::endl;
        }
        for (size_t i = 0; i < value.mLayerNames.size(); i++)
        {
            const std::string layerName = value.mLayerNames[i];
            auto elem = value.mProfile.at(layerName);
            out << std::setw(maxLayerNameLength) << layerName << " ";
            out << std::setw(12) << std::fixed << std::setprecision(1) << (elem.time * 100.0F / totalTime) << "%"
                << " ";
            out << std::setw(12) << elem.count << " ";
            out << std::setw(12) << std::fixed << std::setprecision(2) << elem.time << std::endl;
        }

        out.flags(old_settings);
        out.precision(old_precision);
        out << "========== " << value.mName << " total runtime = " << totalTime << " ms ==========" << std::endl;

        return out;
    }

private:
    std::string mName;
    std::vector<std::string> mLayerNames;
    std::map<std::string, Record> mProfile;
};

} // namespace MNN

#endif // MNN_TRTProfiler_H

```


## :two:模板类/结构体操作符重载


```C++

template<typename Vec>
struct VecBinaryAdd  {
    Vec operator()(Vec& x, Vec& y) const {
        return x + y;
    }
};

template<typename Vec>
struct VecBinarySub  {
    Vec operator()(Vec& x, Vec& y) const {
        return x - y;
    }
};

template<typename Vec>
struct VecBinaryMul  {
    Vec operator()(Vec& x, Vec& y) const {
        return x * y;
    }
};

template<typename Vec>
struct VecBinaryMin  {
    Vec operator()(Vec& x, Vec& y) const {
        return Vec::min(x, y);
    }
};

template<typename Vec>
struct VecBinaryMax  {
    Vec operator()(Vec& x, Vec& y) const {
        return Vec::max(x, y);
    }
};

template<typename Vec>
struct VecBinarySqd  {
    Vec operator()(Vec& x, Vec& y) const {
        return (x-y)*(x-y);
    }
};


```