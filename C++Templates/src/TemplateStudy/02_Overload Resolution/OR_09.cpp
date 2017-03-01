#include <iostream>

using namespace std;

void Ellipsis( ... ) { cout << "#1" << endl; }

int main( )
{
	Ellipsis( 1 );
}