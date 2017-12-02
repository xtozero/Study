/*--------------
__m128 r = _mm_shuffle_ps( __m128 a, __m128 b, unsinged int imm8 )

_MM_SHUFFLE(z, y, x, w)
어셈블리 명령어에는 없는 매크로 함수 상수로 bit 조합해서 사용하던 것을 위치지정 숫자로 지정할 수 있도록 도와준다.
w 인자에 있는 수를 이용해 a에 있는 4개의 pakc중 하나를 선택하여 0~31bit 위치에 값을 복사한다.
x 인자에 있는 수를 이용해 a에 있는 4개의 pakc중 하나를 선택하여 32~63bit 위치에 값을 복사한다.
y 인자에 있는 수를 이용해 b에 있는 4개의 pakc중 하나를 선택하여 64~95bit 위치에 값을 복사한다.
z 인자에 있는 수를 이용해 b에 있는 4개의 pakc중 하나를 선택하여 96~127bit 위치에 값을 복사한다.

__m128 r = _mm_unpacklo_ps( __m128 a, __m128 b )

__m128 r = _mm_unpackhi_ps( __m128 a, __m128 b )

intrinsic			SIMD 연산자		Operation
_mm_shffle_ps		SHUFPS			32bit 실수형 4개를 조합한다.
_mm_unpackhi_ps		UNPCKHPS		a와 b 상위 64bit 값을 교차 조합한다.
_mm_unpacklo_ps		UNPCKLPS		a와 b 하위 64bit 값을 교차 조합한다.
_mm_move_ss			MOVSS			a와 b 상위 64bit 값을 조합한다.
_mm_movehl_ps		MOVHLPS			하위 32bit를 복사하고 나머지 값 전달
_mm_movelh_ps		MOVLHPS			a와 b 하위 64bit 값을 조합한다.
_mm_movemask_ps		MOVEMSKPS		4개의 bit 마스크를 만든다.
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float A[4] = { 1.0, 2.0, 3.0, 4.0 };
	alignas( 16 ) float B[4] = { 5.0, 6.0, 7.0, 8.0 };
	
	alignas( 16 ) float R[4] = { 0 };

	__m128 xmmA = _mm_load_ps( A );
	__m128 xmmB = _mm_load_ps( B );

	__m128 xmmR = _mm_shuffle_ps( xmmA, xmmB, _MM_SHUFFLE( 1, 0, 3, 2 ) );

	_mm_store_ps( R, xmmR );
	std::cout << "Shuffle : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_unpacklo_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );
	std::cout << "unpack low : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	xmmR = _mm_unpackhi_ps( xmmA, xmmB );

	_mm_store_ps( R, xmmR );
	std::cout << "unpack high : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}