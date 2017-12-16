/*--------------
Unpack low
Is16vec8 R = unpack_low( Is16vec8 A, Is16vec8 B )

Unpack high
Is16vec8 R = unpack_high( Is16vec8 A, Is16vec8 B )
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

	*pVR = unpack_low( *pVA, *pVB );
	std::cout << "unpack low : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	*pVR = unpack_high( *pVA, *pVB );
	std::cout << "unpack high : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}