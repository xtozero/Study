#include <iostream>

template <typename T>
class TypeOp
{
public:
	using ArgT = T;
	using BareT = T;
	using ConstT = const T;
	using RefT = T&;
	using RefBareT = T&;
	using RefConstT = const T&;
};

template <typename T>
class TypeOp<const T>
{
public:
	using ArgT = const T;
	using BareT = T;
	using ConstT = const T;
	using RefT = const T&;
	using RefBareT = T&;
	using RefConstT = const T&;
};

template <typename T>
class TypeOp<T&>
{
public:
	using ArgT = const T&;
	using BareT = typename TypeOp<T>::BareT;
	using ConstT = const T;
	using RefT = T&;
	using RefBareT = typename TypeOp<T>::BareT&;
	using RefConstT = const T&;
};

template <>
class TypeOp<void>
{
public:
	using ArgT = void;
	using BareT = void;
	using ConstT = const void;
	using RefT = void;
	using RefBareT = void;
	using RefConstT = void;
};

template <typename T>
void apply( typename TypeOp<T>::RefT arg, void( *func )( T ) )
{
	func( arg );
}

void incr( int& a )
{
	++a;
}

void print( int a )
{
	std::cout << a << std::endl;
}

int main( )
{
	int x = 7;
	apply( x, print );
	apply( x, incr );
}