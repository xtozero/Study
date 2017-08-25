#include <array>
#include <iostream>
#include <type_traits>

template <typename T>
class RParam
{
public:
	using Type = typename std::conditional<sizeof( T ) <= 2 * sizeof( void* ), T, const T&>::type;
};

template <typename T, int N>
class RParam<std::array<T, N>>
{
public:
	using Type = const T&;
};

class MyClass1
{
public:
	MyClass1( ) = default;
	MyClass1( const MyClass1& )
	{
		std::cout << "MyClass1 copy constructor called\n" << std::endl;
	}
};

class MyClass2
{
public:
	MyClass2( ) = default;
	MyClass2( const MyClass2& )
	{
		std::cout << "MyClass2 copy constructor called\n" << std::endl;
	}
};

template <>
class RParam<MyClass2>
{
public:
	using Type = MyClass2;
};

template <typename T1, typename T2>
void foo( typename RParam<T1>::Type p1, typename RParam<T2>::Type p2 )
{

}

template <typename T1, typename T2>
void foo_wrapper( T1 p1, T2 p2 )
{
	foo<T1, T2>( p1, p2 );
}

int main( )
{
	MyClass1 m1;
	MyClass2 m2;
	foo<MyClass1, MyClass2>( m1, m2 );
	foo_wrapper( m1, m2 );
}