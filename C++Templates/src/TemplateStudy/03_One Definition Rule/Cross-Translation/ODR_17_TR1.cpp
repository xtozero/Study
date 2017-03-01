#include "ODR_17.h"

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