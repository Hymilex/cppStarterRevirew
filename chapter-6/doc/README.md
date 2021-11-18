# C++ 的 virtual

---

<h2>
目录
</h2>

- [C++ 的 virtual](#c-的-virtual)
  - [:one: virtual](#one-virtual)
  - [:two: 纯虚函数](#two-纯虚函数)
  - [:three: 虚析构](#three-虚析构)
  - [:four: 虚继承](#four-虚继承)


## :one: virtual

---

作为通常的原则，如果一个类定义了虚函数，那么它的析构函数就应当是virtual的。因为定义了虚函数则隐含着：这个类会被继承，并且会通过基类的指针指向子类对象，从而得到多态性。

**<u>虚函数是C++中用于实现多态(polymorphism)的机制。核心理念就是通过基类访问派生类定义的函数。</u>**


## :two: 纯虚函数

---

一个函数声明为纯虚后，纯虚函数的意思是：我是一个抽象类！不要把我实例化！不能被实例化，只能被子类覆盖。纯虚函数用来规范派生类的行为，实际上就是所谓的“接口”。它告诉使用者，我的派生类都会有这个函数。

即接口(Interface)。

```C++

#ifndef _IACTION_H_
#define _IACTION_H_

class IAction
{
public:
 virtual void run() = 0;
 virtual void attack() = 0;
}

#endif

```

## :three: 虚析构

---

如果一个类用作基类，我们通常需要virtual来修饰它的析构函数，这点很重要。

如果基类的析构函数不是虚析构，当我们用delete来释放基类指针(它其实指向的是派生类的对象实例)占用的内存的时候，只有基类的析构函数被调用，而派生类的析构函数不会被调用，这就可能引起内存泄露。

如果基类的析构函数是虚析构，那么在delete基类指针时，继承树上的析构函数会被自低向上依次调用，即最底层派生类的析构函数会被首先调用，然后一层一层向上直到该指针声明的类型。


## :four: 虚继承

---

在多继承中出现,并且发挥作用。虚拟继承是多重继承中特有的概念。虚拟基类是为解决多重继承而出现的。如:类D继承自类B1、B2，而类B1、B2都继承自类A，因此在类D中两次出现类A中的变量和函数。为了节省内存空间，可以将B1、B2对A的继承定义为虚拟继承，而A就成了虚拟基类。


虚拟继承在一般的应用中很少用到，所以也往往被忽视，这也主要是因为在C++中，多重继承是不推荐的，也并不常用，而一旦离开了多重继承，虚拟继承就完全失去了存在的必要因为这样只会降低效率和占用更多的空间。


```C++

class Animal
{
public:
	Animal() = default;
	// 此处不是纯虚函数,而是虚拟析构函数,为了使new创建的基类,能够按照顺序进行析构
	virtual ~Animal()
	{
		std::cout << "base destroyed.\n";
	}
	// 此处的virtual是为了实现多态,即调用者的类别决定具体调用的方法
	virtual void eat()
	{
		std::cout << "current animal eating at present!\n";
	}
	void sparking()
	{
		std::cout << "sparking...\n";
	}
private:
	int age;
}


class Dog :public virtual Animal
{
public:
	Dog() = default;
	~Dog() 
	{
		std::cout << "dog destroyed.\n";
	}
	void eat()
	{
		std::cout << "dog eating at present.\n";
	}
}

class Cat :public virtual Animal
{
public:
	Cat() = default;
	~Cat()
	{
		std::cout << "cat destroyed .\n";
	}
	void eat()
	{
		std::cout << "cat eating at present.\n";
	}
}

public PaXing:public Cat,public Dog
{
public:
	PaXing() = default;
	~PaXing()
	{
		std::cout << "\n";
	}
private:

}

void AnimalPrint(Animal* animal)
{
	animal->eat();
}

int main()
{
	Animal* animal = new Animal();
	{
		Dog dog;
	}
	Animal* dog = new Dog();
	AnimalPrint(dog);
	AnimalPrint(animal);

	delete dog;
	delete animal;

    return 0;
}


```