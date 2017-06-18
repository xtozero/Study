#include <iostream>
#include <memory>

template <typename T>
class Array
{
private:
	T* data = nullptr;
	size_t	m_size;

public:
	Array( size_t size )
	{
		m_size = size;
		data = new T[size];
		memset( data, 0, sizeof( T ) * size );
	}

	~Array( )
	{
		delete []data;
	}

	void exchange_with( Array<T>* args )
	{
		T* tmp = data;
		data = args->data;
		args->data = tmp;
	}

	T& operator[]( size_t index )
	{
		return data[index];
	}

	size_t size( ) { return m_size; }
};

struct S
{
	int x = 0;
};

template <typename T>
inline void quick_exchange( T* a, T* b )
{
	T tmp( *a );
	*a = *b;
	*b = tmp;
}

template <typename T>
inline void quick_exchange( Array<T>* a, Array<T>* b )
{
	a->exchange_with( b );
}

template <typename T>
inline void exchange( T* lhs, T* rhs )
{
	T tmp( *a );
	*a = *b;
	*b = tmp;
}

template <typename T>
inline void exchange( Array<T>* a, Array<T>* b )
{
	T* p = &( *a )[0];
	T* q = &( *b )[0];

	for ( size_t k = a->size( ); k-- != 0; )
	{
		exchange( p++, q++ );
	}
}

int main( )
{
	S s1, s2;

	Array<int> a1( 5 );
	Array<int> a2( 5 );

	int* p = &a1[0];
	int* q = &s1.x;

	std::cout << *p << ", " << *q << std::endl;

	a1[0] = s1.x = 1;
	a2[0] = s2.x = 2;

	quick_exchange( &a1, &a2 );
	quick_exchange( &s1, &s2 );

	std::cout << *p << ", " << *q << std::endl;
}