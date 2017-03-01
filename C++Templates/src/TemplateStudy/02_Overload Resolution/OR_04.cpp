#include <iostream>

using namespace std;

void PerfectMatch( const int ) { cout << "PerfectMatch( const int )" << endl; } // #1
void PerfectMatch( double ) { cout << "PerfectMatch( double )" << endl; } // #2

int main( )
{
	PerfectMatch( 1 ); // #1 ÀÌ È£Ãâ
}