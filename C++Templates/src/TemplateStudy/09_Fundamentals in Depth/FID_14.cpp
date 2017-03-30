// �����忡 ���Ͽ�
class Calcurator
{
	friend class Owner; // ok ������ Ŭ������ ���� �����ϴ�.
	/*
	friend class Other // error
	{

	};
	*/

	friend void print(); // ok ������ �Լ��� ������ �����ϴ�.
	friend void print( ) // ok ������ �Լ��� ���ǵ� �����ϴ�. �̰�� �� �Լ��� ���� �Լ��̴�.
	{

	}
};

// ���ø������� �����忡 ���Ͽ�
template <typename T>
class Node 
{
	Node<T>* allocate();
};

template <typename T>
class Tree
{
	friend class Factory; // Factory�� ���� ù ��° �����̶� �ص� ������.
	friend class Node<T>; // Node�� ����ȭ�� ���� ������ �����̴�.
};

template <typename T1, typename T2>
void combine( T1, T2 ) {}

class Mixer
{
public:
	friend void combine<>( int&, int& ); // ok
	friend void combine<int, int>( int, int ); // ok
	friend void combine<char>( char, int ); // ok
	// friend void combine<char>( char&, int& ); // error char�� char& ���� ���� �ʴ´�.
	// friend void combine<char>( long, long ) {} // error ���ø� �ν��Ͻ��� ������ �� ����( Ư��ȭ�� ������ �� ���� ���̴�. )
};

void multiply( void* ) {} // �Ϲ� �Լ�

template <typename T>
void multiply( T ) {} // �Լ� ���ø�

class Comrades
{
	friend void multiply( int ) {} // �� �Լ� ::multiply(int)�� ����
	friend void ::multiply( void* ); // �Ϲ� �Լ��� ����
	friend void ::multiply( int ); // ���ø��� �ν��Ͻ��� ����
	friend void ::multiply<double*>( double* ); // ������ �̸� �ڿ��� ���谡 ���� �� �ִ�. �ٸ� ���ø��� ����ȭ�� �־�� �Ѵ�.
	// friend void ::error( ) {} // error �����尡 �����Ǿ� ���� ��� ���ǰ� �� �� ����.
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
	friend void appear( ) // �� �Լ��� Creator�� �ν��Ͻ�ȭ�� ������ �������� �ʴ´�.
	{

	}
	*/

	friend void feed( Creator<T>* ) {} // ��� T�� �ٸ� �Լ� ::feed()�� �����Ѵ�.
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
	Creator<void> miracle; // ::appear�� �� �������� �����ȴ�.
	Creator<double> oops; // error ::appear�� �� ��°�� �����Ǹ� ODR�� ���� �ȴ�.
}