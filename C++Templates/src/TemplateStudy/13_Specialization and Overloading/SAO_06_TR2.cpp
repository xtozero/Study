#include <iostream>

template <typename T1, typename T2>
void f1( T2, T1 ) 
{
	std::cout << "void f1( T2, T1 ) " << std::endl;
}

extern void g( ); // 번역 단위 1에서 정의

int main( )
{
	f1<char, char>( 'a', 'b' );
	g( );
}
