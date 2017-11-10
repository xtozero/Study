#include <iostream>

/*--------------
32bit integer형 정수, 32bit float형 실수, 64bit double형 실수간 형변환이 가능하다.

CVTDQ2PS
32bit integer형 정수 4개를 32bit float형 실수 4개로 변환
xmm0 |		4		|		3		|		2		|		1		|
xmm1 |		4.0		|		3.0		|		2.0		|		1.0		|

CVTDQ2DS
32bit integer형 정수 2개를 32bit double형 실수 2개로 변환
xmm0 |		4		|		3		|		2		|		1		|
xmm1 |				2.0				|				1.0				|

CVTPD2DQ
64bit double형 정수 2개를 32bit integer형 4개로 변환
xmm0 |		4		|		3		|		2		|		1		|
xmm1 |				2.0				|				1.0				|

사용문법						pack size							연산 기능
cvtdq2pd xmm1, xmm2/m64			32bit integer -> 64bit double		32bit integer형 정수 2개를 64bit double형 실수 2개로 변환
cvtdq2ps xmm1, xmm2/m128		32bit integer -> 32bit float		32bit integer형 정수 4개를 32bit float형 실수 4개로 변환
cvtpd2dq xmm1, xmm2/m128		64bit double -> 32bit integer		64bit double형 실수 2개를 32bit integer형 정수 2개로 변환
cvtpd2pi mm, xmm/m128			64bit double -> 32bit integer		64bit double형 실수 2개를 32bit integer형 정수 2개로 변환, mm 레지스터에 대입
cvtpd2ps xmm1, xmm2/m128		64bit double -> 32bit float			64bit double형 실수 2개를 32bit float형 실수 2개로 변환
cvtpi2pd xmm, mm/m64			32bit integer -> 64bit double		32bit integer형 정수 2개를 64bit double형 실수 2개로 변환
cvtpi2ps xmm, mm/m64			32bit integer -> 32bit float		32bit integer형 정수 2개를 32bit float형 실수 2개로 변환
cvtps2dq xmm1, xmm2/m128		32bit float -> 32bit integer		32bit float형 실수 4개를 32bit integer형 정수 4개로 변환
cvtps2pd xmm1, xmm2/m64			32bit float -> 64bit double			32bit float형 실수 2개를 64bit double형 실수 2개로 변환
cvtps2pi mm, xmm/m64			32bit float -> 32bit integer		32bit float형 실수 2개를 32bit integer형 정수 2개로 변환, mm 레지스터에 대입
cvtsd2si r32, xmm/m64			64bit double -> 32bit integer		64bit double형 실수 1개를 32bit intger형 정수 1개로 변환, 범용 레지스터에 대입
cvtsd2ss xmm1, xmm2/m64			64bit double -> 32bit float			64bit double형 실수 1개를 32bit float형 실수 1개로 변환
cvtsi2sd xmm, r/m32				32bit integer -> 64bit double		32bit integer형 정수 1개를 64bit double형 실수 1개로 변환
cvtsi2ss xmm, r/m32				32bit integer -> 32bit float		32bit integer형 정수 1개를 32bit float형 실수 1개로 변환
cvtss2sd xmm1, xmm2/m32			32bit float -> 64bit double			32bit float형 실수 1개를 64bit double형 실수 1개로 변환
cvtss2si r32, xmm/m32			32bit float -> 32bit integer		32bit float형 실수 1개를 32bit integer형 정수 1개로 변환, 범용 레지스터에 대입
cvttpd2dq xmm1, xmm2/m128		64bit double -> 32bit integer		64bit double형 실수 2개를 32bit integer형 정수 2개로 변환, 버림 처리
cvttpd2pi mm, xmm/m128			64bit double -> 32bit integer		64bit double형 실수 2개를 32bit integer형 정수 2개로 변환, mm 레지스터에 대입, 버림 처리
cvttps2dq xmm1, xmm2/m128		32bit float -> 32bit integer		32bit float형 실수 4개를 32bit integer형 정수 4개로 변환, 버림 처리
cvttps2pi mm, xmm/64			32bit float -> 32bit integer		32bit float형 실수 2개를 32bit integer형 정수 2개로 변환, 버림 처리
cvttsd2si r32, xmm/m64			64bit double -> 32bit integer		64bit double형 실수 1개를 32bit integer형 정수 1개로 변환, 범용 레지스터에 대입, 버림 처리
cvttss2si r32, xmm/m32			32bit float -> 32bit integer		32bit float형 실수 1개를 32bit integer형 정수 1개로 변환, 범용 레지스터에 대입, 버림 처리

dq => Double Quard (=4 Doubleword integer)
pd => Packed Double-precision
ps => Packed Single-precision
pi => Packed Integer (= 2 Doubleword integer)
sd => Scalar Double-precision
ss => Scalar Single-precision
cvtt => ConVerT with Truncation
--------------*/

int main( )
{
	alignas( 16 ) int IntSource[4] = { 1, 2, 3, 4 };
	alignas( 16 ) float FloatSource[4] = { 5.0, 6.0, 7.0, 8.0 };
	alignas( 16 ) double DoubleSource[2] = { 9.0, 10.0 };

	alignas( 16 ) float IntToFloat[4] = { 0 };
	alignas( 16 ) double IntToDouble[2] = { 0 };
	alignas( 16 ) int FloatToInt[4] = { 0 };
	alignas( 16 ) double FloatToDouble[2] = { 0 };
	alignas( 16 ) int DoubleToInt[4] = { 0 };
	alignas( 16 ) float DoubleToFloat[4] = { 0 };

	__asm
	{
		pushad
		movdqa xmm0, IntSource
		cvtdq2ps xmm1, xmm0
		cvtdq2pd xmm2, xmm0
		
		movaps xmm0, FloatSource
		cvtps2dq xmm3, xmm0
		cvtps2pd xmm4, xmm0

		movapd xmm0, DoubleSource
		cvtpd2dq xmm5, xmm0
		cvtpd2ps xmm6, xmm0

		movaps IntToFloat, xmm1
		movaps IntToDouble, xmm2

		movdqa FloatToInt, xmm3
		movapd FloatToDouble, xmm4

		movdqa DoubleToInt, xmm5
		movaps DoubleToFloat, xmm6

		popad
	}

	std::cout << "IntToFloat : ";
	for ( float elem : IntToFloat )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "IntToDouble : ";
	for ( double elem : IntToDouble )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "FloatToInt : ";
	for ( int elem : FloatToInt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "FloatToDouble : ";
	for ( double elem : FloatToDouble )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "DoubleToInt : ";
	for ( int elem : DoubleToInt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "DoubleToFloat : ";
	for ( float elem : DoubleToFloat )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}