#include <iostream>

template <typename T1, typename T2>
void f1( T2, T1 ) 
{
	std::cout << "void f1( T2, T1 ) " << std::endl;
}

extern void g( ); // ���� ���� 1���� ����

int main( )
{
	f1<char, char>( 'a', 'b' );
	g( );
}
