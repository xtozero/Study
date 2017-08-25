#include <cstring>
#include <type_traits>

template <typename T>
class RParam
{
public:
	using Type = typename std::conditional<sizeof( T ) <= 2 * sizeof( void* ), T, const T&>::type;
};

template <typename T, bool Bitwise>
class BitOrClassCSM;

template <typename T>
class BitOrClassCSM<T, false>
{
public:
	static void copy( typename RParam<T>::Type src, T* dat )
	{
		*dst = src;
	}

	static void copy_n( const T* src, T* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k)
			dst[k ) = src[k];
	}

	static void copy_init( typename RParam<T>::Type src, void* dst )
	{
		::new( dst ) T( *src );
	}

	static void copy_init_n( const T* src, void* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
			::new( (void*)((T*)dst+k) ) T( src[k] );
	}

	static void swap( T* a, T* b )
	{
		T tmp( *a );
		*a = *b;
		*b = tmp;
	}

	static void swap( T* a, T* b, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
		{
			T tmp( a[k] );
			a[k] = b[k];
			b[k] = tmp;
		}
	}

	static void move( T* src, T* dst )
	{
		*dst = *src;
		src->~T( );
	}

	static void move_n( T* src, T* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
		{
			dst[k] = src[k];
			src[k].~T( );
		}
	}

	static void move_init( T* src, T* dst )
	{
		::new( dst ) T( *src );
		src->~T( );
	}

	static void move_init_n( const T* src, T* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
		{
			::new( (void*)( (T*)dst + k ) ) T( src[k] );
			src[k].~T( );
		}
	}
};

template <typename T>
class BitOrClassCSM<T, true> : public BitOrClassCSM<T, false>
{
public:
	static void copy_n( const T* src, T* dst, size_t n )
	{
		std::memcpy( (void*)dst, (void*)src, n * sizeof( T ) );
	}

	static void copy_init_n( const T* src, T* dst, size_t n )
	{
		std::memcpy( dst, (void*)src, n * sizeof( T ) );
	}

	static void move_n( T* src, T* dst, size_t n )
	{
		std::memcpy( (void*)dst, (void*)src, n * sizeof( T ) );
	}

	static void move_init_n( const T* src, T* dst, size_t n )
	{
		std::memcpy( dst, (void*)src, n * sizeof( T ) );
	}
};
