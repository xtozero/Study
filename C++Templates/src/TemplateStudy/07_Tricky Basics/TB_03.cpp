#include <iostream>

void bar( ) { std::cout << "bar()" << std::endl; }

template <typename T>
class Base
{
public:
	void bar( ) { std::cout << "Base::bar()" << std::endl; }
};

template <typename T>
class Derived : Base<T>
{
public:
	void foo( )
	{
		bar( );
	}

	void goo( )
	{
		this->bar( );
		Base<T>::bar( );
	}
};

int main( )
{
	Derived<int> d;
	d.foo( );

	d.goo( );
}