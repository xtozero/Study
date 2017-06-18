#include <string>
#include <iostream>

template <typename T>
std::string f( T )
{
	return "Templates";
}

std::string f( int& )
{
	return "Not Templates";
}

int main( )
{
	int x = 7;
	std::cout << f( x ) << std::endl;
}