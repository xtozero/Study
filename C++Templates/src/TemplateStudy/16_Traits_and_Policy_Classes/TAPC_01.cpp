#include <iostream>

template <typename T>
inline T accum( const T* beg, const T* end )
{
	T total = T( );
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}

int main( )
{
	int num[] = { 1, 2, 3, 4, 5 };

	std::cout << "Æò±Õ°ª :"
			<< accum( &num[0], &num[5] ) / 5
			<< std::endl;

	char name[] = "templates";
	int length = sizeof( name ) - 1;

	std::cout << "Æò±Õ°ª :"
			<< accum( &name[0], &name[length] ) / length
			<< std::endl;
}