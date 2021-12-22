# C++的深拷贝、浅拷贝

<h2>
目录
</h2>

- [C++的深拷贝、浅拷贝](#c的深拷贝浅拷贝)
  - [:one: 区别](#one-区别)
  - [:two:代码解释](#two代码解释)

## :one: 区别

---

1、在没有定义显式构造函数的情况下,系统会调用默认的拷贝函数,即浅拷贝,它能够完成成员的一一复制,与memcpy()的效果是十分相似的。当数据成员没有指针时,浅拷贝是完全够用的。

2、当数据成员中存在时,如果使用简单的浅拷贝,则两类中的两个指针将会指向同一个地址,当对象结束时,会调用两次析构函数,而导致指针悬挂的现象,所以此时必须使用深拷贝。

3、 深拷贝与浅拷贝的区别就在于**深拷贝会在堆内存中另外申请空间来储存数据，从而也就解决了指针悬挂的问题**。简而言之，当数据成员中有指针时，必须要用深拷贝。

4、换句话说,**浅拷贝只复制指向某个对象的指针，而不复制对象本身，新旧对象还是共享同一块内存**。但**深拷贝会另外创造一个一模一样的对象，新对象跟原对象不共享内存，修改新对象不会改到原对象**。

## :two:代码解释

---

```C++
class SString
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	SString(const char* string)
	{
		m_Size = (unsigned int)strlen(string);
		m_Buffer = new char[m_Size + 1];
		//memset(m_Buffer, 0, m_Size + 1);
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}
	SString(const SString& other, const char* c_string) = delete; // 表示禁用这个函数
	~SString()
	{
		delete[] m_Buffer;
	}
	// 浅拷贝共享对象成员的内存,深拷贝复制对象,重新分配内存
	SString(const SString& other) :m_Buffer(other.m_Buffer),m_Size(other.m_Size)
	{
		//memcpy(this,&other,sizeof(SString));

		//memcpy(this->m_Buffer,other.m_Buffer,m_Size);
	}
	SString(const SString& other, bool isDeep)
	{
		if (isDeep)
		{
			m_Size = other.m_Size;
			m_Buffer = new char[m_Size + 1];
			memcpy(m_Buffer,other.m_Buffer,m_Size + 1);
		}
		else
		{
			memcpy(this, &other, sizeof(SString));
		}
	}
	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const SString& string);
};

std::ostream& operator<<(std::ostream& stream, const SString& string)
{
	stream << string.m_Buffer;
	return stream;
}



int main(int argc, char* argv)
{


	SString ss_name_1 = "Simon";
	SString ss_name_2 = ss_name_1;
	SString ss_name_3(ss_name_1,1);
	ss_name_2[2] = 'c';
	ss_name_3[3] = 'w';

	std::cout << ss_name_1 << std::endl;
	std::cout << ss_name_2 << std::endl;
	std::cout << ss_name_3 << std::endl;
}
```