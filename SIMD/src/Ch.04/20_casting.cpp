/*--------------
__m128i r = _mm_cvtepi32_ps( __m128i a )
__m128i r = _mm_cvtps_epi32( __m128i a )

intrinsic				SIMD 연산자		Operation
_mm_cvtsi64_sd			CVTSI2SD		64bit 정수와 __m128d 조합
_mm_cvtsd_si64			CVTSD2SI		__m128d에서 하위 64bit 정수 변환
_mm_cvttsd_si64			CVTTSD2SI		__m128d에서 하위 64bit인자를 버림에 의한 변환
_mm_cvtepi32_ps			없음				정수에서 실수 변환
_mm_cvtps_epi32			없음				실수에서 정수 변환
_mm_cvttps_epi32		없음				실수에서 정수 변환 끝자리 버림
_mm_cvtsi32_si128		MOVD			32bit 정수를 128bit 데이터에 대입 나머지 0으로 초기화
_mm_cvtsi64_si128		MOVQ			64bit 정수를 128bit 데이터에 대입 나머지 0으로 초기화
_mm_cvtsi128_si32		MOVD			128bit 값 중 하위 32bit를 integer 형으로 리턴
_mm_cvtsi128_si64		MOVQ			128bit 값 중 하위 64bit를 __int64 형으로 리턴
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float FloatA[4] = { 1.0, 2.0, 3.0, 4.0 };
	alignas( 16 ) int IntR[4] = { 0 };

	alignas( 16 ) int intA[4] = { 1.0, 2.0, 3.0, 4.0 };
	alignas( 16 ) float FloatR[4] = { 0 };

	__m128 xmmA = _mm_load_ps( FloatA );

	__m128i ixmmR = _mm_cvtps_epi32( xmmA );

	_mm_store_si128( reinterpret_cast<__m128i*>( IntR ), ixmmR );

	std::cout << "Convert Float to integer : ";
	for ( int elem : IntR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m128i ixmmA = _mm_load_si128( reinterpret_cast<__m128i*>( intA ) );

	__m128 xmmR = _mm_cvtepi32_ps( ixmmA );

	_mm_store_ps( FloatR, xmmR );

	std::cout << "Convert integer to Float : ";
	for ( float elem : FloatR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}