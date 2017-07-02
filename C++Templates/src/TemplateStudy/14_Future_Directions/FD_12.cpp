#include <iostream>
//class D_Union
//{
//public:
//	enum { n_bytes };
//	char bytes[n_bytes];
//};

template <typename T, typename... U>
class Alignment
{
public:
	enum { max = ( alignof( T ) > Alignment<U...>::max ) ? alignof( T ) : Alignment<U...>::max };
};

template <typename T>
class Alignment<T>
{
public:
	enum { max = alignof( T ) };
};

struct PerfectFit
{
	char a;
	short b;
	bool d;
};

struct Pedding
{
	char a;
	double c;
};

int main( )
{
	std::cout << Alignment<PerfectFit, Pedding>::max << std::endl;
}