#include <list>
#include <vector>

typedef std::vector<std::list<int> > LineTable;
typedef std::vector<std::list<int>> OtherTable;	// C++11 ���������� error

template <int N> class Buf;

template <typename T> void strange( ) {}
template <int N> void strange( ) {}

class Marker;

int main( )
{
	strange<Buf<16>>2>>( ); // >> ��ū�� ������ �ƴ����� error
	std::list<::Marker>* marker; // g++ ���� -std=c++11 �̻� �ɼ��� ���� ���� ok
}