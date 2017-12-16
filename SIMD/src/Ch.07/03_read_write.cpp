/*--------------
내부 데이터형이 intrinsic 변수이므로 intrinsic 함수를 이용해서 읽고 쓸 수 있다.
--------------*/

#include <dvec.h>
#include <emmintrin.h>
#include <iostream>

int main( )
{
	alignas( 16 ) short A[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	alignas( 16 ) short R[8] = { 0 };

	// 낮은 주소에 8부터 역순으로 입력
	Is16vec8 Vector( 1, 2, 3, 4, 5, 6, 7, 8 );

	_mm_store_si128( reinterpret_cast<__m128i*>( R ), Vector );

	std::cout << "Store : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	// 포인터 캐스팅으로 바로 읽기
	Is16vec8* a = (Is16vec8*)A;

	Is16vec8 *r = (Is16vec8*)R;

	*r = *a;

	std::cout << "Store : ";
	for ( short elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}