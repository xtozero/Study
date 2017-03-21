#include <cstring>
#include <iostream>
#include <string>

template <typename T>
T max( const T& lhs, const T& rhs )
{
	std::cout << "max( T, T )" << std::endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T* const& max( T* const & a, T* const & b )
{
	std::cout << "T* const & a, T* const & b" << std::endl;
	return *a < *b ? b : a;
}

const char* const& max( const char* const& a, const char* const& b )
{
	std::cout << "max( const char* const& a, const char* const& b )" << std::endl;
	return strcmp( a, b ) < 0 ? b : a;
}

int main( )
{
	std::string hey = "hey";
	std::string you = "you";

	::max( hey, you );

	int a = 1;
	int b = 2;
	int* p1 = &b;
	int* p2 = &a;

	::max( p1, p2 );

	const char* s1 = "Alpha";
	const char* s2 = "Bong";
	::max( s1, s2 );
}