#include <iostream>

using namespace std;

class Userdefined
{
public:
	Userdefined( int ) {}
};
void UserdefinedConversion( Userdefined ) { cout << "#1" << endl; }
void UserdefinedConversion( ... ) { cout << "#2" << endl; }

int main( )
{
	UserdefinedConversion( 1 );
}