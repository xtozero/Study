#include <iostream>

template <typename T1, typename T2>
void f1( T1, T2 ) {}

template <typename T1, typename T2>
void f1( T2, T1 ) {}

template <typename T>
long f2( T ) {}

template <typename T>
char f2( T ) {}

int main( )
{
	f1<char, char>( 'a', 'b' ); // f1( T1, T2 )과 f1( T2, T1 )의 인스턴스화 결과 f1( char, char )의 같은 함수가 생성되기 때문에 모호하다.
}