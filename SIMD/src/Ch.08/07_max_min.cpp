/*--------------
정수 vector 클래스와 동일한 함수를 사용한다.
--------------*/
#include <fvec.h>
#include <iostream>

int main( )
{
	float pA[4] = { 1.1, 2.2, 3.3, 4.4 };
	float pB[4] = { 4.4, 3.3, 2.2, 1.1 };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 B;
	F32vec4 R;

	loadu( A, pA );
	loadu( B, pB );

	R = simd_min( A, B );
	
	storeu( pR, R );
	std::cout << "Min : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = simd_max( A, B );

	storeu( pR, R );
	std::cout << "Max : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}