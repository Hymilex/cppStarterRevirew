# C++ 头文件高级

---

<h2>目录</h2>

- [C++ 头文件高级](#c-头文件高级)
  - [:one: 常规头文件](#one-常规头文件)
    - [理论](#理论)
    - [实践](#实践)
  - [:two: template头文件](#two-template头文件)
    - [理论](#理论-1)
    - [实践](#实践-1)
  - [:three: cc文件调用](#three-cc文件调用)


## :one: 常规头文件

---

### 理论

### 实践

```C++

#ifndef HYLIM_H_
#define HYLIM_H_

namespace HySp
{
    enum Season{SPRING=0,SUMMER,AUTUMN,WINTER};
    
    enum
    {
        INFO =0,
        WARNING=1,
        ERROR=2
    };

    struct Vec2
    {
        float x,y;
        Vec2()=delete;
        Vec2(int mx,int my):x(mx),y(my){}
        Vec2& operator+(const Vec2& other)
        {
            this->x = this->x + other.x;
            this->y = this->y + other.y;
            return *this;
        }
    };
    
    class Student
    {
    private:
    Season m_season=Season::WINTER;
    public:
        Student()=default;
        Student(Season s):m_season(s){}
        ~Student(){}
    };
    
}

#endif

```


## :two: template头文件

---

### 理论

### 实践

## :three: cc文件调用

---

