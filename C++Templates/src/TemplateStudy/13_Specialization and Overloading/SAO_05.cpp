#include <iostream>

template <typename T1, typename T2>
void f1( T1, T2 ) {}

template <typename T1, typename T2>
void f1( T2, T1 ) {}

template <typename T>
long f2( T ) {}

template <typename T>
char f2( T ) {}

int main( )
{
	f1<char, char>( 'a', 'b' ); // f1( T1, T2 )�� f1( T2, T1 )�� �ν��Ͻ�ȭ ��� f1( char, char )�� ���� �Լ��� �����Ǳ� ������ ��ȣ�ϴ�.
}