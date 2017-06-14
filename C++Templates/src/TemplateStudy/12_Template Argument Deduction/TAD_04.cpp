#include <iostream>

template <typename T>
void f1( const T& arg ) { std::cout << typeid( arg ).name( ) << std::endl; }

template <typename T>
void f2( volatile T& arg ) { std::cout << typeid( arg ).name( ) << std::endl; }

template <typename T>
void f3( const T* arg ) {}

template <typename T>
class Base {};

template <typename T>
class Derive : public Base<T> {};

template <typename T>
void f4( Base<T>* ) {}

void g( Derive<long> dl )
{
	f4( &dl );
}

int main()
{
	int val = 0;
	f1( val );
	f2( val );

	f3( &val );

	Derive<long> dl;
	g( dl );
}