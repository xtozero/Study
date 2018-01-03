/*--------------
실수형 연산에서 sqrt와 같은 연산을 math 라이브러리를 이용하여 소프트웨어 연산을 사용하면 많은 시간을 소비할 수 있다.
SSE와 AVX는 하드웨어적으로 sqrt를 지원하여 빠르게 연산할 수 있다.

사용 문법				pack 사이즈			연산 기능
vsqrtps ymm1, ymm0		32bit float			32bit float형 실수 8개에 대한 제곱근을 구한다.
vrcpps ymm1, ymm0		32bit float			32bit float형 실수 8개에 대한 역수를 구한다.
vrsqrtps ymm1, ymm0		32bit float			32bit float형 실수 8개에 대한 제곱근의 역수를 구한다.
--------------*/

#include <iostream>

int main( )
{
	alignas( 32 ) float Src[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

	alignas( 32 ) float DstSqrt[8] = { 0.f };
	alignas( 32 ) float DstRcp[8] = { 0.f };
	alignas( 32 ) float DstRsqrt[8] = { 0.f };

	__asm
	{
		vmovaps ymm0, Src

		vsqrtps ymm1, ymm0
		vmovaps DstSqrt, ymm1

		vrcpps ymm1, ymm0
		vmovaps DstRcp, ymm1

		vrsqrtps ymm1, ymm0
		vmovaps DstRsqrt, ymm1
	}

	std::cout << "Rcp : ";
	for ( float elem : DstRcp )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Sqrt : ";
	for ( float elem : DstSqrt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Rsqrt : ";
	for ( float elem : DstRsqrt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}