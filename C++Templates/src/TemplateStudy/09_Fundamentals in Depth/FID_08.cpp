#include <iostream>

template <typename Func, typename T>
void apply( Func func_ptr, T x )
{
	func_ptr( x );
}

template <typename T> void single( T ) { std::cout << "void single( T )" << std::endl; }

template <typename T> void multi( T ) { std::cout << "void multi( T )" << std::endl; }
template <typename T> void multi( T* ) { std::cout << "void multi( T* )" << std::endl; }

int main( )
{
	apply( &single<int>, 3 ); // ok

	apply( &multi<int>, 7 ); // error multi<int>가 하나가 아님.
}