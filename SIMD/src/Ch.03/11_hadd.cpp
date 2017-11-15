#include <iostream>

/*--------------
2개의 128bit xmm레지스터를 입력받아 좌우에 있는 값을 더하여 결과를 얻어온다.
기존에 병렬 수직 방향으로 합을 구하던 것에서 수평방향으로 합을 구할 수 있도록 하는 명령어이다.

첫 번째 레지스터의 1,2 pack을 더해 dest의 첫 번째 pack에 넣고 첫 번째 레지스터의 3, 4번 pack을 합쳐서 dest의 2번째 pack에 넣는다.
두 번째 레지스터의 1,2 pack을 더해 dest의 세 번째 pack에 넣고 두 번째 레지스터의 3, 4번 pack을 합쳐서 dest의 4번째 pack에 넣는다.

Packed Horizontal Add

사용문법					pack size				연산 기능
haddps					32bit float				32bit float형 실수 8개에 대한 수평 덧셈 값을 구한다.
haddpd					64bit double			64bit double형 실수 4개에 대한 수평 덧셈 값을 구한다.
--------------*/

int main( )
{
	float SrcA[4] = { 1.f, 2.f, 3.f, 4.f };
	float SrcB[4] = { 5.f, 6.f, 7.f, 8.f };

	float Result[4] = { 0.f };

	__asm
	{
		movups xmm0, SrcA
		movups xmm1, SrcB

		haddps xmm0, xmm1	// 8 + 7, 6 + 5, 4 + 3, 2 + 1

		movups Result, xmm0
	}

	std::cout << "HADDPS : ";
	for ( float elem : Result )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}