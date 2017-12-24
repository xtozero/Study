/*--------------
제곱근 함수
F32vec4 sqrt( const F32vec4& a )

역수 함수
F32vec4 rcp( const F32vec4& a )

제곱근 역수 함수
F32vec4 rsqrt( const F32vec4& a )

Newton-Raphson법의 역수 함수
F32vec4 rcp_nr( const F32vec4& a)
Newton-Raphson법의 역수 함수는 한 번의 연산으로 값을 구해주는 것이 아니라 intrinsic 함수의 조합으로 수식을 구현한 것이다.
따라서 직접 조합해서 만든 것과 성능 차이는 없다.
Newton-Raphson 역수 알고리즘은 https://en.wikipedia.org/w/index.php?title=Newton%27s_method&section=36#Multiplicative_inverses_of_numbers_and_power_series 에서 볼 수 있다.
Xn 이 역수 값이 되므로 Newton-Raphson 법의 역수 수식은 다음과 같다.
[2 * rcpps(x)-(x * rcpps(x) * rcpps(x))]

Newton-Raphson법의 제곱근 역수 함수
F32vec4 rsqrt_nr( const F32vec4& a )

수평 덧셈
float add_horizontal( const F32vec4& a )
한 번의 연산이 아니라 내부적으로 5개의 명령어가 조합되어 있다.
--------------*/

#include <fvec.h>
#include <iostream>

int main( )
{
	float pA[4] = { 1.0, 2.0, 3.0, 4.0 };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 R;

	loadu( A, pA );

	R = sqrt( A );

	storeu( pR, R );
	std::cout << "Square Root : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = rcp( A );

	storeu( pR, R );
	std::cout << "Reciprocal : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = rsqrt( A );

	storeu( pR, R );
	std::cout << "Reciprocal Square Root : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = rcp_nr( A );

	storeu( pR, R );
	std::cout << "Reciprocal Newton Raphson : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = rsqrt_nr( A );

	storeu( pR, R );
	std::cout << "Reciprocal Square Root Newton Raphson : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = add_horizontal( A );

	storeu( pR, R );
	std::cout << "Horizontal Add : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}

