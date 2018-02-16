#include "cons.h"

#include <iostream>

template <typename T, typename U>
struct SmallerThanT
{
	static constexpr bool value = sizeof( T ) < sizeof( U );
};

int main( )
{
	using TwoShort = Cons<short, Cons<unsigned short>>;

	using ConsList = Cons<int, Cons<char, Cons<short, Cons<double>>>>;
	using SortedType = InsertionSort<ConsList, SmallerThanT>;
	using Expected = Cons<char, Cons<short, Cons<int, Cons<double>>>>;

	std::cout << ( std::is_same<SortedType, Expected>::value ? "is same" : "is not same" ) << std::endl;
}