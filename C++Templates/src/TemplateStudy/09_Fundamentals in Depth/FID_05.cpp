/*
template <typename Allocator>
class List
{
	class Allocator* allocator;		// error	
	friend class Allocator;			// error

	//...
};
*/

template <int buf[5]> class Lexer;	// buf는 사실 int*
template <int* buf> class Lexer;	// ok 이것은 재선언

template <int const length> class Buffer;	// const 무시
template <int length> class Buffer // 이전 선언과 동일
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

template <template <typename T, T*> class Buf> // ok 파라미터화 구문애서는 사용 가능
class Edge
{
	//...
};

template <template <typename T> class List>
class Node
{
//	T* storage; // error 템플릿 템플릿 파라미터의 파라미터는 여기서 사용할 수 없음
};

class MyAllocator
{

};

template <template <typename, typename = MyAllocator> class Container>
class Adaptataion
{
	Container<int> storage; // 묵시적으로 Container<int, MyAllocator>와 동일
};

int main( )
{
	Buffer<10> n;
}