/*--------------
shift 연산도 지원된다. signed를 지원하는 클래스는 산술적 오른쪽 shift가 수행된다.

사용문법
Is16vec8 A;
Is16vec8 B;
Is16vec8 R;

R = A << 1
R <<= 1
R = A >> 2
R >>= 2
--------------*/

#include <dvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short pA[8] = { 1, 2, 3, 4, -5, -6, -7, -8 };
	alignas( 16 ) short pR[8] = { 0 };

	Is16vec8* pVA = reinterpret_cast<Is16vec8*>( pA );
	Is16vec8* pVR = reinterpret_cast<Is16vec8*>( pR );

	*pVR = *pVA << 2;

	std::cout << "Left 2 shift : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = *pVA >> 1;

	std::cout << "Right 1 shift : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR <<= 1;

	std::cout << "Left 1 shift : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR >>= 1;

	std::cout << "Right 1 shift : ";
	for ( short elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}