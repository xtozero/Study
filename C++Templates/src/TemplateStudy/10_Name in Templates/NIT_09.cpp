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
struct S : /*typename*/ X<T>::Base // 2 error 3번 규칙 X
{
	//	   3 error 3번 규칙 X	4 ok 필요하다.
	S( ) : /*typename*/ X<T>::Base( typename X<T>::Base( 0 ) ) {}
	/*typename*/ X<T> f( )	// 5 error 2번 규칙 X
	{
		typename X<T>::C* p;	// 6 ok
		// X<T>::D * q;			// 곱하기이다.
		
		return X<T>( );
	}
	typename X<int>::C* s; // 7 ok 붙여도 되고 안 붙여도 된다.
};

struct U
{
	typename X<int>::C * pc; // 8 ok... gcc, vs community 2015에서도 컴파일 성공
};

int main( )
{
	S<int> s;
	s.f( );
}