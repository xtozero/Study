/*--------------
==, !=, <, <=, >, >=, !(A < B), !(A <= B), !(A > B), !(A >= B) 비교 연산을 수행한다.
F64vec2, F32vec1 클래스도 지원한다.
--------------*/

#include <fvec.h>
#include <iostream>

int main()
{
	float pA[4] = { 1.1, 0.0, 3.3, -4.4 };
	float pB[4] = { 1.1, 3.3, 2.2, 1.1 };
	float pR[4] = { 0 };

	F32vec4 A;
	F32vec4 B;
	F32vec4 R;

	loadu( A, pA );
	loadu( B, pB );

	R = cmpeq( A, B );	// Equality

	storeu( pR, R );
	std::cout << std::hex;
	std::cout << "cmpeq : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpneq( A, B );	// Inequality

	storeu( pR, R );
	std::cout << "cmpneq : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpgt( A, B );	// Greater Than

	storeu( pR, R );
	std::cout << "cmpgt : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpge( A, B );	// Greatoer Than or Equal To

	storeu( pR, R );
	std::cout << "cmpge : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpngt( A, B );	// Not Greater Than

	storeu( pR, R );
	std::cout << "cmpngt : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpnge( A, B );	// Not Greater Than or EqualTo

	storeu( pR, R );
	std::cout << "cmpnge : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmplt( A, B );	// Less Than

	storeu( pR, R );
	std::cout << "cmplt : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmple( A, B );	// Less Than or Equal To

	storeu( pR, R );
	std::cout << "cmple : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpnlt( A, B );	// Not Less Than

	storeu( pR, R );
	std::cout << "cmpnlt : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	R = cmpnle( A, B );	// Not Less Than or Equal To

	storeu( pR, R );
	std::cout << "cmpnle : ";
	for ( float elem : pR )
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;

	return 0;
}