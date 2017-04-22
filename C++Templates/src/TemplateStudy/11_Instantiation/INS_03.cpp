#include <iostream>

class MyInt
{
public:
	MyInt( int i ) {}
};

MyInt operator- ( const MyInt& )
{
	return MyInt( 1 );
}

bool operator > ( const MyInt&, const MyInt& )
{
	return false;
}

//typedef int Int;
typedef MyInt Int;

template <typename T>
void f( T i )
{
	if ( i > 0 )
	{
		g( -i );
	}
}

// 1
void g( Int )
{
	// 2
	f<Int>( 42 );
	// 3
}
// 4

int main( )
{
	g( Int( 2 ) );
}