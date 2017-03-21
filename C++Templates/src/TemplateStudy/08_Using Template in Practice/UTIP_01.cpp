// #include "UTIP_01.hpp"

#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}