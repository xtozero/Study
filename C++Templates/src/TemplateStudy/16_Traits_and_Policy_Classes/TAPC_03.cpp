#include <iostream>

template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
	static const AccT zero = 0;
};

template<>
class AccumulationTraits<short>
{
public:
	typedef int AccT;
	static const AccT zero = 0;
};

template <>
class AccumulationTraits<int>
{
public:
	typedef long AccT;
	static const AccT zero = 0;
};

template <>
class AccumulationTraits<unsigned int>
{
public:
	typedef unsigned long AccT;
	static const AccT zero = 0;
};

template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
	static const AccT zero;
};

const double AccumulationTraits<float>::zero = 0.0;

template <typename T>
inline typename AccumulationTraits<T>::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AccumulationTraits<T>::AccT;
	AccT total = AccumulationTraits<T>::zero;
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}

int main( )
{
	float num[] = { 1, 2, 3, 4, 5 };

	std::cout << "Æò±Õ°ª :"
		<< accum( &num[0], &num[5] ) / 5
		<< std::endl;
}