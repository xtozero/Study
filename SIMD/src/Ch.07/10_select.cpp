/*--------------
비교 함수를 수행하면 결과값이 1, 0로 세팅된다. 비교 결과만으로 연산이 끝나는 경우는 많지 않다.
비교 결과를 값으로 가져오거나 다른 Vector 클래스에 적용하는 기능을 도와주는 것이 Select 함수이다.

사용문법
Is16vec8 A;
Is16vec8 B;
Is16vec8 C;
Is16vec8 D;
Is16vec8 R;

R = select_eq( A, B, C, D );
R = select_neq( A, B, C, D );
R = select_gt( A, B, C, D );
R = select_ge( A, B, C, D );
R = select_lt( A, B, C, D );
R = select_le( A, B, C, D );

다음과 같은 문법으로 사용하면 max 함수와 비슷하게 동작한다.
Is16vec8 A;
Is16vec8 B;
Is16vec8 R;

R = select_gt( A, B, A, B ) // 큰 값 선택

연산 기능
R0 := ( A0 > B0 ) ? C0 : D0
R1 := ( A1 > B1 ) ? C1 : D1
R2 := ( A2 > B2 ) ? C2 : D2
R3 := ( A3 > B3 ) ? C3 : D3
R4 := ( A4 > B4 ) ? C4 : D4
R5 := ( A5 > B5 ) ? C5 : D5
R6 := ( A6 > B6 ) ? C6 : D6
R7 := ( A7 > B7 ) ? C7 : D7
--------------*/

#include <dvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short pA[8] = { 1, 0, 1, 0, -1, 0, -1, 2 };
	alignas( 16 ) short pB[8] = { 1, 1, 0, 0, 1, 1, 0, 0 };
	alignas( 16 ) short pR[8] = { 0 };

	Is16vec8* pVA = (Is16vec8*)pA;
	Is16vec8* pVB = (Is16vec8*)pB;
	Is16vec8* pVR = (Is16vec8*)pR;

	*pVR = select_eq( *pVA, *pVB, *pVA, *pVB );
	std::cout << "Equality : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = select_neq( *pVA, *pVB, *pVA, *pVB );
	std::cout << "Inequality : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = select_gt( *pVA, *pVB, *pVA, *pVB );
	std::cout << "Greater Than : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = select_lt( *pVA, *pVB, *pVA, *pVB );
	std::cout << "Less Then : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}