#include <iostream>

using namespace std;

class Base
{
public:
	void f( char ) { cout << "Base::f" << endl; }
	void g( char ) { cout << "Base::g" << endl; }
};

class Derived : public Base
{
public:
	using Base::f;
	using Base::g;
	void f( int ) { cout << "Derived::f" << endl; f( 'c' ); }
	void g( int ) { cout << "Derived::g" << endl; g( 'c' ); }
};

int main( )
{

}