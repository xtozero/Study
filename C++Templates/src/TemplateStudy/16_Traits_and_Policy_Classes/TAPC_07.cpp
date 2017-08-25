#include <iostream>
#include <numeric>

template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
	static AccT zero( )
	{
		return 0;
	}
};

template<>
class AccumulationTraits<short>
{
public:
	typedef int AccT;
	static AccT zero( )
	{
		return 0;
	}
};

template <>
class AccumulationTraits<int>
{
public:
	typedef long AccT;
	static AccT zero( )
	{
		return 0;
	}
};

template <>
class AccumulationTraits<unsigned int>
{
public:
	typedef unsigned long AccT;
	static AccT zero( )
	{
		return 0;
	}
};

template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
	static AccT zero( )
	{
		return 0.0;
	}
};

template <typename T1, typename T2>
class SumPolicy
{
public:
	static void accumulate( T1& total, const T2& value )
	{
		total += value;
	}
};

/*
template <bool use_compound_op = true>
class SumPolicy
{
public:
	template <typename T1, typename T2>
	static void accumulate( T1& total, const T2& value )
	{
		total += value;
	}
};

template <>
class SumPolicy<false>
{
public:
	template <typename T1, typename T2>
	static void accumulate( T1& total, const T2& value )
	{
		total = total + value;
	}
};
*/

template <typename T1, typename T2>
class MultPolicy
{
public:
	static void accumulate( T1& total, const T2& value )
	{
		total *= value;
	}
};

template <typename T,
	template<typename, typename> class Policy = SumPolicy,
	typename Traits = AccumulationTraits<T>>
	inline typename Traits::AccT accum( const T* beg, const T* end )
{
	using AccT = typename Traits::AccT;
	AccT total = Traits::zero( );
	while ( beg != end )
	{
		Policy<AccT, T>::accumulate( total, *beg );
		++beg;
	}

	return total;
}

int main( )
{
	int num[] = { 1, 2, 3, 4, 5 };

	std::cout << "모든 값의 곱을 출력 :"
		<< accum<int, SumPolicy>( &num[0], &num[5] )
		<< std::endl;
}