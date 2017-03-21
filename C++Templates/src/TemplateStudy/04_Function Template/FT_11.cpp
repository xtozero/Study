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
	// �Լ� ���ø� �����ε��� ����ġ ���ϰ� �����ϴ� ���2
	min( 1, 2, 3 );
}