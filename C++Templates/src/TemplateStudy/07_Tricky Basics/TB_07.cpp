#include <iostream>

template <typename T>
T foo( )
{
	T x; // 적절할 초기값을 정하기 곤란하다.
	return x;
}

template <typename T>
T goo( )
{
	T x = T(); // 내장 데이터형에 대해서 0으로 초기화된다.
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