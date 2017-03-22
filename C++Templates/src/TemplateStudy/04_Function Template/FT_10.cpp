#include <iostream>
#include <cstring>
#include <cstdio>

template <typename T>
const T& new_max( const T& lhs, const T& rhs )
{
	std::cout << "new_max( const T& lhs, const T& rhs )" << std::endl;
	return lhs < rhs ? rhs : lhs;
}

const char* new_max( const char* lhs, const char* rhs )
{
	std::cout << "const char* new_max( const char* lhs, const char* rhs )" << std::endl;
	return strcmp( lhs, rhs ) < 0 ? rhs : lhs;
}

template <typename T>
const T& new_max( const T& first, const T& second, const T& third )
{
	std::cout << "new_max( const T& first, const T& second, const T& third )" << std::endl;
	return new_max( new_max( first, second ), third );
}

void foo( const int* a )
{
	std::cout << "foo( const int* a )" << std::endl;
}

void foo( const int*& a )
{
	std::cout << "foo( const int*& a )" << std::endl;
}

int main( )
{
	// 함수 템플릿 오버로딩이 예상치 못하게 동작하는 경우
	// VS2015에서는 잘 컴파일되나 gcc에서는 크래시가 난다.
	const char* st1 = "Template";
	const char* st2 = "Study";
	const char* st3 = "Successfull";
	std::cout << new_max( st1, st2, st2 ) << std::endl;

	const int* a = nullptr;
	const int*& b = a;
	foo( b );
}