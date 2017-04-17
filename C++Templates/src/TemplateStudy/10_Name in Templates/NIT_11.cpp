#include <iostream>

class BX
{
public:
	void f( int ) { std::cout << "BX::f(int)" << std::endl; }
	void f( const char* ) { std::cout << "BX::f( const char* )" << std::endl; }
	void g( ) { std::cout << "BX::g()" << std::endl; }
};

class DX : private BX
{
public:
	using BX::f;
};

template <typename T>
class BXT
{
public:
	typedef T Mystery;
	template <typename U>
	struct Magic
	{
	};
};

template <typename T>
class DXTT : private BXT<T>
{
public:
	using typename BXT<T>::Mystery;		// typename을 빼면 gcc에서 컴파일 error VS 2015 community에서는 정상적으로 빌드 됨
	Mystery* p;
};

template <typename T>
class DXTM : private BXT<T>
{
public:
	// gcc 에서는 error vs 2015 community에서는 에러가 아님.
	using BXT<T>::template Magic;	// error 표준이 아님.
	Magic<T>* plink;				// error Magic은 알려진 템플릿이 아님.
};

int main( )
{
	DX dx;
	dx.f( 1 );

	DXTT<int> dxtt;
	int val = 10;
	dxtt.p = &val;
	std::cout << *dxtt.p << std::endl;

	DXTM<int> dxtm;
	BXT<int>::Magic<int> magic;
	dxtm.plink = &magic;
}