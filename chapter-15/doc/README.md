# C++ 的动态数组 std::vector

<h2>
目录
</h2>

- [C++ 的动态数组 std::vector](#c-的动态数组-stdvector)
  - [:one: vector优缺点](#one-vector优缺点)
    - [优点](#优点)
    - [缺点](#缺点)
  - [:two: vector 使用 [] operator和 at的差异](#two-vector-使用--operator和-at的差异)

小感慨:

发现比自己优秀的博主太多了,虽然说经常要和自己比,但是差距是真实存在的。

路漫漫其修远兮,吾将上下而求索。


主要探究以下 **EASTL**对于vector的源码实现。



## :one: vector优缺点

### 优点

1、定义时可以不用确定大小

2、节省空间

3、支持随机访问[i]


### 缺点

1、进行插入删除效率低

2、智能在末端进行pop和push

## :two: vector 使用 [] operator和 at的差异

operator [] 在回传元素时是不会做任何的边界检查,而at()取元素时会做边界的处理,如果存取越界是,std::vector会抛出一个out_of_range,故at比较安全,[]operator比较快。
