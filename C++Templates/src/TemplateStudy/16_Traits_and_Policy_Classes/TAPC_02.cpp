#include <iostream>

template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
};

template<>
class AccumulationTraits<short>
{
public:
	typedef int AccT;
};

template <>
class AccumulationTraits<int>
{
public:
	typedef long AccT;
};

template <>
class AccumulationTraits<unsigned int>
{
public:
	typedef unsigned long AccT;
};

template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
};

template <typename T>
inline typename AccumulationTraits<T>::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AccumulationTraits<T>::AccT;
	AccT total = AccT( );
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}

int main( )
{
	int num[] = { 1, 2, 3, 4, 5 };

	std::cout << "Æò±Õ°ª :"
		<< accum( &num[0], &num[5] ) / 5
		<< std::endl;

	char name[] = "templates";
	int length = sizeof( name ) - 1;

	std::cout << "Æò±Õ°ª :"
		<< accum( &name[0], &name[length] ) / length
		<< std::endl;
}