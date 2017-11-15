#include <iostream>

/*--------------
두 XMM 레지스터에 각각의 pack안의 값을 평균하여 넣어준다.

사용문법							pack size			연산 기능
pavgb xmm1, xmm2/m128			8bit byte			8bit byte형 정수 16개를 가진 레지스터 2개의 평균값을 구한다.
pavgw xmm1, xmm2/m128			16bit short			16bit short형 정수 8개를 가진 레지스터 2개의 평균값을 구한다.
--------------*/

int main( )
{
	short ValueA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	short ValueB[8] = { 0 };
	short Result[8] = { 0 };

	__asm
	{
		pushad
		movdqu xmm0, ValueA
		movdqu xmm1, ValueB
		pavgw xmm0, xmm1
		movdqu Result, xmm0
		popad
	}

	std::cout << "Result : ";
	for ( short elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}