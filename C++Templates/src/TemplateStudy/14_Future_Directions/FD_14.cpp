#include <algorithm>
#include <iostream>
#include <vector>

class BigValue
{
public:
	void init( )
	{
		std::cout << "init" << std::endl;
	}
};

class Init
{
public:
	void operator()( BigValue& v ) const
	{
		v.init( );
	}
};

int main()
{
	std::vector<BigValue> vec;
	vec.emplace_back( );
	vec.emplace_back( );
	vec.emplace_back( );

	std::for_each( vec.begin( ), vec.end( ), Init() );

	std::for_each( vec.begin( ), vec.end( ), []( BigValue& v ) { v.init( ); } );
}