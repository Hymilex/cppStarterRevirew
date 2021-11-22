#include "CPUMatMul.hpp"
#include "Vec.hpp"
#include <limits>
#include <iostream>
#include <iostream>
#include <utility>
#include <functional>

using Vec4 = MNN::Math::Vec<float, 4>;

namespace MNN
{
    CPUMatMul::CPUMatMul(bool transposeA, bool transposeB, bool transposeC, bool multiThread)
    {
    }

    void CPUMatMul::reset()
    {
        int x = 0, y = 1, z = 2;

        //std::vector<std::pair<std::function<void(int, const float*, const float*, const float*)>, int>> mPreFunctions;
        mPreFunctions.emplace_back(std::make_pair([](int tId, const float *APtr, const float *BPtr, const float *Bia) {}, 0));
        
        // &x 按照引用 y 按照值传递 ()括号内时lambda表达式形参
        mPreFunctions.emplace_back(std::make_pair([&x,y](int tId, const float *APtr, const float *BPtr, const float *Bia) {}, 0));

        mPreFunctions.emplace_back(std::make_pair([&](int tId, const float *APtr, const float *BPtr, const float *Bia) {}, 0));

        mPreFunctions.emplace_back(std::make_pair([=](int tId, const float *APtr, const float *BPtr, const float *Bia) {}, 0));
    }
}
