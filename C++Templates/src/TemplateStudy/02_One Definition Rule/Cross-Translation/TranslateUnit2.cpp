#include "CrossTranslation.h"

#include <iostream>

static int counter = 0;

inline void increase_counter( )
{
	++counter;
	std::cout << counter << std::endl;
}

inline void increase_counter2( )
{
	++counter;
	std::cout << counter << std::endl;
}

void count2( )
{
	increase_counter2( );
}

void count_error2( )
{
	increase_counter( );
}

// �⺻ ������ ���
namespace
{
	void unused( int a = 3 );
	void unused( int a )
	{
		std::cout << a << std::endl;
	}
}

void defaultArg2( )
{
	unused( );
}

// ���������� ������ �������� ���
class X
{
public:
	X( int );
	X( int, int );
};

X::X( int = 0 )
{
	std::cout << "X(int)" << std::endl;
}

class D : public X
{

};

D d2;