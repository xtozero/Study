#include <iostream>
#include <type_traits>

template <typename T, int I>
class Mix {};

typedef int Int;

using Short = short;

int main( )
{
	std::cout << ( std::is_same<Mix<int, 3 * 3>, Mix<Int, 4 + 5>>() ? "true" : "false" ) << std::endl;
	std::cout << ( std::is_same<Mix<short, 2 + 5>, Mix<Short, 7>>::value ? "true" : "false") << std::endl;
}