/*--------------
사칙 연산도 SSE 명령어에 v 접두사가 붙고 3항 연산으로 변화되었다.
--------------*/

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float DstAdd[8] = { 0 };
	float DstSub[8] = { 0 };
	float DstMul[8] = { 0 };
	float DstDiv[8] = { 0 };

	__asm
	{
		vmovups ymm0, SrcA
		vmovups ymm1, SrcB

		vaddps ymm2, ymm0, ymm1
		vmovups DstAdd, ymm2

		vsubps ymm2, ymm0, ymm1
		vmovups DstSub, ymm2

		vmulps ymm2, ymm0, ymm1
		vmovups DstMul, ymm2

		vdivps ymm2, ymm0, ymm1
		vmovups DstDiv, ymm2
	}

	std::cout << "Add : ";
	for ( float elem : DstAdd )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Sub : ";
	for ( float elem : DstSub )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Mul : ";
	for ( float elem : DstMul )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Div : ";
	for ( float elem : DstDiv )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}