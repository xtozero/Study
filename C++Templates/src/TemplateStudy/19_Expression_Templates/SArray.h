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
SArray<T> operator+ ( const SArray<T>& lhs, const SArray<T>& rhs )
{
	SArray<T> result( lhs.size( ) );
	for ( size_t k = 0; k < lhs.size( ); ++k )
	{
		result[k] = lhs[k] + rhs[k];
	}
	return result;
}

template <typename T>
SArray<T> operator* ( const SArray<T>& lhs, const SArray<T>& rhs )
{
	SArray<T> result( lhs.size( ) );
	for ( size_t k = 0; k < lhs.size( ); ++k )
	{
		result[k] = lhs[k] * rhs[k];
	}
	return result;
}

template <typename T>
SArray<T> operator* ( const T& lhs, const SArray<T>& rhs )
{
	SArray<T> result( rhs.size( ) );
	for ( size_t k = 0; k < rhs.size( ); ++k )
	{
		result[k] = lhs * rhs[k];
	}
	return result;
}
