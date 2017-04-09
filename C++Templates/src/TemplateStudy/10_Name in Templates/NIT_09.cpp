#include <string>

template <typename T>
class X
{
public:
	typedef std::string Base;
	typedef int C;
	typedef short D;
};

template <typename T> // 1 ok
struct S : /*typename*/ X<T>::Base // 2 error 3�� ��Ģ X
{
	//	   3 error 3�� ��Ģ X	4 ok �ʿ��ϴ�.
	S( ) : /*typename*/ X<T>::Base( typename X<T>::Base( 0 ) ) {}
	/*typename*/ X<T> f( )	// 5 error 2�� ��Ģ X
	{
		typename X<T>::C* p;	// 6 ok
		// X<T>::D * q;			// ���ϱ��̴�.
		
		return X<T>( );
	}
	typename X<int>::C* s; // 7 ok �ٿ��� �ǰ� �� �ٿ��� �ȴ�.
};

struct U
{
	typename X<int>::C * pc; // 8 ok... gcc, vs community 2015������ ������ ����
};

int main( )
{
	S<int> s;
	s.f( );
}