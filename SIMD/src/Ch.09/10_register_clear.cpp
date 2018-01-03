/*--------------
AVX에서 모든 레지스터를 클리어하는 명령어가 추가됐다.
레지스터 하나를 클리어 할 경우에는 xor를 사용하면 되지만 모든 레지스터를 초기화 해야 한다면
64bit 환경에서 ymm0 ~ ymm15 까지 16번의 호출을 해야한다. 레지스터 클리어 명령어는 이런 불편을 해소해 준다.

사용 문법		연산 기능
vzeroall		ymm0 ~ ymm15 까지 레지스터를 모두 초기화한다.
vzeroupper		0 ~ 127bit는 그대로 두고 상위 비트를 초기화한다.
--------------*/

#include <iostream>

int main( )
{
	double Data[4] = { 1, 2, 3, 4 };
	double Ret0[4] = { 0 };
	double Ret7[4] = { 0 };
	double ZURet0[4] = { 0 };
	double ZURet7[4] = { 0 };
	double ZRet0[4] = { 0 };
	double ZRet7[4] = { 0 };

	__asm
	{
		vmovupd ymm0, Data
		vmovupd ymm7, ymm0
		vmovupd Ret0, ymm0
		vmovupd Ret7, ymm7

		vzeroupper

		vmovupd ZURet0, ymm0
		vmovupd ZURet7, ymm7

		vzeroall

		vmovupd ZRet0, ymm0
		vmovupd ZRet7, ymm7
	}

	std::cout << "Ret 0 : ";
	for ( double elem : Ret0 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Ret 7 : ";
	for ( double elem : Ret7 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl << std::endl;

	std::cout << "ZURet0 : ";
	for ( double elem : ZURet0 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "ZURet7 : ";
	for ( double elem : ZURet7 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl << std::endl;

	std::cout << "ZRet0 : ";
	for ( double elem : ZRet0 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "ZRet7 : ";
	for ( double elem : ZRet7 )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}