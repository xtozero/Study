#include <iostream>

using namespace std;

class Wonder
{
public:
	void tick( ) { cout << "#1" << endl; }
	void tick( ) const { cout << "#2" << endl; }
	void tack( ) const { cout << "#3" << endl; }
};

int main( )
{
	Wonder device;
	device.tick( ); // #1
	device.tack( ); // #3 Wonder::tack 함수 중에 const가 아닌 함수가 없으므로
}