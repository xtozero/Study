#include <iostream>
#include <list>
#include <vector>

template <typename T>
using Table = std::vector<std::list<T>>;

template <typename T>
class CTable
{
public:
	typedef std::vector<std::list<T>> Type;
};

//template <typename T> using Opaque = T;
//template <typename T> using Opaque<T*> = void*;
//template <> using Opaque<void> = bool;

void candidate( long ) { std::cout << "#1" << std::endl; }
template <typename T> using DT = T;
template <typename T> void candidate( DT<T> ) { std::cout << "#2" << std::endl; }

int main( )
{
	Table<int> t;
	CTable<int>::Type ct;

	candidate( 42 );
}