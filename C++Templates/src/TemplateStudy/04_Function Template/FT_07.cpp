#include <iostream>

template <typename T = int> // c++ 11 지원 컴파일러 부터 가능
void DefaultParameter( T value ) {}

template <typename T1, typename T2>
T1 add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2, typename R>
R add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename R, typename T1, typename T2>
R add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2>
decltype(T1( ) + T2( )) new_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

// c++ 14 부터 가능
template <typename T1, typename T2>
decltype(auto) auto_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

int main( )
{
	// 함수 템플릿의 기본 파라미터 사용
	DefaultParameter( 1 );

	// 서로 다른 템플릿 파라미터를 사용한 add 버전
	add( 1.f, 1 );

	// 반환형을 지정할 수 있도록한 add 버전 1
	add<int, double, double>( 1, 1.f );

	// 반환형을 지정할 수 있도록한 add 버전 2
	add<double>( 1, 1.f );

	// decltype, auto를 사용한 add 버전
	std::cout << new_add( 5.1234, 1 ) << std::endl;
	std::cout << auto_add( 1.2345f, 2L ) << std::endl;
}