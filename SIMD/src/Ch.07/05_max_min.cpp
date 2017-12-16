/*--------------
C++ 에서는 Min, Max를 구하는 연산자나 명령어가 없어 함수 형태로 제공한다.
따라서 Vector 클래스에도 연산자가 아닌 함수를 지원한다.

inline Is16vec8 simd_max( const Is16vec8& A, const Is16vec8& B )
{ return _mm_max_epi16( a, b ); }
inline Is16vec8 simd_min( const Is16vec8& A, const Is16vec8& B )
{ return _mm_min_epi16( a, b ); }

특별한 코드 없이 intrinsic 함수를 호출한 것을 알 수 있다.
참고할 점은 32bit integer형 정수 package에 대한 Min, Max 연산은 SEE4부터 지원한다.

연산 기능		연산 기호
Max값 연산		simd_max
Min값 연산		simd_min
--------------*/

#include <emmintrin.h>
#include <dvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short pA[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	alignas( 16 ) short pB[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short pR[8] = { 0 };

	Is16vec8* pVA = (Is16vec8*)pA;
	Is16vec8* pVB = (Is16vec8*)pB;
	Is16vec8* pVR = (Is16vec8*)pR;

	*pVR = simd_max( *pVA, *pVB );

	std::cout << "Max : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = simd_min( *pVA, *pVB );

	std::cout << "Min : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}