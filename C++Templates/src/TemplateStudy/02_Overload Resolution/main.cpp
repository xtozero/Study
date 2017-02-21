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

int main()
{
	std::cout << "Default overload resolution sample" << std::endl;	
	DisplayNum(1);
	DisplayNum(1.0);
	
    // Ambigouous(1); error �ĺ��� ������ �־� ��ȣ�� ȣ��
	
	// Combine( 1, 2 ); // error C2666: 'Combine': 2�� �����ε忡 ����� ��ȯ�� �ֽ��ϴ�. 

	std::cout << "Perfect match overload sample" << std::endl;	
	PerfectMatch( 1 ); // #1 �� ȣ��

	std::cout << "Minor adjust overload sample" << std::endl;
	int arr[5] = {};
	MinorAdjust( arr ); // �迭�� �����ͷ� ��ȯ(decay)

	int* pArr = arr;
	int** ppArr = &pArr;
	MinorAdjust( ppArr ); // #2�� �ּ��� Ǯ�� �Ϻ��� ��ġ�� #2
			      // #2�� ������ int** -> int const* const*�� �����Ͽ� #3 ȣ��
	
	std::cout << "Promotion overload sample" << std::endl;	
	Promotion( true ); // bool -> int �������� �°����� #2 ȣ��
	
	std::cout << "Standard conversion sample" << std::endl;	
	StandardConversion( true ); // bool -> char �� ǥ�� ��ȯ�� ����Ǽ� #1 ȣ��

	std::cout << "Userdefined conversion sample" << std::endl;
	UserdefinedConversion( 1 );

	std::cout << "Ellipsis conversion sample" << std::endl;	
	Ellipsis( 1 );

	TemplateFunction<int>( 1 ); //ok
	// TemplateFunction( 1 ); // error

	BadString str( "correckt" );
	// str[5] = 'c'; // "[]" ������ �� �� �� �̻��� �� �ǿ����ڿ� ��ġ�մϴ�.
		      // �⺻ ���� ������ "pointer-to-object[interger]
		      // �Լ� "BadString::operator[]( size_t )"
	
	char c = 'a';
	PerfectMatch( c ); // #1
	PerfectMatch( 'a' ); // #2
}
