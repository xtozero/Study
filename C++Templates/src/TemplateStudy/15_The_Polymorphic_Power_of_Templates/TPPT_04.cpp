#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

template <typename T>
void print_max( const T& coll )
{
	typename T::const_iterator pos;

	pos = std::max_element( coll.begin( ), coll.end( ) );

	if ( pos != coll.end( ) )
	{
		std::cout << *pos << std::endl;
	}
	else
	{
		std::cout << "empty" << std::endl;
	}
}

int main( )
{
	std::vector<int> c1 = { 10, 9, 8, 20, 40, 9 };
	std::list<float> c2 = { 1.f, 1.f, 2.f, 3.f, 5.f, 8.f };

	print_max( c1 );
	print_max( c2 );
}