/*--------------
pack 사이즈를 절반으로 줄여서 Vector를 생성한다. unsigned, signed 함수를 제공한다.

signed
Is16vec8 R = pack_sat( Is32vec4 A, Is32vec4 B)

unsigned
Is16vec8 R = packu_sat( Is32vec4 A, Is32vec4 B)
--------------*/

#include <dvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) int pA[4] = { 1, 0, -1, 0 };
	alignas( 16 ) int pB[4] = { 1, 2, 0, -2 };
	alignas( 16 ) short pR[8] = { 0 };

	Is32vec4* pVA = (Is32vec4*)pA;
	Is32vec4* pVB = (Is32vec4*)pB;
	Is16vec8* pVR = (Is16vec8*)pR;

	*pVR = pack_sat( *pVA, *pVB );

	std::cout << "pack : ";
	for ( const short& elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}