#include <iostream>

namespace X
{
	template<typename T> void f( T );
}

namespace N
{
	using namespace X;
	enum E { el };
	void f( E )
	{
		std::cout << "N::f(N::E) called" << std::endl;
	}
}

void f( int )
{
	std::cout << "::f(int) called" << std::endl;
}

int main( )
{
	::f( N::el );  // ������ �Լ� �̸� : ADL �ƴ�
	f( N::el ); // �Ϲ����� ����� ::f()�� ã�� ADL�� N::f()�� ã��
}