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
	::f( N::el );  // 한정된 함수 이름 : ADL 아님
	f( N::el ); // 일반적인 룩업은 ::f()를 찾고 ADL은 N::f()를 찾음
}