#include <iostream>

using namespace std;

class Interface {};

class CommonProcesses : public Interface {};

class Machine : public CommonProcesses {};

void serialize( Interface* ) { cout << "#1" << endl; } // #1
void serialize( CommonProcesses* ) { cout << "#2" << endl; } // #2
void serialize( void* ) { std::cout << "#3" << std::endl; } // #3

int main( )
{
	Machine* machine = nullptr;
	serialize( machine );
}