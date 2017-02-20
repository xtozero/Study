#include <iostream>
#include <string>

using namespace std;

template <typename T>
T add( T lhs, T rhs )
{
	return lhs + rhs;
}

int main()
{
	cout << add( 1, 2 ) << endl; // 3�� ���
	cout << add( 3.1, 4.1 ) << endl; // 7.2�� ���
	cout << add( string( "hello " ), string( "world" ) ) << endl; // "hello world" ���
}