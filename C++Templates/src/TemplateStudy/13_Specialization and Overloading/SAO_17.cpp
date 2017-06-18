template <typename T>
class List
{
public:
	void append( const T& );
	inline size_t length( ) const;
};

// void* 형 멤버 접근 포인터에 대한 특수화
template <typename C>
class List<void* C::*>
{
public:
	typedef void* C::*ElementType;

	void append( ElementType pm );
	inline size_t length( ) const;
};

// 멤버 접근 포인터 포인터형을 위한 부분 특수화
// void* 형 멤버 접근 포인터는 이미 처리됐으므로 여기서는 제외된다.
// 이 부분 특수화는 두 템플릿 파라미터를 가지는데 기본 템플릿은 하나의 파라미터를 가진다.
template <typename T, typename C>
class List<T* C::*>
{
private:
	List<void* C::*> impl;

public:
	typedef T* C::*ElementType;

	void append( ElementType pm )
	{
		impl.append( ( void* C::* )pm );
	}

	inline size_t length( ) const
	{
		return impl.length( );
	}
};