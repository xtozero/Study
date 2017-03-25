#include <vector>

template <typename T>
class List
{
public:
	template <typename T2>
	List( const List<T2>& list );
};

template <typename T>
template <typename T2>
List<T>::List( const List<T2>& list )
{
	// ...
}

template <typename T>
union AllocChuck
{
	T object;
	unsigned char bytes[sizeof( T )];
};

template <typename T>
void report_top( const std::vector<T>&, int number = 10 )
{
	// ...
}

template <typename T>
void fill( const std::vector<T>&, const T& = T( ) )
{
	// ...
}

template <int N>
class CupBoard
{
	void open( );
	class Shelf;
	static double total_weight;
};

template <int N>
void CupBoard<N>::open( )
{
	// ...
}

template <int N>
class CupBoard<N>::Shelf
{
	// ...
};

template <int N>
double CupBoard<N>::total_weight = 0.0;

class Value
{
public:
	Value( int ) {}		// 기본 생성자 없음
};

int main( )
{
	Value zero( 0 );
	std::vector<Value> v;

	fill( v, zero ); // T() 가 사용되지 않음.
	// fill( v ); error T() 가 사용됨.
}