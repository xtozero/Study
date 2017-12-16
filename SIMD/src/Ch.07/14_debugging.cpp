/*--------------
outstream << 연산자
쉬운 디버깅과 구현을 위해 Vector 클래스에서는 outstream << 연산자를 지원한다.
사용을 위해서는 #define _ENABLE_VEC_DEBUG 코드를 추가해서 사용해야 한다.

[] 연산자
Pack에 있는 값을 읽거나 쓰기 위해 []연산자를 지원한다.
--------------*/
#define _ENABLE_VEC_DEBUG
#define DVEC_STD std::

#include <iostream>
#include <dvec.h>

int main( )
{
	// outstream << 연산자
	Is16vec8 A( 1, 2, 3, 4, 5, 6, 7, 8 );
	std::cout << A << std::endl;

	// [] 연산자
	short R = A[2];		// 6
	std::cout << R << std::endl;
}