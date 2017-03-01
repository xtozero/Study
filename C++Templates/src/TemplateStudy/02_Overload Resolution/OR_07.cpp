#include <iostream>

using namespace std;

void StandardConversion( char ) { cout << "#1" << endl; }
void StandardConversion( ... ) { cout << "#2" << endl; }

int main( )
{
	StandardConversion( true );
}