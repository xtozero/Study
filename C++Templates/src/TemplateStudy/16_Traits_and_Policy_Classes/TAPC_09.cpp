#include <cstddef>
#include <iostream>

template <typename T>
class TypeSize
{
public:
	static const size_t value = sizeof( T );
};

int main( )
{
	std::cout << "TypeSize<int>::value = "
			  << TypeSize<int>::value << std::endl;
}