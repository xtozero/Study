#include <iostream>

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

template <typename T, typename AT = AccumulationTraits<T>>
class Accum
{
public:
	static typename AT::AccT accum( const T* beg, const T* end )
	{
		using AccT = typename AT::AccT;
		AccT total = AT::zero( );
		while ( beg != end )
		{
			total += *beg;
			++beg;
		}

		return total;
	}
};

template <typename T, typename AT = AccumulationTraits<T>>
inline typename AT::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AT::AccT;
	AccT total = AT::zero( );
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}

int main( )
{
	char name[] = "templates";
	int length = sizeof( name ) - 1;

	std::cout << "Æò±Õ°ª :"
		<< Accum<char>::accum( &name[0], &name[length] ) / length
		<< std::endl;

	float num[] = { 1, 2, 3, 4, 5 };

	std::cout << "Æò±Õ°ª :"
		<< accum<float, AccumulationTraits<int>>( &num[0], &num[5] ) / 5
		<< std::endl;
}