#include "ctvalue.h"
#include "valuelist.h"
#include "Typelist.h"

#include <iostream>
#include <type_traits>
#include <typeinfo>

int main( )
{
	using Primes = Typelist<CTValue<int, 2>, CTValue<int, 3>, CTValue<int, 5>, CTValue<int, 7>, CTValue<int, 11>>;

	Accumulate<Primes, MultiplyT, CTValue<int, 1>>::value;

	using Primes = CTTypelist<int, 2, 3, 5, 7, 11>;

	using Integers = Valuelist<int, 6, 2, 4, 9, 5, 2, 1, 7>;

	using SortedIntegers = InsertionSort<Integers, GreaterThanT>;

	static_assert( std::is_same<SortedIntegers, Valuelist<int, 9, 7, 6, 5, 4, 2, 2, 1>>::value, "inserttion sort failed" );

	using SignedIntegralTypes = Typelist<signed char, short, int, long, long long>;

	using ReversedSignedIntegerTypes = Select<SignedIntegralTypes, Valuelist<unsigned, 4, 3, 2, 1, 0>>;
	std::cout << typeid(ReversedSignedIntegerTypes).name() << std::endl;
}