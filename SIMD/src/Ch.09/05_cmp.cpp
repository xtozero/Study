/*--------------
float형 8개 또는 double형 4개를 가진 vector 데이터에 대하여 대소비교를 수행한다.
비교 연산의 조건을 충족하면 타겟이 되는 package에 ffffffff 값을 채워 넣는다.
--------------*/

#include <iostream>

int main( )
{
	float SrcA[8] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f };
	float SrcB[8] = { 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f };

	float DstEq[8] = { 0 };
	float DstLt[8] = { 0 };
	float DstLe[8] = { 0 };
	float DstGt[8] = { 0 };
	float DstGe[8] = { 0 };

	__asm
	{
		vmovups ymm0, SrcA
		vmovups ymm1, SrcB

		vcmpeqps ymm2, ymm1, ymm0
		vmovups DstEq, ymm2

		vcmpltps ymm2, ymm2, ymm0
		vmovups DstLt, ymm2

		vcmpleps ymm2, ymm1, ymm0
		vmovups DstLe, ymm2

		vcmpgtps ymm2, ymm1, ymm0
		vmovups DstGt, ymm2

		vcmpgeps ymm2, ymm1, ymm0
		vmovups DstGe, ymm2
	}

	std::cout << "Equal : ";
	for ( float elem : DstEq )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Less Than : ";
	for ( float elem : DstLt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Less Equal : ";
	for ( float elem : DstLe )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Greater Than : ";
	for ( float elem : DstGt )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	std::cout << "Greater Equal : ";
	for ( float elem : DstGe )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}