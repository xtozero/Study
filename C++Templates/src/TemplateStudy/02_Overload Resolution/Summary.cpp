#include <iostream>

void DisplayNum(int) { std::cout << "DisplayNum(int)" << std::endl; }
void DisplayNum(double) { std::cout << "DisplayNum(double)" << std::endl; }

void Ambigouous(long) {}
void Ambigouous(double) {}

void Combine( int, double ) {}
void Combine( double, int ) {}

void PerfectMatch( const int ) { std::cout << "#1" << std::endl; }
void PerfectMatch( double ) { std::cout << "#2" << std::endl; }

void MinorAdjust( int* pArray ) { std::cout << "#1" << std::endl; }
//void MinorAdjust( int** ptr ) { std::cout << "#2" << std::endl; }
void MinorAdjust( int const* const* ptr ) { std::cout << "#3" << std::endl; }

void Promotion( char ) { std::cout << "#1" << std::endl; }
void Promotion( int ) { std::cout << "#2" << std::endl; }

void StandardConversion( char ) { std::cout << "#1" << std::endl; }
void StandardConversion( ... ) { std::cout << "#2" << std::endl; }

class Userdefined
{
public:
	Userdefined( int ) {}
};

void UserdefinedConversion( Userdefined ) { std::cout << "#1" << std::endl; }
void UserdefinedConversion( ... ) { std::cout << "#2" << std::endl; }

void Ellipsis( ... ) { std::cout << "#1" << std::endl; }

template <typename T>
class Implicit
{
public:
	Implicit( T a ) {}
};

template <typename T>
void TemplateFunction( Implicit<T> ) {}

class BadString
{
public:
	BadString( const char* ) {}

	char& operator[] ( size_t ) {}
	const char& operator[] ( size_t ) const {}

	operator char* () {}
	operator const char* () {}
};

void PerfectMatch( char& ) { std::cout << "#1" << std::endl; }
void PerfectMatch( const char& ) { std::cout << "#2" << std::endl; }
// void PerfectMatch( char ) {} �߰��� ��ȣ�� �߻�

class Wonder
{
public:
	void tick( ) { std::cout << "#1" << std::endl; }
	void tick( ) const { std::cout << "#2" << std::endl; }
	void tack( ) const { std::cout << "#3" << std::endl; }
};

template<typename T> int f( T ) {}
void f( int ) {}

class Base
{
public:
	operator short( ) const { return 0; }
};

class Derived : public Base
{

};

void count( int ) {}

// void count( short ) {} int���� ������ �°��� �Ͼ�� �ʾƵ� �ǹǷ� �� ��ȣ�ȴ�.

void check( void* ) { std::cout << "#1" << std::endl; } // #1
void check( bool ) { std::cout << "#2" << std::endl; } // #2

class Interface {};

class CommonProcesses : public Interface {};

class Machine : public CommonProcesses {};

void serialize( Interface* ) { std::cout << "#1" << std::endl; } // #1
void serialize( CommonProcesses* ) { std::cout << "#2" << std::endl; } // #2
void serialize( void* ) { std::cout << "#3" << std::endl; } // #3

using FuncType = void( *)(double, int);

class IndirectFunctor
{
public:
	void operator()( double, double ) const {}
	operator FuncType( ) const { return nullptr; }
};

void n_elements( int ) { std::cout << "#1" << std::endl; }
void n_elements( float ) { std::cout << "#2" << std::endl; }

class BigNum
{
public:
	BigNum( int ) { std::cout << "#1" << std::endl; }
	BigNum( long ) { std::cout << "#2" << std::endl; }
	BigNum( double ) { std::cout << "#3" << std::endl; }
	BigNum( const std::string& ) { std::cout << "#4" << std::endl; }

	operator double( ) { std::cout << "#5" << std::endl; return 1; }
	operator long( ) { std::cout << "#6" << std::endl; return 1.0; }
};

int main()
{
	std::cout << "Default overload resolution sample" << std::endl;	
	DisplayNum(1);
	DisplayNum(1.0);
	
    // Ambigouous(1); error �ĺ��� ������ �־� ��ȣ�� ȣ��
	
	// Combine( 1, 2 ); // error C2666: 'Combine': 2�� �����ε忡 ����� ��ȯ�� �ֽ��ϴ�. 

	// �Ϻ��� ��ġ
	std::cout << "Perfect match overload sample" << std::endl;	
	PerfectMatch( 1 ); // #1 �� ȣ��

	std::cout << "Minor adjust overload sample" << std::endl;
	int arr[5] = {};
	MinorAdjust( arr ); // �迭�� �����ͷ� ��ȯ(decay)

	// ���� ������ ���� ��ġ
	int* pArr = arr;
	int** ppArr = &pArr;
	MinorAdjust( ppArr ); // #2�� �ּ��� Ǯ�� �Ϻ��� ��ġ�� #2
			      // #2�� ������ int** -> int const* const*�� �����Ͽ� #3 ȣ��
	
	// �°��� ���� ��ġ
	std::cout << "Promotion overload sample" << std::endl;	
	Promotion( true ); // bool -> int �������� �°����� #2 ȣ��
	
	// ǥ�� ��ȯ�� ���� ��ġ
	std::cout << "Standard conversion sample" << std::endl;	
	StandardConversion( true ); // bool -> char �� ǥ�� ��ȯ�� ����Ǽ� #1 ȣ��

	// ����� ��ȯ�� ���� ��ġ
	std::cout << "Userdefined conversion sample" << std::endl;
	UserdefinedConversion( 1 );

	// ������ ���� ��ġ
	std::cout << "Ellipsis conversion sample" << std::endl;	
	Ellipsis( 1 );

	// ���ø� ���� �߷а� �����ε� �ؼ��� ����
	TemplateFunction<int>( 1 ); //ok
	// TemplateFunction( 1 ); // error

	// ��� �Լ��� ���� ������ ���ڿ� ���� �����ε� ����
	BadString str( "correckt" );
	// str[5] = 'c'; // "[]" ������ �� �� �� �̻��� �� �ǿ����ڿ� ��ġ�մϴ�.
		      // �⺻ ���� ������ "pointer-to-object[interger]
		      // �Լ� "BadString::operator[]( size_t )"
	

	// �Ϻ��� ��ġ ��
	char c = 'a';
	PerfectMatch( c ); // #1
	PerfectMatch( 'a' ); // #2

	Wonder device;
	device.tick( ); // #1
	device.tack( ); // #3 Wonder::tack �Լ� �߿� const�� �ƴ� �Լ��� �����Ƿ�

	// �����ø� ��ȣ
	// return f( 0 ); error ��ȯ ���� ���� �� ���ø� �Լ��� ����

	// ������ ��ȯ�� �������� ����
	Derived object;
	count( object ); // ok Derived -> Base -> short -> int ������ ��ȯ�Ǿ� �� �����Ѵ�.

	// ������ ��ȯ
	int* p = nullptr;
	check( p ); // bool �������� ��ȯ�� �ٸ� ǥ�� �������� ��ȯ���� ���� ���� ������ ���.

	Machine* machine = nullptr;
	serialize( machine ); // #2 ��� ������ �����ͷ��� ��ȯ�� void*���� ��ȯ ���� ��ȣ�ȴ�.

	// Functor�� �븮�Լ�
	IndirectFunctor functor;
	//functor( 3, 5 ); // error ��ȣ�� ȣ�� operator()�� �������� *this �Ķ���Ϳ� ���ؼ��� �� ������ �ι�° ���ڰ� FuncType���� �� ���� �����Ƿ� �쿭�� ���� �� ����.

	// �� ���� �����ε� ����
	// �Լ� �ּҰ� �ʿ��� ���
	void( *pFunc )(float) = n_elements;
	pFunc( 1 ); // #2

	// �ʱ�ȭ�� ������ �����ڸ� ȣ���ϰų� ��ȯ �����ڸ� ������ ���
	BigNum bn1( 100103 ); // #1
	BigNum bn2( "7057103224.095764" ); // #4
	int in = bn1; // #6
}
