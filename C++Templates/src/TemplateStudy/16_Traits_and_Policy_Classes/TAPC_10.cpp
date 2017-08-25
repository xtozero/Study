#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include <functional>

template <typename T>
class ElementT;

template <typename T>
class ElementT<std::vector<T>>
{
public:
	using Type = T;
};

template <typename T>
class ElementT<std::list <T>>
{
public:
	using Type = T;
};

template <typename T>
class ElementT<std::stack<T>>
{
public:
	using Type = T;
};

template <typename C>
class ElementT
{
public:
	using Type = typename C::value_type;
};

template <typename T>
void print_element_type( const T& c )
{
	std::cout << "Container of "
			  << typeid( typename ElementT<T>::Type ).name( )
			  << " elements." << std::endl;
}

int main( )
{
	std::stack<bool> s;
	print_element_type( s );
}