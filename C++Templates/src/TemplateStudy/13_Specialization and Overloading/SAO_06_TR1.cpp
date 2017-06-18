#include <iostream>

template <typename T1, typename T2>
void f1( T1, T2 )
{
	std::cout << "void f1( T1, T2 ) " << std::endl;
}

void g( )
{
	f1<char, char>( 'a', 'b' );
}