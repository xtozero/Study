﻿/*--------------
XMM 레지스터를 사용한 후에는 XMM상태 레지스터를 클리어해야 한다.

intrinsic 함수 : _mm_empty
SIMD 명령어 : emms

emms를 사용하는 것은 새 컨텐츠를 수용하기 위해서 컨테이너를 비우는 것과 같다.
emms 명령어는 mmx 레지스터를 비우고 부동 소수점 태그 워드의 값을 비어 있게 설정한다.
부동 소수점 연산을 사용하기 전 MMX 레지스터를 비워야한다. 왜냐면 부동소수점 컨벤션은 부동소수점 스택을 사용후 비우도록 정하고 있기 때문이다.
emms 명령을 mmx 코드의 끝에 삽입하여 부동 소수점 오버플로우 예외가 발생하는 것을 회피해야 한다.
--------------*/

#include <emmintrin.h>

int main( )
{
	__asm
	{
		emms
	}

	_mm_empty( );
}