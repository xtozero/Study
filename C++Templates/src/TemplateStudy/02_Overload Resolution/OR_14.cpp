#include <iostream>

using namespace std;

template<typename T> int f( T ) { cout << "#1" << endl; }
void f( int ) { cout << "#2" << endl; }

int main( )
{
	return f( 7 ); // error ��ȯ ���� ���� �����ø� �Լ��� ����.
}