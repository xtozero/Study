/*--------------
AVX는 실수형 연산만 가능하지만 정수형과 float, double 형 형변환 명령어는 지원하고 있다.

사용 문법					pack 사이즈			연산 기능
vcvtdq2ps	ymm1, ymm0		32bit integer		32bit integer형 정수 8개를 32bit float형 실수 8개로 변환
vcvtdq2pd	ymm1, xmm0		32bit integer		32bit integer형 정수 4개를 64bit double형 실수 4개로 변환
vcvtps2dq	ymm1, ymm0		32bit float			32bit float형 실수 8개를 32bit integer형 정수 8개로 변환 
--------------*/

#include <iostream>

int main( )
{
	int nSrc[8] = { 10, 20, 30, 40, 50, 60, 70, 80 };
	float fSrc[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

	int DstPStoI[8] = { 0 };
	float DstItoPS[8] = { 0 };
	double DstItoPD[4] = { 0 };

	__asm
	{
		vmovdqu ymm0, nSrc
		vcvtdq2ps ymm1, ymm0
		vmovups DstItoPS, ymm1

		vmovdqu xmm0, nSrc
		vcvtdq2pd ymm1, xmm0
		vmovupd DstItoPD, ymm1

		vmovups ymm0, fSrc
		vcvtps2dq ymm1, ymm0
		vmovdqu DstPStoI, ymm1
	}

	std::cout << "convert i to ps : ";
	for ( float elem : DstItoPS )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "convert i to pd : ";
	for ( double elem : DstItoPD )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "convert ps to i : ";
	for ( int elem : DstPStoI )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}