/*
template <typename T>
class Array
{
	// ...
};

// �Լ� ���ø��� �����ε��� �Ұ����ߴ� ������ �̷��� operator== �� �����ϸ�
// �ٸ� Ŭ������ ���� operator==�� ������ �� ������.
template <typename T>
bool operator==( const Array<T>& lhs, const Array<T>& rhs )
{
	// ...
}
*/

template <typename T>
class Array;

template <typename T>
bool ArrayAreEqual( const Array<T>& lhs, const Array<T>& rhs );

// ��ư-�ظ� Ʈ���� ����� ���
template <typename T>
class Array
{
public:
	friend bool operator==( const Array<T>& lhs, const Array<T>& rhs )
	{
		return ArrayAreEqual( lhs, rhs ); // example code
	}
};

// ������ ������ ���� �ʱ� ���� �Լ� ���� ��
template<typename T>
bool ArrayAreEqual( const Array<T>& lhs, const Array<T>& rhs )
{
	return false;
}

// ���Ե� ������ �Լ��� ����ȭ
class S {};

template <typename T>
class Wrapper
{
private:
	T object;
public:
	Wrapper( T obj ) : object( obj ) {}
	friend void f( const Wrapper<T>& arg ) {}
};

int main()
{
	S s;
	Wrapper<S> w( s );

	f( w );
	f( s ); // vs 2015 : ok , g++ : error
}