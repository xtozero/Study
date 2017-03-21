#include <iostream>
#include <string>

template <typename T> // or template <class T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

int main( )
{
	std::cout << add( 1, 2 ) << std::endl; // 3이 출력
	/*
	위의 함수로 인해 아래와 같은 함수가 생성된다.
	inline int add( int lhs, int rhs )
	{
	return lhs + rhs;
	}
	*/

	std::cout << add( 3.1, 4.1 ) << std::endl; // 7.2이 출력
	std::cout << add( std::string( "hello " ), std::string( "world" ) ) << std::endl; // "hello world" 출력
}