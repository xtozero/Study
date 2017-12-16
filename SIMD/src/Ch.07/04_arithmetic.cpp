/*--------------
클래스로 이루어져 있기 때문에 사칙연산의 사용도 간단하다.
다만 정수형 SIMD 명령어에 나눗셈 연산이 없어 마찬가지로 Vector 클래스도 나눗셈 연산을 지원하지 않는다.

연산기능			기호
덧셈				+, +=
뺄셈				-, -=
곱셈				*, *=
곱셈 상위 bit	mul_high
곱 합			mul_add
--------------*/

#include <emmintrin.h>
#include <dvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short pA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short pB[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short pR[8] = { 0 };

	__m128i m = _mm_load_si128( reinterpret_cast<__m128i*>( pA ) );

	Is16vec8 vA( m );
	Is16vec8 vB( 1, 1, 1, 1, 1, 1, 1, 1 );
	Is16vec8 vC = vA + vB;

	_mm_store_si128( reinterpret_cast<__m128i*>( pR ), vC );

	std::cout << "ADD : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	Is16vec8* pVA = reinterpret_cast<Is16vec8*>( pA );
	Is16vec8* pVB = reinterpret_cast<Is16vec8*>( pB );
	Is16vec8* pVR = reinterpret_cast<Is16vec8*>( pR );

	*pVR = *pVA + *pVB;

	std::cout << "ADD : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}