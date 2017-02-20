#include <iostream>
#include <string>

using namespace std;

template <typename T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

template <typename T, typename U>
decltype( T() + U() ) new_add( T lhs, U rhs )
{
	return lhs + rhs;
}

class UnsurpportedOperator{};

class TypeDeduction
{
public:
	mutable int m_value;
};

template <typename T>
void f( T& param ) {}

int main()
{
	cout << add( 1, 2 ) << endl; // 3이 출력
	cout << add( 3.1, 4.1 ) << endl; // 7.2이 출력
	cout << add( string( "hello " ), string( "world" ) ) << endl; // "hello world" 출력

	UnsurpportedOperator lhs;
	UnsurpportedOperator rhs;

	// + 연산자를 지원하지 않아 에러
	// add( lhs, rhs );

	cout <<  add( 4, 7 ) << endl; // ok T는 두 인자에 대해 int
	//add( 4, 4.2 ); // error 첫 번째 T는 int 두 번째 T는 double

	// 정상적으로 호출하기 위해서는 아래와 같이 호출하여야 한다.
	cout <<  add( static_cast<double>(4), 4.2 ) << endl; // 두 인자가 일치하도록 명시적으로 형변환
	cout <<  add<double>( 4, 4.2 ) << endl; // T의 데이터 형을 명시
	
	cout <<  new_add( 4, 4.2 ) << endl; // 파라미터가 다른 데이터형을 가질 수 있도록 명시

	// T&인 경우
	int x = 27;
	int& rx = x;
	const int cx = x;
	const int& crx = x;

	f( x );			// T: int ParamType : int&
	f( rx );		// T: int ParamType : int&
	f( cx );		// T: const int, ParamType : const int&
	f( crx );		// T: const int, ParamType : const int&
	// T&& 인 경우

	// T 인 경우
	TypeDeduction t = { 0 };
	auto deducted = t.m_value;
}