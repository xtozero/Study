/*--------------
Unpack low
32bit float 실수 pack을 가진 두 개의 클래스 A, B에서 하위 인자 위치의 2개 pack을 조합하여 Vector를 생성한다.

사용 문법
F32vec4 A;
F32vec4 B;
F32Vec4 R;

R = unpack_low( A, B );

연산 기능
R0 := A0
R1 := B0
R2 := A1
R3 := B1

Unpack high
32bit float 실수 pack을 가진 두 개의 클래스 A, B에서 상위 인자 위치의 2개 pack을 조합하여 Vector를 생성한다.

사용 문법
F32vec4 A;
F32vec4 B;
F32Vec4 R;

R = unpack_high( A, B );

연산 기능
R0 := A2
R1 := B2
R2 := A3
R3 := B3

실수 Vector 클래스는 pack_sat 함수를 지원하지 않는다.
--------------*/

#include <fvec.h>
#include <iostream>

int main( )
{
	float pA[4] = { 0.f, 1.1f, 2.2f, 3.3f };
	float pB[4] = { 4.4f, 5.5f, 6.6f, 7.7f };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 B;

	loadu( A, pA );
	loadu( B, pB );

	F32vec4 R;

	R = unpack_low( A, B );

	storeu( pR, R );
	std::cout << "unpack_low : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = unpack_high( A, B );

	storeu( pR, R );
	std::cout << "unpack_high : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}