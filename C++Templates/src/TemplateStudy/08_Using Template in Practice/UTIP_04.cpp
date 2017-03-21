#ifndef  UTIP_04_CPP
#define UTIP_04_CPP

#include "UTIP_04.hpp"

#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}

#endif
