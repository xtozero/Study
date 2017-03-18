#include <iostream>

template <typename T>
T foo( )
{
	T x; // ������ �ʱⰪ�� ���ϱ� ����ϴ�.
	return x;
}

template <typename T>
T goo( )
{
	T x = T(); // ���� ���������� ���ؼ� 0���� �ʱ�ȭ�ȴ�.
	return x;
}

template <typename T>
class MyClass
{
public:
	T x;

	MyClass( ) : x( )
	{

	}

	//or in c++11

	T y = T( );
};

int main( )
{
	std::cout << foo<int>( ) << std::endl;
	std::cout << goo<int>( ) << std::endl;

	MyClass<int> cls;
	std::cout << cls.x << std::endl;
	std::cout << cls.y << std::endl;
}