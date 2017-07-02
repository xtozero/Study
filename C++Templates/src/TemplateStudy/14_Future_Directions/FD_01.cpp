#include <list>
#include <vector>

typedef std::vector<std::list<int> > LineTable;
typedef std::vector<std::list<int>> OtherTable;	// C++11 이전에서는 error

template <int N> class Buf;

template <typename T> void strange( ) {}
template <int N> void strange( ) {}

class Marker;

int main( )
{
	strange<Buf<16>>2>>( ); // >> 토큰은 오류가 아니지만 error
	std::list<::Marker>* marker; // g++ 에서 -std=c++11 이상 옵션을 줬을 때만 ok
}