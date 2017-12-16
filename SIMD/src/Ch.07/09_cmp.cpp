/*--------------
양수와 음수 모두 비교 가능하다.
사용할 Vector의 사이즈와 데이터형은 모두 같아야 한다.

사용문법
Is16vec8 A;
Is16vec8 B;
Is16vec8 R;

R = cmpeq(A, B)
R = cmpneq(A, B)
R = cmpgt(A, B)
R = cmpge(A, B)
R = cmplt(A, B)
R = cmple(A, B)
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

	std::cout << std::hex;

	*pVR = cmpeq( *pVA, *pVB );
	std::cout << "Equality : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = cmpneq( *pVA, *pVB );
	std::cout << "Inequality : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;


	*pVR = cmpgt( *pVA, *pVB );
	std::cout << "Greater Than : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = cmplt( *pVA, *pVB );
	std::cout << "Less Than : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}