#include <iostream>
#include <type_traits>

int main( )
{
	std::cout << std::is_copy_assignable<int>::value << std::endl;
	std::cout << std::is_union<int>( ) << std::endl;
}