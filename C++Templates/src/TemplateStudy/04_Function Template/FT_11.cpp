#include <iostream>
#include <cstdlib>

template <typename T>
const T& min( const T& lhs, const T& rhs )
{
	std::cout << "min( T, T )" << std::endl;
	return lhs < rhs ? lhs : rhs;
}

/*
const int& min( const int& lhs, const int& rhs )
{
std::cout << "min( const int& lhs, const int& rhs )" << std::endl;
return lhs < rhs ? lhs : rhs;
}
*/

template <typename T>
const T& min( const T& first, const T& second, const T& third )
{
	std::cout << "min( T, T, T )" << std::endl;
	return min( min( first, second ), third );
}

const int& min( const int& lhs, const int& rhs )
{
	std::cout << "min( const int& lhs, const int& rhs )" << std::endl;
	return lhs < rhs ? lhs : rhs;
}

int main( )
{
	// 함수 템플릿 오버로딩이 예상치 못하게 동작하는 경우2
	min( 1, 2, 3 );
}