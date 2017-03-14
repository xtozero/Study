#include <algorithm>
#include <iostream>
#include <vector>

template <typename T, int VAL>
T addValue( const T& x )
{
	return x + VAL;
}

int main( )
{
	// std::vector<int> source = { 10, 20, 30, 40, 50, 60 };
	std::vector<int> source;
	source.push_back( 10 );
	source.push_back( 20 );
	source.push_back( 30 );
	source.push_back( 40 );
	source.push_back( 50 );
	source.push_back( 60 );

	std::vector<int> dest( source.size() );

	std::transform( source.begin( ), source.end( ), dest.begin( ), addValue<int, 5> );
}