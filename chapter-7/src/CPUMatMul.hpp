//
//  CPUMatMul.hpp
//  MNN
//
//  Created by MNN on 2018/08/06.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#ifndef _CPUMATMUL_HPP
#define _CPUMATMUL_HPP

#include <functional>

namespace MNN {

class CPUMatMul {
public:
    CPUMatMul(bool transposeA, bool transposeB, bool transposeC, bool multiThread);
    
    void reset();
private:
    std::vector<std::pair<std::function<void(int, const float*, const float*, const float*)>, int>> mPreFunctions;
    std::vector<std::pair<std::function<void(int, const float*, const float*, const float*, float*)>, int>> mPostFunctions;
};
} // namespace MNN

#endif // CPUMATMUL_HPP
