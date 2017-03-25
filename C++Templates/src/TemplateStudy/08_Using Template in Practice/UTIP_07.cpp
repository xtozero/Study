#include <iostream>

template <typename T>
void clear( const T& p )
{
	*p = 0;
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

template <typename T>
inline void ignore( const T& )
{
}

template <typename T>
void shell( const T& env )
{
	/*
	class ShallowChecks
	{
		void deref( typename T::Index ptr )
		{
			ignore( *ptr );
		}
	};
	*/

	// or

	/*
	static_assert( std::is_pointer<typename T::Index>(), "is not pointer" );
	*/
	typename T::Index i = T::Index();
	middle<T>( i );
}

class Client
{
public:
	typedef int Index;
};

int main( )
{
	Client main_client;
	shell( main_client );
}
