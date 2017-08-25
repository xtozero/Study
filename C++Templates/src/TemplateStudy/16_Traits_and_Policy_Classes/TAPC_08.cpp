#include <iostream>
#include <iterator>

template <typename Iter>
inline typename std::iterator_traits<Iter>::value_type accum( Iter start, Iter end )
{
	using VT = typename std::iterator_traits<Iter>::value_type;

	VT total = VT( );
	while ( start != end )
	{
		total += *start;
		++start;
	}

	return total;
}

int main( )
{
	int num[] = { 1, 2, 3, 4, 5 };

	std::cout << "Æò±Õ°ª :"
		<< accum( &num[0], &num[5] ) / 5
		<< std::endl;
}