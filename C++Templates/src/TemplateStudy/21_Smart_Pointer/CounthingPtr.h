#include <cassert>
#include <cstddef>

class StandardObjectPolicy
{
public:
	template <typename T> void dispose( T* object )
	{
		delete object;
	}
};

class StandardArrayPolicy
{
public:
	template <typename T> void dispose( T* object )
	{
		delete[] object;
	}
};

class SimpleReferenceCount
{
public:
	template <typename T> 
	void init( T* )
	{
		counter = new size_t;
		*counter = 1;
	}

	template <typename T>
	void dispose( T* )
	{
		delete counter;
	}

	template <typename T>
	void increment( T* )
	{
		++*counter;
	}

	template <typename T>
	void decrement( T* )
	{
		--*counter;
	}

	template <typename T>
	bool is_zero( T* )
	{
		return *counter == 0;
	}

private:
	size_t* counter = nullptr;
};


template <typename ObjectT, typename CountT, CountT ObjectT::*CountP>
class MemberReferenceCount
{
public:
	template <typename T>
	void init( T* object )
	{
		object->*CountP = 1;
	}

	template <typename T>
	void dispose( T* object )
	{
	}

	template <typename T>
	void increment( T* object )
	{
		++object->*CountP;
	}

	template <typename T>
	void decrement( T* object )
	{
		--object->*CountP;
	}

	template <typename T>
	bool is_zero( T* object )
	{
		return object->*CountP == 0;
	}
};

template <typename T, 
	typename CounterPolicy = SimpleReferenceCount,
	typename ObjectPolicy = StandardObjectPolicy>
class CountingPtr : private CounterPolicy, private ObjectPolicy
{
private:
	using CP = CounterPolicy;
	using OP = ObjectPolicy;

	T* object_pointed_to = nullptr;
public:
	explicit CountingPtr( T* p )
	{
		init( p ); // 포인터로 초기화
	}

	CountingPtr( const CountingPtr<T, CP, OP>& cp ) :
		CP( static_cast<const CP&>( cp ) ),
		OP( static_cast<const OP&>( cp ) )
	{
		attach( cp ); // 포인터를 복사하고 카운터를 증가시킴
	}

	~CountingPtr( )
	{
		detach( );
	}

	CountingPtr<T, CP, OP>& operator= ( T* p )
	{
		assert( p != object_pointed_to );
		detach( );
		init( p );
		return *this;
	}

	CountingPtr<T, CP, OP>& operator=( const CountingPtr<T, CP, OP>& cp )
	{
		if ( this->object_pointed_to != cp.object_pointed_to )
		{
			detach( );
			CP::operator=( static_cast<const CP&>( cp ) );
			OP::operator=( static_cast<const OP&>( cp ) );
			attach( cp )
		}

		return *this;
	}


	T* operator->( ) const
	{
		return object_pointed_to;
	}

	T& operator*( ) const
	{
		return *object_pointed_to;
	}

private:
	void init( T* p )
	{
		if ( p != nullptr )
		{
			CounterPolicy::init( p );
		}
		object_pointed_to = p;
	}

	void attach( const CountingPtr<T, CP, OP>& cp )
	{
		object_pointed_to = cp.object_pointed_to;
		if ( cp.object_pointed_to != nullptr )
		{
			CounterPolicy::increment( cp.object_pointed_to );
		}
	}

	void detach( )
	{
		if ( object_pointed_to != nullptr )
		{
			CounterPolicy::decrement( object_pointed_to );
			if ( CounterPolicy::is_zero( object_pointed_to ) )
			{
				CounterPolicy::dispose( object_pointed_to );
				ObjectPolicy::dispose( object_pointed_to );
			}
		}
	}
};