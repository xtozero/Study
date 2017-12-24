/*--------------
비교 결과를 가지고 값을 가져오거나 다른 Vector 클래스에 적용해야하는 기능을 도와준다.
select 함수는 단 한번의 연산에 이뤄지는 것이 아니다.
비교 함수와 AND 연산, ANDNOT 연산, 생성 대입 연산, OR 연산의 5개 함수가 호출된다.
--------------*/

#include <fvec.h>
#include <iostream>

int main( )
{
	float pA[4] = { 0.f, -1.1f, -2.2f, -3.3f };
	float pB[4] = { 0.f, 1.1f, 2.2f, 3.3f };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 B;
	F32vec4 C( 1.f, 1.f, 1.f, 1.f );
	F32vec4 D( 2.f, 2.f, 2.f, 2.f );
	F32vec4 R;

	loadu( A, pA );
	loadu( B, pB );

	R = select_eq( A, B, C, D );	// Equality

	storeu( pR, R );
	std::cout << "Equality : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_neq( A, B, C, D );	// Inequality

	storeu( pR, R );
	std::cout << "Inequality : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_gt( A, B, C, D );	// Greater Than

	storeu( pR, R );
	std::cout << "Greater Than : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_ge( A, B, C, D );	// Greatoer Than or Equal To

	storeu( pR, R );
	std::cout << "Greatoer Than or Equal To : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_ngt( A, B, C, D );	// Not Greater Than

	storeu( pR, R );
	std::cout << "Not Greater Than : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_nge( A, B, C, D );	// Not Greater Than or EqualTo

	storeu( pR, R );
	std::cout << "Not Greater Than or EqualTo : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_lt( A, B, C, D );	// Less Than

	storeu( pR, R );
	std::cout << "Less Than : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_le( A, B, C, D );	// Less Than or Equal To

	storeu( pR, R );
	std::cout << "Less Than or Equal To : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_nlt( A, B, C, D );	// Not Less Than

	storeu( pR, R );
	std::cout << "Not Less Than : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = select_nle( A, B, C, D );	// Not Less Than or Equal To

	storeu( pR, R );
	std::cout << "Not Less Than or Equal To : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}