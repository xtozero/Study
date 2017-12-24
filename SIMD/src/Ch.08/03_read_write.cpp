/*--------------
실수 Vector 클래스에 있는 값은 double*, float* 같이 포인터 형으로 받아서 배열에 있는 값을 바로 입력하고 쓸 수 있다.
읽기와 쓰기를 위한 메모리는 정렬되지 않아도 된다.

메모리에서 데이터 읽기
loadu( F32vec4 R, float* pa );
loadu 함수는 F32vec4, F64vec2 클래스를 모두 지원한다.

메모리에 데이터 쓰기
storeu( float* pb, F32vec4 R);
storeu 함수는 F32vec4, F64vec2 클래스를 모두 지원한다.
--------------*/

#include <fvec.h>
#include <iostream>

int main( )
{
	alignas( 16 ) float A[4] = { 1.1, 2.2, 3.3, 4.4 };
	alignas( 16 ) float B[4] = { 4.4, 3.3, 2.2, 1.1 };
	alignas( 16 ) float R[4] = { 0 };

	F32vec4 Vector;

	loadu( Vector, B );

	storeu( R, Vector );

	std::cout << "Store : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	F32vec4* vA = (F32vec4*)A;
	F32vec4* vR = (F32vec4*)R;

	*vR = *vA;

	std::cout << "Store : ";
	for ( float elem : R )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}