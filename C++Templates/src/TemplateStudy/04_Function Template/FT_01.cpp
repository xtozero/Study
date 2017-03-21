#include <iostream>
#include <string>

template <typename T> // or template <class T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

int main( )
{
	std::cout << add( 1, 2 ) << std::endl; // 3�� ���
	/*
	���� �Լ��� ���� �Ʒ��� ���� �Լ��� �����ȴ�.
	inline int add( int lhs, int rhs )
	{
	return lhs + rhs;
	}
	*/

	std::cout << add( 3.1, 4.1 ) << std::endl; // 7.2�� ���
	std::cout << add( std::string( "hello " ), std::string( "world" ) ) << std::endl; // "hello world" ���
}