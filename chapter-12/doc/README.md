# C++ 三元表达式

<h2>
目录
</h2>


## noexcept

### When use noexcept?

- 每个函数都考虑noexcept会很麻烦，所以只在明显的时候使用
- 现在编译器在好路径上异常没有影响，noexcept可能的作用是减小体积
- 推荐在构造、复制等常用操作标记noexcept，这样性能提升可能会比较大。例如vector不会使用你的类move操作，除非它被标记为noexcept（有的编译器能自动推导）
- noexcept主要是给使用者看的，对编译器影响不大


我不建议业务代码使用noexcept。原因如下：

- noexcept只是一个优化相关的东西，不用不影响代码的正确性
- 通常情况下，在广泛使用STL容器，智能指针的现代C++风格下，编译器能够推导自动生成的析构函数，move构造和赋值运算符的noexcept属性
- noexcept判断比较复杂，业务代码程序员更关注业务逻辑本身，而且需求变化大，代码可能很复杂，人工判断很容易出错
- noexcept会影响接口的灵活性，比如基类某个虚函数设置为noexcept，派生类覆盖虚函数时也必须遵守，这个有些情况下难以保证
- noexcept用错了危害很大，会强行调std::terminate，本来能处理的都没有处理机会了就像异常规格的存在版本问题一样，如果一个函数从noexcept变为noexcept(false)，调用处可能也需要跟着改动
- C++17后，noexcept还影响了函数的签名，进一步影响了代码的复杂性和兼容性

```C++
#if (defined(__GXX_EXPERIMENTAL_CXX0X__) && (__GNUC__ * 100 + __GNUC_MINOR__ >= 406)) || \
    (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 190023026)) || \
    defined(__clang__)
  #define FLATBUFFERS_NOEXCEPT noexcept
#else
  #define FLATBUFFERS_NOEXCEPT
#endif

struct ParameterUnion {
  Parameter type;
  void *value;

  ParameterUnion() : type(Parameter_NONE), value(nullptr) {}
  ParameterUnion(ParameterUnion&& u) FLATBUFFERS_NOEXCEPT :
    type(Parameter_NONE), value(nullptr)
    { std::swap(type, u.type); std::swap(value, u.value); }
  ParameterUnion(const ParameterUnion &) FLATBUFFERS_NOEXCEPT;
  ParameterUnion &operator=(const ParameterUnion &u) FLATBUFFERS_NOEXCEPT
    { ParameterUnion t(u); std::swap(type, t.type); std::swap(value, t.value); return *this; }
  ParameterUnion &operator=(ParameterUnion &&u) FLATBUFFERS_NOEXCEPT
    { std::swap(type, u.type); std::swap(value, u.value); return *this; }
  ~ParameterUnion() { Reset(); }

  void Reset();

#ifndef FLATBUFFERS_CPP98_STL
  template <typename T>
  void Set(T&& val) {
    Reset();
    type = ParameterTraits<typename T::TableType>::enum_value;
    if (type != Parameter_NONE) {
      value = new T(std::forward<T>(val));
    }
  }
#endif  // FLATBUFFERS_CPP98_STL

  static void *UnPack(const void *obj, Parameter type, const flatbuffers::resolver_function_t *resolver);
  flatbuffers::Offset<void> Pack(flatbuffers::FlatBufferBuilder &_fbb, const flatbuffers::rehasher_function_t *_rehasher = nullptr) const;

  RasterInfoT *AsRasterInfo() {
    return type == Parameter_RasterInfo ?
      reinterpret_cast<RasterInfoT *>(value) : nullptr;
  }
  const RasterInfoT *AsRasterInfo() const {
    return type == Parameter_RasterInfo ?
      reinterpret_cast<const RasterInfoT *>(value) : nullptr;
  }
  BroadCastInfoT *AsBroadCastInfo() {
    return type == Parameter_BroadCastInfo ?
      reinterpret_cast<BroadCastInfoT *>(value) : nullptr;
  }
  const BroadCastInfoT *AsBroadCastInfo() const {
    return type == Parameter_BroadCastInfo ?
      reinterpret_cast<const BroadCastInfoT *>(value) : nullptr;
  }
  ScatterNdInfoT *AsScatterNdInfo() {
    return type == Parameter_ScatterNdInfo ?
      reinterpret_cast<ScatterNdInfoT *>(value) : nullptr;
  }
  const ScatterNdInfoT *AsScatterNdInfo() const {
    return type == Parameter_ScatterNdInfo ?
      reinterpret_cast<const ScatterNdInfoT *>(value) : nullptr;
  }
  InterpInfoT *AsInterpInfo() {
    return type == Parameter_InterpInfo ?
      reinterpret_cast<InterpInfoT *>(value) : nullptr;
  }
  const InterpInfoT *AsInterpInfo() const {
    return type == Parameter_InterpInfo ?
      reinterpret_cast<const InterpInfoT *>(value) : nullptr;
  }
  GatherInfoT *AsGatherInfo() {
    return type == Parameter_GatherInfo ?
      reinterpret_cast<GatherInfoT *>(value) : nullptr;
  }
  const GatherInfoT *AsGatherInfo() const {
    return type == Parameter_GatherInfo ?
      reinterpret_cast<const GatherInfoT *>(value) : nullptr;
  }
  DetectionPostProcessInfoT *AsDetectionPostProcessInfo() {
    return type == Parameter_DetectionPostProcessInfo ?
      reinterpret_cast<DetectionPostProcessInfoT *>(value) : nullptr;
  }
  const DetectionPostProcessInfoT *AsDetectionPostProcessInfo() const {
    return type == Parameter_DetectionPostProcessInfo ?
      reinterpret_cast<const DetectionPostProcessInfoT *>(value) : nullptr;
  }
  OneHotInfoT *AsOneHotInfo() {
    return type == Parameter_OneHotInfo ?
      reinterpret_cast<OneHotInfoT *>(value) : nullptr;
  }
  const OneHotInfoT *AsOneHotInfo() const {
    return type == Parameter_OneHotInfo ?
      reinterpret_cast<const OneHotInfoT *>(value) : nullptr;
  }
};

```


## 三元表达符

在C++中三元表达式可以嵌套使用,从而可以取代if else的操作。

```C++

static size_t MNNGridSampleComputeOffsetFP16(int h, int w, int height, int width, bool padMode) {
    if (padMode == true) { //padMode == BorderMode_ZEROS
        if (h < 0 || h >= height || w < 0 || w >= width) {
            return -1;
        }
    } else {
        // Clearly, CLAMP is the right way to go for GridSamplePaddingMode_BORDER
        // For GridSamplePaddingMode_REFLECTION, since we have reflected the values into (-1, 1),
        // the leftover reflections degrade to GridSamplePaddingMode_BORDER
        h = h < 0 ? 0 : (h > (height - 1) ? (height - 1) : h);
        w = w < 0 ? 0 : (w > (width - 1) ? (width - 1) : w);
    }
    return h * width * 8 + w * 8;
}


```