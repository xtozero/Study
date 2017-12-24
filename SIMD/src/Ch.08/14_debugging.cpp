/*--------------
정수 Vector 클래스와 동일하게 객체 안에 들어 있는 값을 알 수 있도록 output stream << 연산자를 구현하였다.
이를 통해서 더 편리하게 디버깅과 구현을 할 수 있다.
주의점은 <iostream> 파일을 포함할 때 fvec.h, dvec.h 보다 우선해야 한다는 점이다.

[] 연산자
실수 vector 클래스 안에 있는 값을 가져오고 입력하기 위해 []연산자도 제공한다.
--------------*/
#define _ENABLE_VEC_DEBUG

#include <iostream>
#include <fvec.h>

int main( )
{
	float pA[4] = { 1.1f, 2.2f, 3.3f, 4.4f };
	float pB[4] = { 4.4f, 3.3f, 2.2f, 1.1f };
	float pR[4] = { 0.f };

	F32vec4 A;
	F32vec4 B;
	F32vec4 R;

	loadu( A, pA );
	loadu( B, pB );

	R = A + B;
	std::cout << "Add : " << R << std::endl;

	R = A - B;
	std::cout << "Sub : " << R << std::endl;

	R = A * B;
	std::cout << "Mul : " << R << std::endl;

	R = A / B;
	std::cout << "Div : " << R << std::endl;

	float f = A[2];	// pack 안의 값 가져오기
	std::cout << "Get Pack Value : " << f << std::endl;

	A[3] = 5.5f; // 값 입력하기
	std::cout << "Set Pack Value : " << A << std::endl;

	return 0;
}