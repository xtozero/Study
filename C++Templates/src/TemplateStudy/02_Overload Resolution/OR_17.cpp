// Quiz

#include <iostream>

using namespace std;

void check( void* ) { cout << "#1" << endl; } // #1
void check( bool ) { cout << "#2" << endl; } // #2

int main( )
{
	int (*p )() = nullptr;
	check( p ); // ?
}