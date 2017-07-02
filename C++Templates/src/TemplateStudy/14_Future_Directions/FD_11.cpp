#include <iostream>

template <typename T, typename... U>
const T& max( const T& first, const T& second, const U&... remain )
{
	return max( max( first, second ), remain... );
}

template <typename T>
const T& max( const T& first, const T& second )
{
	return first > second ? first : second;
}

template <typename... T>
int countArg( const T&... args )
{
	return sizeof...(args);
}

int main( )
{
	std::cout << max( 1, 2, 3, 5, 8, 9 ) << std::endl;
	std::cout << ( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ) << std::endl;
}