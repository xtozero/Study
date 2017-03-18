#include <string>

template <typename T>
const T& max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
const T maxByValue( const T lhs, const T rhs )
{
	return lhs < rhs ? rhs : lhs;
}

int main( )
{
	std::string s;

	max( "apple", "peach" ); // ok
	max( "apple", "banana" ); // error
	max( "apple", s ); // error

	maxByValue( "apple", "banana" ); // ok
	maxByValue( "apple", s ) // error
}