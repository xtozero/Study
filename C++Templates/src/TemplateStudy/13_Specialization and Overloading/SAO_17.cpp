template <typename T>
class List
{
public:
	void append( const T& );
	inline size_t length( ) const;
};

// void* �� ��� ���� �����Ϳ� ���� Ư��ȭ
template <typename C>
class List<void* C::*>
{
public:
	typedef void* C::*ElementType;

	void append( ElementType pm );
	inline size_t length( ) const;
};

// ��� ���� ������ ���������� ���� �κ� Ư��ȭ
// void* �� ��� ���� �����ʹ� �̹� ó�������Ƿ� ���⼭�� ���ܵȴ�.
// �� �κ� Ư��ȭ�� �� ���ø� �Ķ���͸� �����µ� �⺻ ���ø��� �ϳ��� �Ķ���͸� ������.
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