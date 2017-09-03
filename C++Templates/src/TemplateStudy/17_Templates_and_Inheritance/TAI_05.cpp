#include <iostream>

class NotVirtual
{
};

class Virtual
{
public:
	virtual void foo() {}
};

template <typename VBase>
class Base : private VBase
{
public:
	void foo() 
	{
		std::cout << "Base::foo()" << std::endl;
	}
};

template <typename V>
class Derived : public Base<V>
{
public:
	void foo( )
	{
		std::cout << "Derived::foo()" << std::endl;
	}
};

int main( )
{
	Base<NotVirtual>* p1 = new Derived<NotVirtual>;
	p1->foo( );

	Base<Virtual>* p2 = new Derived<Virtual>;
	p2->foo( );

	delete p1;
	delete p2;
}