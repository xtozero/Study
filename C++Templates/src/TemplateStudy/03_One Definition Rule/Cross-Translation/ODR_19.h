#ifndef _ODR_19_H_
#define _ODR_19_H_

#include <iostream>

enum Color { red, green, blue };

template<typename T> void highlight( T x )
{
	paint( x );
}

void init( );

#endif
