#include <iostream>

using namespace std;

template<typename T> int f( T ) { cout << "#1" << endl; }
void f( int ) { cout << "#2" << endl; }

int main( )
{
	return f( 7 ); // error 반환 값이 없는 비템플릿 함수가 선택.
}