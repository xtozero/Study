/*
template <typename Allocator>
class List
{
	class Allocator* allocator;		// error	
	friend class Allocator;			// error

	//...
};
*/

template <int buf[5]> class Lexer;	// buf�� ��� int*
template <int* buf> class Lexer;	// ok �̰��� �缱��

template <int const length> class Buffer;	// const ����
template <int length> class Buffer // ���� ����� ����
{
};

template <template <typename X> class C>
void f( C<int>* p );

/*
template <template <typename X> struct C> // error
void f( C<int>* p );

template <template <typename X> union C> // error
void f( C<int>* p );
*/

template <template <typename T, T*> class Buf> // ok �Ķ����ȭ �����ּ��� ��� ����
class Edge
{
	//...
};

template <template <typename T> class List>
class Node
{
//	T* storage; // error ���ø� ���ø� �Ķ������ �Ķ���ʹ� ���⼭ ����� �� ����
};

class MyAllocator
{

};

template <template <typename, typename = MyAllocator> class Container>
class Adaptataion
{
	Container<int> storage; // ���������� Container<int, MyAllocator>�� ����
};

int main( )
{
	Buffer<10> n;
}