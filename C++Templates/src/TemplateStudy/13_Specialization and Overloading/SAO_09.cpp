#include <iostream>

// 기본 사용법
template <typename T>
class S
{
public:
	void info( )
	{
		std::cout << "generic (S<T>::info())" << std::endl;
	}
};

template <>
class S<void>
{
public:
	void msg( )
	{
		std::cout << "fully specialized (S<T>::msg())" << std::endl;
	}
};

// 기본 인자를 가진 템플릿 파라미터의 경우
template <typename T>
class Types
{
public:
	typedef int I;
};

template <typename T, typename U = typename Types<T>::I>
class FS;

template <>
class FS<void> 
{
public:
	void f( );
};

template <>
class FS<char, char>;

template <>
class S<char, 0>;		// error

// 클래스 템플릿 완전 특수화에서 멤버 함수의 정의
template<>

class S<char**>
{
public:
	void print( ) const;
};

void S<char**>::print( ) const
{
	std::cout << "Pointer to pointer to char" << std::endl;
}

int main( )
{
	FS<int>* pi;		// ok
	FS<int>	e1;			// error : 정의 없음
	FS<void>* pv;		// ok
	FS<void, int> sv;	// ok
	FS<void, char> e2;	// error : 정의 없음
	FS<char, char> e3;	// error : 정의 없음
}