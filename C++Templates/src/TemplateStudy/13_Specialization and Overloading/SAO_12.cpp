#include <iostream>

template <typename T>	// 1
int f( T )
{
	return 1;
}

template <typename T>	// 2
int f( T* )
{
	return 2;
}

template<> int f( int )
{
	return 3;
}

template<> int f( int* )
{
	return 4;
}

// 전체 함수 템플릿 특수화에서의 기본 인자
template <typename T>
int f( T, T x = 42 )
{
	return x;
}

//template <>
//int f( int, int = 35 ) // error : 전체 함수 템플릿 특수화에서 기본 인자를 사용할 수 없다.
//{
//	return 0;
//}

template <typename T>
int g( T, T x = 42 )
{
	return x;
}

template <>
int g( int, int y )
{
	return y / 2;
}

int main( )
{
	std::cout << g( 0 ) << std::endl;
}