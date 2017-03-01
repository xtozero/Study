#include <iostream>

using namespace std;

class BigNum
{
public:
	BigNum( int ) { cout << "#1" << endl; }
	BigNum( long ) { cout << "#2" << endl; }
	BigNum( double ) { cout << "#3" << endl; }
	BigNum( const std::string& ) { cout << "#4" << endl; }

	operator double( ) { cout << "#5" << endl; return 1; }
	operator long( ) { cout << "#6" << endl; return 1.0; }
};

int main( )
{
	BigNum bn1( 100103 ); // #1
	BigNum bn2( "7057103224.095764" ); // #4
	int in = bn1; // #6
}