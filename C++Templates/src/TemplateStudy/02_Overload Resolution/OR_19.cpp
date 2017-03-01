#include <iostream>

using namespace std;

class Interface { public: void foo( ) {} };

class CommonProcesses : public Interface {};

class Machine : public CommonProcesses {};

void serialize( int Interface::* ) { cout << "#1" << endl; } // #1
void serialize( int CommonProcesses::* ) { cout << "#2" << endl; } // #2

void serialize( void (Interface::*pFunc)() ) { cout << "#1" << endl; } // #1
void serialize( void (CommonProcesses::*pFunc)() ) { cout << "#2" << endl; } // #2


int main( )
{
	int Machine::* machine = nullptr;
	serialize( machine );

	void (Machine::*pFunc)() = nullptr;
	serialize( pFunc );
}