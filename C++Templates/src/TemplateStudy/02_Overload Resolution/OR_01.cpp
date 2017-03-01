#include <iostream>

using namespace std;

void DisplayNum( int ) { cout << "void DisplayNum( int )" << endl; }
void DisplayNum( double ) { cout << "void DisplayNum( double )" << endl; }

int main( )
{
	DisplayNum( 1 );
	DisplayNum( 1.0 );
}