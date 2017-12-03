/*--------------
64bit double형 실수 package를 정수로 변환하거나 반대의 연산을 수행한다.
64bit double형 실수를 32bit float형 실수로 변환하거나 반대의 연산을 수행한다.
64bit double형 실수 package는 2개의 데이터가 들어가므로 나머지 2개는 버리거나 0으로 채워준다.

명명법
_mm_cvt : 형변환 intrinsic 함수임을 의미
ss : 32bit float 형 스칼라
ps : 32bit float 형 pack
pd : 64bit double 형 pack
si32 : 32bit 정수형 스칼라

intrinsic 함수		SIMD 명령어		연산 방식
_mm_cvtpd_ps		CVTPD2PS		doble형 실수를 float형 실수로 변환
_mm_cvtps_pd		CVTPS2PD		float형 실수를 double형 실수로 변환
_mm_cvtepi32_pd		CVTDQ2PD		32bit integer형 정수를 doubleㅎㅇ 실수로 변환
_mm_cvtpd_epi32		CVTPD2DQ		double형 실수를 integer형 정수로 변환
_mm_cvtsd_si32		CVTSD2SI		하위 double형 실수 한개를 32bit integer형 정수로 변환
_mm_cvtsd_ss		CVTSD2SS		하위 double형 실수 한개를 float형 실수로 변환
_mm_cvtsi32_sd		CVTSI2SD		signed integer형 정수를 double형 실수로 변환
_mm_cvtss_sd		CVTSS2SD		하위 float형 실수를 double형 실수로 변환
_mm_cvttpd_epi32	CVTTPD2DQ		double형 실수를 signed integer형 정수로 변환
_mm_cvttsd_si32		CVTTSD2SI		하위 double형 실수를 signed integer형 정수로 변환
_mm_cvtpd_pi32		CVTPD2PI		2개의 double형 실수를 signed integer형 정수로 변환
_mm_cvttpd_pi32		CVTTPD2PI		2개의 double형 실수를 버림을 이용해서 signed integer형 정수로 변환
_mm_cvtpi32_pd		CVTPI2PD		2개의 signed integer형 정수를 double형 실수로 변환
_mm_cvtsd_f64		없음				첫 번째 변수 값을 double형 변수로 변환
--------------*/

#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) double DoubleA[2] = { 1.f, 2.f };
	alignas( 16 ) float FloatA[4] = { 3.f, 4.f, 5.f, 6.f };
	alignas( 16 ) int IntA[4] = { 7, 8, 9, 10 };

	alignas( 16 ) double DoubleR[2] = { -1, -1 };
	alignas( 16 ) float FloatR[4] = { -1, -1, -1, -1, };
	alignas( 16 ) int IntR[4] = { -1, -1, -1, -1 };

	__m128d dxmmA = _mm_load_pd( DoubleA );

	__m128 fxmmR = _mm_cvtpd_ps( dxmmA );

	_mm_store_ps( FloatR, fxmmR );

	std::cout << "Convert double to float : ";
	for ( float elem : FloatR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m128 fxmmA = _mm_load_ps( FloatA );

	__m128d dxmmR = _mm_cvtps_pd( fxmmA );

	_mm_store_pd( DoubleR, dxmmR );
	std::cout << "Convert float to double : ";
	for ( double elem : DoubleR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m128i ixmmR = _mm_cvtpd_epi32( dxmmA );

	_mm_store_si128( reinterpret_cast<__m128i*>( IntR ), ixmmR );
	std::cout << "Convert double to integer : ";
	for ( int elem : IntR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	__m128i ixmmA = _mm_load_si128( reinterpret_cast<__m128i*>( IntA ) );

	dxmmR = _mm_cvtepi32_pd( ixmmA );

	_mm_store_pd( DoubleR, dxmmR );
	std::cout << "Convert integer to double : ";
	for ( double elem : DoubleR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}