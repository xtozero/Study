template <typename T>
class List
{
public:
	void append( const T& );
	inline size_t length( ) const;
};

template <typename T>
class List<T*>
{
private:
	List<void*> impl;

public:
	void append( T* p )
	{
		impl.append( p );
	}

	size_t length( ) const
	{
		return impl.length( );
	}
};

template <>
class List<void*>
{
	void append( void* p );
	inline size_t length( ) const;
};