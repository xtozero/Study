#include <iostream>

int max( const int& lhs, const int& rhs )
{
	std::cout << "max( int, int )" << std::endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& lhs, const T& rhs )
{
	std::cout << "max( T, T )" << std::endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& first, const T& second, const T& third )
{
	std::cout << "max( T, T, T )" << std::endl;
	return max( max( first, second ), third );
}

int main( )
{
	// 함수 템플릿의 오버로딩
	::max( 7, 42, 68 );			// 세 인자를 위한 템플릿 호출
	::max( 7.0, 42.0 );			// max<double> 호출
	::max( 'a', 'b' );			// max<char> 호출
	::max( 7, 42 );				// nontemplate 함수 max 호출
	::max<>( 7, 42 );				// max<int> 호출
	::max<double>( 7, 42 );		// max<double> 호출
	::max( 'a', 42.7 );			// nontemplate 함수 max 호출
}