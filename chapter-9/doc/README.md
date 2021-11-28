# C++ 的enum


<h2>
目录
</h2>

- [C++ 的enum](#c-的enum)
  - [:one: 常见enum](#one-常见enum)
    - [匿名枚举](#匿名枚举)
    - [struct中的enum使用](#struct中的enum使用)
    - [class中使用enum](#class中使用enum)

## :one: 常见enum


### 匿名枚举


这种比较常用,和typedef搭配使用。


```C++

typedef enum {
  CORE_ML__SPECIFICATION__DICTIONARY_FEATURE_TYPE__KEY_TYPE__NOT_SET = 0,
  CORE_ML__SPECIFICATION__DICTIONARY_FEATURE_TYPE__KEY_TYPE_INT64_KEY_TYPE = 1,
  CORE_ML__SPECIFICATION__DICTIONARY_FEATURE_TYPE__KEY_TYPE_STRING_KEY_TYPE = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(CORE_ML__SPECIFICATION__DICTIONARY_FEATURE_TYPE__KEY_TYPE)
} CoreML__Specification__DictionaryFeatureType__KeyTypeCase;



typedef enum {
	/** A well-formed message must have exactly one of this field. */
	PROTOBUF_C_LABEL_REQUIRED,

	/**
	 * A well-formed message can have zero or one of this field (but not
	 * more than one).
	 */
	PROTOBUF_C_LABEL_OPTIONAL,

	/**
	 * This field can be repeated any number of times (including zero) in a
	 * well-formed message. The order of the repeated values will be
	 * preserved.
	 */
	PROTOBUF_C_LABEL_REPEATED,

	/**
	 * This field has no label. This is valid only in proto3 and is
	 * equivalent to OPTIONAL but no "has" quantifier will be consulted.
	 */
	PROTOBUF_C_LABEL_NONE,
} ProtobufCLabel;

```

### struct中的enum使用

```C++

struct OneHotInfo FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef OneHotInfoT NativeTableType;
  static const flatbuffers::TypeTable *MiniReflectTypeTable() {
    return OneHotInfoTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_OUTERSIZE = 4,
    VT_INNERSIZE = 6
  };
  int32_t outerSize() const {
    return GetField<int32_t>(VT_OUTERSIZE, 0);
  }
  int32_t innerSize() const {
    return GetField<int32_t>(VT_INNERSIZE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_OUTERSIZE) &&
           VerifyField<int32_t>(verifier, VT_INNERSIZE) &&
           verifier.EndTable();
  }
  OneHotInfoT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(OneHotInfoT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<OneHotInfo> Pack(flatbuffers::FlatBufferBuilder &_fbb, const OneHotInfoT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};



```

### class中使用enum


```C++

#ifndef VulkanCommandPool_hpp
#define VulkanCommandPool_hpp

#include "core/NonCopyable.hpp"
#include "backend/vulkan/component/VulkanDevice.hpp"
#include "backend/vulkan/vulkan/vulkan_wrapper.h"
namespace MNN {
class VulkanImage;
class VulkanCommandPool : public NonCopyable {
public:
    VulkanCommandPool(const VulkanDevice& dev);
    virtual ~VulkanCommandPool();

    class Buffer : public NonCopyable {
    public:
        Buffer(const VulkanCommandPool* pool);
        virtual ~Buffer();

        VkCommandBuffer get() const {
            return mBuffer;
        }

        void begin(VkCommandBufferUsageFlags flags) const;
        void end() const;
        enum BarrierType {
            READ_WRITE = 0,
            WRITE_WRITE,
        };
        void barrierSource(VkBuffer source, size_t start, size_t end, BarrierType type = READ_WRITE) const;
        void barrierImage(VkImage source, VkImageLayout oldLayout, VkImageLayout newLayout, BarrierType type = READ_WRITE) const;
        void barrierImageIfNeeded(const VulkanImage* image, VkImageLayout newLayout, BarrierType type = READ_WRITE) const;

    private:
        VkCommandBuffer mBuffer;
        const VulkanCommandPool* mPool;
    };

    VulkanCommandPool::Buffer* allocBuffer() const;

    VkCommandPool pool() const {
        return mPool;
    }

    void submitAndWait(VkCommandBuffer buffer) const;

private:
    const VulkanDevice& mDevice;
    VkCommandPool mPool;
    mutable std::vector<VkCommandBuffer> mFreeBuffers;
};
} // namespace MNN
#endif /* VulkanCommandPool_hpp */


```