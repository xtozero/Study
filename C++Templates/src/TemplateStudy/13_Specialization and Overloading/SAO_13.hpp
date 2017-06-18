#pragma once

template <typename T>
int g( T, T x = 42 )
{
	return x;
}

template<> int g( int, int y );