#include <iostream>

template <typename T> void f( )
{
	std::cout << "f() TR1" << std::endl;
}

// template <> void f<int>( );	// Ư��ȭ�� ����

extern template void f<int>( );	// ��������� ���ǵ��� ����

void g( )
{
	f<int>( );
}