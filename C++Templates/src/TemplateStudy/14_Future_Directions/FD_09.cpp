#include <iostream>
#include <type_traits>

template <typename T>
void clear( const T& p )
{
	*p = 0; // T가 포인터와 유사한 데이터형을 가진다고 가정했다.
}

template <typename T>
void core( const T& p )
{
	clear( p );
}

template <typename T>
void middle( typename T::Index p )
{
	core( p );
}

namespace detail {
	template <typename T> auto test( T* val ) -> decltype( *(*val) );
	struct two { char c[2]; };
	template <typename T> two test( ... );
}

template <class T>
struct has_dereference_operator : std::integral_constant<bool, !std::is_same<decltype( detail::test<T>( nullptr ) ), detail::two>::value> {};

template <typename T>
void shell( const T& env )
{
	typename T::Index i = 0;
	static_assert( has_dereference_operator<T::Index>::value, "illigal type" );
	middle<T>( i );
}

class Client
{
public:
	typedef int Index;

	int& operator*()
	{
		return m_value;
	}

	int m_value;
};

int main( )
{
	Client main_client;
	// shell( main_client );

	std::cout << has_dereference_operator<int*>::value << std::endl;		// true
	std::cout << has_dereference_operator<int>::value << std::endl;			// false
	std::cout << has_dereference_operator<int&>::value << std::endl;		// false
	std::cout << has_dereference_operator<const int*>::value << std::endl;	// true
	std::cout << has_dereference_operator<Client>::value << std::endl;		// true
}