#include <cassert>

template <typename T>
class SArray
{
public:
	explicit SArray( size_t s ) : storage( new T[s] ), storage_size( s )
	{
		init( );
	}

	SArray( const SArray<T>& orig ) : storage( new T[orig.size( )] ), storage_size( orig.size( ) )
	{
		copy( orig );
	}

	SArray( )
	{
		delete[] storage;
	}

	SArray<T>& operator=( const SArray<T>& orig )
	{
		if ( &orig != this )
		{
			copy( orig );
		}

		return *this;
	}

	size_t size( ) const
	{
		return storage_size;
	}

	T operator[] ( size_t idx ) const
	{
		return storage[idx];
	}

	T& operator[] ( size_t idx )
	{
		return storage[idx];
	}

	SArray<T>& operator+= ( const SArray<T>& arg );
	SArray<T>& operator*= ( const SArray<T>& arg );
	SArray<T>& operator*= ( const T& arg );

protected:
	void init( )
	{
		for ( size_t idx = 0; idx < size( ); ++idx )
		{
			storage[idx] = T( );
		}
	}

	void copy( const SArray<T>& orig )
	{
		assert( size( ) == orig.size( ) );
		for ( size_t idx = 0; idx < size( ); ++idx )
		{
			storage[idx] = orig.storage[idx];
		}
	}

private:
	T* storage;
	size_t storage_size;
};

template <typename T>
SArray<T>& SArray<T>::operator+= ( const SArray<T>& arg )
{
	for ( size_t k = 0; k < arg.size( ); ++k )
	{
		(*this)[k] += arg[k];
	}
	return *this;
}

template <typename T>
SArray<T>& SArray<T>::operator*= ( const SArray<T>& arg )
{
	for ( size_t k = 0; k < arg.size( ); ++k )
	{
		( *this )[k] *= arg[k];
	}
	return *this;
}

template <typename T>
SArray<T>& SArray<T>::operator*= ( const T& arg )
{
	for ( size_t k = 0; k < arg.size( ); ++k )
	{
		( *this )[k] *= arg;
	}

	return *this;
}

int main( )
{
	SArray<double> x( 1000 ), y( 1000 );

	// 1.2 * x + x * y;
	SArray<double> tmp( x );
	tmp *= y;
	x *= 1.2;
	x += tmp;

	// 원하는 이상적인 방향
	for ( size_t idx = 0; idx < x.size( ); ++idx )
	{
		x[idx] = 1.2 * x[idx] + x[idx] * y[idx];
	}
}
