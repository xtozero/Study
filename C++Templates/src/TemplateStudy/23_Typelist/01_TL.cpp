#include "addconst.h"
#include "Typelist.h"

#include <iostream>
#include <typeinfo>

int main( )
{
	using SignedIntegralTypes = Typelist<signed int, short, int, long, long long>;

	using GetFront = Front<SignedIntegralTypes>;
	std::cout << typeid( GetFront ).name( ) << std::endl;

	using NewType = PushFront<PopFront<SignedIntegralTypes>, bool>;
	std::cout << typeid( NewType ).name( ) << std::endl;

	using TL = NthElement<Typelist<short, int, long>, 2>;
	std::cout << typeid( TL ).name( ) << std::endl;

	using LT = LargestType<Typelist<bool, int, long, short>>;
	std::cout << typeid( LT ).name( ) << std::endl;

	using PB = PushBack<Typelist<char, short>, int>;
	std::cout << typeid( PB ).name( ) << std::endl;

	using RT = Reverse<SignedIntegralTypes>;
	std::cout << typeid( RT ).name( ) << std::endl;

	using TR = Transform<SignedIntegralTypes, AddConstT>;
	std::cout << typeid( TR ).name( ) << std::endl;

	using AC_RT = Accumulate<SignedIntegralTypes, PushFrontT, Typelist<>>;
	std::cout << ( std::is_same<RT, AC_RT>::value ? "RT, AC_RT is same" : "RT, AC_RT is not same" ) << std::endl;

	using LTA = LargesetTypeAcc<Typelist<bool, int, long, short>>;
	std::cout << ( std::is_same<LT, LTA>::value ? "LT, LTA is same" : "LT, LTA is not same" ) << std::endl;
}