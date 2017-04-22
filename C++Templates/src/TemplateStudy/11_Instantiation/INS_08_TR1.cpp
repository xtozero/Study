#include <iostream>

template <typename T> void f( )
{
	std::cout << "f() TR1" << std::endl;
}

// template <> void f<int>( );	// 특수화로 선언

extern template void f<int>( );	// 선언됐으나 정의되지 않음

void g( )
{
	f<int>( );
}