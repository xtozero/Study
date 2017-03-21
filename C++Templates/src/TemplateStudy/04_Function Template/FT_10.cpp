#include <iostream>
#include <cstring>
#include <cstdio>

template <typename T>
const T& new_max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

const char* new_max( const char* lhs, const char* rhs )
{
	return strcmp( lhs, rhs ) < 0 ? rhs : lhs;
}

template <typename T>
const T& new_max( const T& first, const T& second, const T& third )
{
	return new_max( new_max( first, second ), third );
}

int main( )
{
	// �Լ� ���ø� �����ε��� ����ġ ���ϰ� �����ϴ� ���
	// VS2015������ �� �����ϵǳ� gcc������ ũ���ð� ����.
	const char* st1 = "Template";
	const char* st2 = "Study";
	const char* st3 = "Successfull";
	std::cout << new_max( st1, st2, st2 ) << std::endl;
}