# C++ 的 string


<h2>
目录
</h2>

- [C++ 的 string](#c-的-string)
  - [:zero: string的使用](#zero-string的使用)
    - [介绍](#介绍)
    - [充分使用string 操作符](#充分使用string-操作符)
    - [string的find函数](#string的find函数)
    - [string insert, replace, erase](#string-insert-replace-erase)
  - [:one: string 和 C风格字符串](#one-string-和-c风格字符串)
  - [:two: string 和 Charactor Traits](#two-string-和-charactor-traits)
  - [:three: string的建议](#three-string的建议)
  - [:four: 区别](#four-区别)
  - [:five:参考](#five参考)


## :zero: string的使用

---


### 介绍

其实，string并不是一个单独的容器，只是basic_string 模板类的一个typedef 而已，相对应的还有wstring, 你在string 头文件中你会发现下面的代码:

```C++

extern "C++"{
    typedef basic_string<char> string;
    typedef basic_string<wchar_t> wstring;
}

```

由于只是解释string的用法，如果没有特殊的说明，本文并不区分string 和 basic_string的区别。

string 其实相当于一个保存字符的序列容器，因此除了有字符串的一些常用操作以外，还有包含了所有的序列容器的操作。字符串的常用操作包括：增加、删除、修改、查找比较、链接、输入、输出等。详细函数列表参看附录。不要害怕这么多函数，其实有许多是序列容器带有的，平时不一定用的上。

如果你要想了解所有函数的详细用法，你需要查看basic_string，或者下载STL编程手册。这里通过实例介绍一些常用函数。

### 充分使用string 操作符

string 重载了许多操作符，包括 +, +=, <, =, , [], <<, >>等，正式这些操作符，对字符串操作非常方便。


```C++

#include <string>
#include <iostream>
using namespace std;
int main() {
	string strinfo = "Please input your name:";
	cout << strinfo;
	cin >> strinfo;
	if (strinfo == "winter")
		cout << "you are winter!" << endl;
	else if (strinfo != "wende")
		cout << "you are not wende!" << endl;
	else if (strinfo < "winter")
		cout << "your name should be ahead of winter" << endl;
	else
		cout << "your name should be after of winter" << endl;
	strinfo += " , Welcome to China!";
	cout << strinfo << endl;
	cout << "Your name is :" << endl;
	string strtmp = "How are you? " + strinfo;
	for (int i = 0; i < strtmp.size(); i++)
		cout << strtmp[i];
	return 0;
}

```

有了这些操作符，在STL中仿函数都可以直接使用string作为参数，例如 less, great, equal_to 等，因此在把string作为参数传递的时候，它的使用和int 或者float等已经没有什么区别了。例如，你可以使用:

```C++

std::map<string,int> my_map;

```

有了 operator + 以后，你可以直接连加，例如:

```C++

string strinfo="Winter";
string strlast="Hello " + strinfo + "!";
//你还可以这样：
string strtest="Hello " + strinfo + " Welcome" + " to China" + " !";

```

有了操作符以后，assign(), append(), compare(), at()等函数，除非有一些特殊的需求时，一般是用不上。当然at()函数还有一个功能，那就是检查下标是否合法，如果是使用:

```C++

string str="winter";
//下面一行有可能会引起程序中断错误
str[100]='!';
//下面会抛出异常:throws: out_of_range
cout<<str.at(100)<<endl;

```

了解了吗？如果你**希望效率高，还是使用[]来访问**，如果你**希望稳定性好，最好使用at()来访问**。


### string的find函数

由于查找是使用最为频繁的功能之一，string 提供了非常丰富的查找函数。

所有的查找函数都返回一个size_type类型，这个返回值一般都是所找到字符串的位置，如果没有找到，则返回string::npos。有一点需要特别注意，所有和string::npos的比较一定要用string::size_type来使用，不要直接使用int 或者unsigned int等类型。其实string::npos表示的是-1, 看看头文件：


find 和 rfind 都还比较容易理解，一个是正向匹配，一个是逆向匹配，后面的参数pos都是用来指定起始查找位置。对于find_first_of 和find_last_of 就不是那么好理解。


find_first_of 是给定一个要查找的字符集，找到这个字符集中任何一个字符所在字符串中第一个位置。

```C++

#include <string>
#include <iostream>
using namespace std;
int main() {
	string strinfo = " //*---Hello Word!......------";
	string strset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int first = strinfo.find_first_of(strset);
	if (first == string::npos) {
		cout << "not find any characters" << endl;
		return -1;
	}
	int last = strinfo.find_last_of(strset);
	if (last == string::npos) {
		cout << "not find any characters" << endl;
		return -1;
	}
	cout << strinfo.substr(first, last - first + 1) << endl;
	return 0;
}

```

这里把所有的英文字母大小写作为了需要查找的字符集，先查找第一个英文字母的位置，然后查找最后一个英文字母的位置，然后用substr 来的到中间的一部分，用于输出结果。下面就是其结果:

```

Hello Word

```

### string insert, replace, erase

了解了string 的操作符，查找函数和substr，其实就已经了解了string的80%的操作了。insert函数, replace函数和erase函数在使用起来相对简单。下面以一个例子来说明其应用。

```C++

void string_replace(string & strBig, const string & strsrc, const string &strdst) {
	string::size_type pos = 0;
	string::size_type srclen = strsrc.size();
	string::size_type dstlen = strdst.size();
	while ((pos = strBig.find(strsrc, pos)) != string::npos) {
		strBig.replace(pos, srclen, strdst);
		pos += dstlen;
	}
}
#include <string>
#include <iostream>
using namespace std;
int main() {
	string strinfo = "This is Winter, Winter is a programmer. Do you know Winter?";
	cout << "Orign string is :/n" << strinfo << endl;
	string_replace(strinfo, "Winter", "wende");
	cout << "After replace Winter with wende, the string is :/n" << strinfo << endl;
	return 0;
}

```

当然，这种方法没有使用replace来得直接。



## :one: string 和 C风格字符串

---

c_str()的流程是：先调用terminate()，然后在返回data()。因此如果你对效率要求比较高，而且你的处理又不一定需要以/0的方式结束，你最好选择data()。但是对于一般的C函数中，需要以const char*为输入参数，你就要使用c_str()函数。


对于c_str() data()函数，返回的数组都是由string本身拥有，千万不可修改其内容。其原因是许多string实现的时候采用了引用机制，也就是说，有可能几个string使用同一个字符存储空间。而且你不能使用sizeof(string)来查看其大小。详细的解释和实现查看Effective STL的条款15：小心string实现的多样性。





## :two: string 和 Charactor Traits

---


现在默认的string版本中，并不支持忽略大小写的比较函数和查找函数，如果你想练练手，你可以试试改写一个char_traits , 然后生成一个case_string类, 也可以在string 上做继承，然后派生一个新的类，例如：ext_string，提供一些常用的功能，例如：
1、定义分隔符。给定分隔符，把string分为几个字段。
2、提供替换功能。例如，用winter, 替换字符串中的wende
3、大小写处理。例如，忽略大小写比较，转换等
4、整形转换。例如把"123"字符串转换为123数字。
这些都是常用的功能，如果你有兴趣可以试试。其实有人已经实现了，看看Extended STL string。如果你想偷懒，下载一个头文件就可以用，有了它确实方便了很多。


## :three: string的建议

---


使用string 的方便性就不用再说了，这里要重点强调的是string的安全性。
string并不是万能的，如果你在一个大工程中需要频繁处理字符串，而且有可能是多线程，那么你一定要慎重(当然，在多线程下你使用任何STL容器都要慎重)。
string的实现和效率并不一定是你想象的那样，如果你对大量的字符串操作，而且特别关心其效率，那么你有两个选择，首先，你可以看看你使用的STL版本中string实现的源码；另一选择是你自己写一个只提供你需要的功能的类。
string的c_str()函数是用来得到C语言风格的字符串，其返回的指针不能修改其空间。而且在下一次使用时重新调用获得新的指针。
string的data()函数返回的字符串指针不会以'/0'结束，千万不可忽视。
尽量去使用操作符，这样可以让程序更加易懂（特别是那些脚本程序员也可以看懂）


## :four: 区别

---

std::string是std::basic_string<T> 的一个实例:

```C++

typedef std::basic_string<char> string;

```


## :five:参考

---

1、https://www.cnblogs.com/rosesmall/archive/2012/03/28/2422373.html

2、https://github.com/kango31/snowball/wiki/String