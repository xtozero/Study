#include <iostream>

using namespace std;

void n_elements( int ) { cout << "#1" << endl; }
void n_elements( float ) { cout << "#2" << endl; }

int main( )
{
	void( *pFunc )(float) = n_elements;
	pFunc( 1 ); // #2
}