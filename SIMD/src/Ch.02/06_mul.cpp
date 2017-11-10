#include <iostream>

/*--------------
16bit 변수 2개를 받아 곱셈 연산을 하면 값이 커지므로 오버플로우가 발생하게 된다.
완전한 결과값을 얻기 위해서 곱셈 연산의 변수 사이즈는 다음과 같이 지정되어야 한다.
16bit * 16bit = 32bit 결과 값
pmullw, pmulld 함수는 결과 값을 절반의 하위 주소 공간의 값을 가져오고 상위 주소 공간의 값은 버리게 된다.
만약 오버플로우가 나지 않는다면 pmullw, pmuld는 단순한 곱셈 연산과 같다고 생각하면 된다.

사용문법						pack size			연산 기능
pmullw xmm1, xmm2/m128			16bit short			16bit short형 정수 8개의 곱을 수행한다.
pmulld xmm1, xmm2/m128			32bit interger		32bit integer형 정수 4개의 곱을 수행한다.

절반의 상위 주소는 pmulhw, pmulhd를 이용해 얻을 수 있다.

사용문법						pack size			연산 기능
pmulhw xmm1, xmm2/m128			16bit short			16bit short형 정수 8개의 곱의 16bit 이상의 값
pmulhd xmm1, xmm2/m128			32bit interger		32bit integer형 정수 4개의 곱의 32bit 이상의 값

SIMD 정수 연산은 나눗셈을 지원하지 않는다.
--------------*/

int main( )
{
	short ShortArrayA[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	short ShortArrayB[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
	short ShortResult[8] = { 0 };

	__asm
	{
		pushad
		movdqu xmm0, ShortArrayA
		movdqu xmm1, ShortArrayB
		pmullw xmm0, xmm1
		movdqu ShortResult, xmm0
		popad
	}

	std::cout << "MulResult : ";
	for ( short elem : ShortResult )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}