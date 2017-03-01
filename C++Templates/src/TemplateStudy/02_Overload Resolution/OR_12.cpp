#include <iostream>

using namespace std;

void PerfectMatch( int& ) { cout << "#1" << endl; } // #1
void PerfectMatch( const int & ) { cout << "#2" << endl; } // #2
//void PerfectMatch( int ) { cout << "#3" << endl; }

int main( )
{
	int k = 0;
	PerfectMatch( k );
	PerfectMatch( 42 );

	const int ck = 2017;
	PerfectMatch( ck );
}