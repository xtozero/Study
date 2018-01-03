/*--------------
하나의 pack을 insert하는 명령어는 SSE에서도 존재하였다.
AVX에서는 하나의 pack이 아니라 128bit 데이터를 256bit 레지스터의 절반에 입력하는 명령어가 추가되었다.

사용 문법								pack 사이즈				연산 기능
vinsertf128 ymm1, ymm0, xmm1, imm		128bit SIMD				ymm0의 값을 ymm1에 복사하고 xmm1에 있는 값을 imm이 지정하는 위치에 넣는다.

ymm0	|	0	|	0	|	0	|	0	|	4	|	3	|	2	|	1	|

xmm2,1	|	8	|	7	|	6	|	5	|

ymm0	|	8	|	7	|	6	|	5	|	4	|	3	|	2	|	1	|

imm이 0 이면 하위 128bit 위치, 1 이면 상위 128bit 위치에 입력한다.
--------------*/

#include <iostream>

int main( )
{
	float fSrc[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };

	float DInsert0[8] = { 0 };
	float DInsert1[8] = { 0 };

	__asm
	{
		vmovups xmm1, [fSrc]
		vmovups xmm2, [fSrc+16]
		vxorps ymm0, ymm0, ymm0

		vinsertf128 ymm0, ymm0, xmm1, 0
		vmovups DInsert0, ymm0

		vinsertf128 ymm0, ymm0, xmm2, 1
		vmovups DInsert1, ymm0
	}

	for ( float elem : DInsert0 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	for ( float elem : DInsert1 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}