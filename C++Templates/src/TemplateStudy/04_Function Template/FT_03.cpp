#include <iostream>

template <typename T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2>
decltype(T1( ) + T2( )) new_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

int main( )
{
	// + 연산자를 지원하지 않아 에러
	// add( lhs, rhs );

	std::cout << add( 4, 7 ) << std::endl; // ok T는 두 인자에 대해 int
								 //add( 4, 4.2 ); // error 첫 번째 T는 int 두 번째 T는 double

								 // 정상적으로 호출하기 위해서는 아래와 같이 호출하여야 한다.
	std::cout << add( static_cast<double>(4), 4.2 ) << std::endl; // 두 인자가 일치하도록 명시적으로 형변환
	std::cout << add<double>( 4, 4.2 ) << std::endl; // T의 데이터 형을 명시

	std::cout << new_add( 4, 4.2 ) << std::endl; // 파라미터가 다른 데이터형을 가질 수 있도록 명시

}