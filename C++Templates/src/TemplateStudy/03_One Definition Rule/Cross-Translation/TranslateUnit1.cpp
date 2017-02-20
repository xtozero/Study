#include "CrossTranslation.h"

#include <iostream>

static int counter = 0;

inline void increase_counter( )
{
	++counter;
	std::cout << counter << std::endl;
}

inline void increase_counter1( )
{
	++counter;
	std::cout << counter << std::endl;
}

void count1( )
{
	increase_counter1( );
}

void count_error1( )
{
	increase_counter( );
}

// �⺻ ������ ���
namespace
{
	void unused( int a = 4 );
	void unused( int a )
	{
		std::cout << a << std::endl;
	}
}

void defaultArg1( )
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

X::X( int = 0, int = 0 )
{
	std::cout << "X(int, int)" << std::endl;
}

class D : public X
{

};

D d1;

// ���ø��� ���
namespace
{
	void paint( Color c )
	{
		std::cout << "paint - TraslationUnit1 : " << c << std::endl;
	}
}

void init( )
{
	highlight( blue );
}