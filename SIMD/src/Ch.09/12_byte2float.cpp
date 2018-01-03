/*--------------
4byte를 읽어 4개의 integer로 변환하여 xmm0과 xmm1에 입력하고 
2개의 127bit 값을 다시 ymm0 레지스터에 입력하여 integer 값을 float 형으로 반환하는 예제이다.
xmm 레지스터는 ymm 레지스터의 subset인 점에 주의해야 한다.
xmm0에 값을 쓴다음 ymm0에 값을 다시 쓰면 xmm0에 있는 값은 사라진다.
--------------*/

#include <iostream>

int main( )
{
	char nSrc[20] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	float DstPS[8] = { 0 };

	__asm
	{
		vxorps ymm0, ymm0, ymm0

		;pmovzebd - Packed Move with Zero Extend
		vpmovzxbd xmm1, [nSrc]				;byte를 int로 확장
		vpmovzxbd xmm2, [nSrc+4]

		vinsertf128 ymm0, ymm0, xmm1, 0
		vinsertf128 ymm0, ymm0, xmm2, 1

		vcvtdq2ps ymm0, ymm0
		vmovups DstPS, ymm0
	}

	std::cout << std::fixed;
	for ( float elem : DstPS )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}
