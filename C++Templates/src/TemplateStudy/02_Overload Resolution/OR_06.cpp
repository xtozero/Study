#include <iostream>

using namespace std;

void Promotion( char ) { cout << "#1" << endl; } // #1
void Promotion( int ) { cout << "#2" << endl; } // #2

int main( )
{
	Promotion( true );
}