// 프렌드에 관하여
class Calcurator
{
	friend class Owner; // ok 프렌드 클래스는 선언만 가능하다.
	/*
	friend class Other // error
	{

	};
	*/

	friend void print(); // ok 프렌드 함수는 선언이 가능하다.
	friend void print( ) // ok 프렌드 함수는 정의도 가능하다. 이경우 이 함수는 전역 함수이다.
	{

	}
};

// 템플릿에서의 프렌드에 관하여
template <typename T>
class Node 
{
	Node<T>* allocate();
};

template <typename T>
class Tree
{
	friend class Factory; // Factory에 대한 첫 번째 선언이라 해도 괜찮다.
	friend class Node<T>; // Node가 가시화돼 있지 않으면 오류이다.
};

template <typename T1, typename T2>
void combine( T1, T2 ) {}

class Mixer
{
public:
	friend void combine<>( int&, int& ); // ok
	friend void combine<int, int>( int, int ); // ok
	friend void combine<char>( char, int ); // ok
	// friend void combine<char>( char&, int& ); // error char와 char& 형이 맞지 않는다.
	// friend void combine<char>( long, long ) {} // error 템플릿 인스턴스를 정의할 수 없다( 특수화를 정의할 수 있을 뿐이다. )
};

void multiply( void* ) {} // 일반 함수

template <typename T>
void multiply( T ) {} // 함수 템플릿

class Comrades
{
	friend void multiply( int ) {} // 새 함수 ::multiply(int)를 정의
	friend void ::multiply( void* ); // 일반 함수를 참조
	friend void ::multiply( int ); // 템플릿의 인스턴스를 참조
	friend void ::multiply<double*>( double* ); // 한정된 이름 뒤에도 꺾쇠가 나올 수 있다. 다만 템플릿은 가시화돼 있어야 한다.
	// friend void ::error( ) {} // error 프렌드가 한정되어 있을 경우 정의가 될 수 없다.
};

template <typename T>
class List
{
	friend Node<T>* Node<T>::allocate( );
};

template <typename T>
class Creator
{
	/*
	friend void appear( ) // 이 함수는 Creator가 인스턴스화될 때까지 존재하지 않는다.
	{

	}
	*/

	friend void feed( Creator<T>* ) {} // 모든 T는 다른 함수 ::feed()를 생성한다.
};

class Manager
{
	template <typename T>
	friend class Task;
	template <typename T>
	friend Node<T>* Node<T>::allocate( );
	template <typename T>
	friend int ticket( )
	{
		++Manager::counter;
	}
	static int counter;
};

int main( )
{
	Creator<void> miracle; // ::appear는 이 시점에서 생성된다.
	Creator<double> oops; // error ::appear가 두 번째로 생성되며 ODR을 어기게 된다.
}