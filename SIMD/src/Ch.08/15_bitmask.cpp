/*--------------
각각의 pack안에 들어 있는 최상위 bit를 가져와 2bit 혹은 4bit mask를 생성한다.

연산 기능			Vector 함수			intrinsic 함수
bit Mask 조립		move_mask			_mm_movemask_pd, _mm_movemask_pd
--------------*/

#include "fvec.h"
#include <iostream>

int main( )
{
	float pA[4] = { -1.1f, -2.2f, 3.3f, 4.4f };

	F32vec4 A;

	loadu( A, pA );

	int i = move_mask( A );

	std::cout << "Bit maks : " << i << std::endl;

	return 0;
}