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
// void PerfectMatch( char ) {} 추가시 모호함 발생

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

// void count( short ) {} int로의 데이터 승격이 일어나지 않아도 되므로 더 선호된다.

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
	
    // Ambigouous(1); error 후보가 여러개 있어 모호한 호출
	
	// Combine( 1, 2 ); // error C2666: 'Combine': 2개 오버로드에 비슷한 변환이 있습니다. 

	// 완벽한 일치
	std::cout << "Perfect match overload sample" << std::endl;	
	PerfectMatch( 1 ); // #1 이 호출

	std::cout << "Minor adjust overload sample" << std::endl;
	int arr[5] = {};
	MinorAdjust( arr ); // 배열을 포인터로 변환(decay)

	// 작은 수정을 통한 일치
	int* pArr = arr;
	int** ppArr = &pArr;
	MinorAdjust( ppArr ); // #2의 주석을 풀면 완벽한 일치로 #2
			      // #2가 없으면 int** -> int const* const*로 수정하여 #3 호출
	
	// 승격을 통한 일치
	std::cout << "Promotion overload sample" << std::endl;	
	Promotion( true ); // bool -> int 데이터형 승격으로 #2 호출
	
	// 표준 변환을 통한 일치
	std::cout << "Standard conversion sample" << std::endl;	
	StandardConversion( true ); // bool -> char 로 표준 변환이 적용되서 #1 호출

	// 사용자 변환을 통한 일치
	std::cout << "Userdefined conversion sample" << std::endl;
	UserdefinedConversion( 1 );

	// 생략을 통한 일치
	std::cout << "Ellipsis conversion sample" << std::endl;	
	Ellipsis( 1 );

	// 템플릿 인자 추론과 오버로딩 해석의 순서
	TemplateFunction<int>( 1 ); //ok
	// TemplateFunction( 1 ); // error

	// 멤버 함수를 위한 묵시적 인자에 관한 오버로딩 동작
	BadString str( "correckt" );
	// str[5] = 'c'; // "[]" 연산자 중 두 개 이상이 이 피연산자와 일치합니다.
		      // 기본 제공 연산자 "pointer-to-object[interger]
		      // 함수 "BadString::operator[]( size_t )"
	

	// 완벽한 일치 상세
	char c = 'a';
	PerfectMatch( c ); // #1
	PerfectMatch( 'a' ); // #2

	Wonder device;
	device.tick( ); // #1
	device.tack( ); // #3 Wonder::tack 함수 중에 const가 아닌 함수가 없으므로

	// 비템플릿 선호
	// return f( 0 ); error 반환 값이 없는 비 템플릿 함수가 선택

	// 묵시적 변환은 연속적인 적용
	Derived object;
	count( object ); // ok Derived -> Base -> short -> int 순으로 변환되어 잘 동작한다.

	// 포인터 변환
	int* p = nullptr;
	check( p ); // bool 형으로의 변환은 다른 표준 데이터형 변환보다 좋지 않은 것으로 취급.

	Machine* machine = nullptr;
	serialize( machine ); // #2 상속 관계의 포인터로의 변환이 void*로의 변환 보다 선호된다.

	// Functor와 대리함수
	IndirectFunctor functor;
	//functor( 3, 5 ); // error 모호한 호출 operator()는 묵시적인 *this 파라미터에 대해서는 잘 맞지만 두번째 인자가 FuncType보다 잘 맞지 않으므로 우열을 가릴 수 없다.

	// 그 밖의 오버로딩 문맥
	// 함수 주소가 필요한 경우
	void( *pFunc )(float) = n_elements;
	pFunc( 1 ); // #2

	// 초기화시 적절할 생성자를 호출하거나 변환 연산자를 선택할 경우
	BigNum bn1( 100103 ); // #1
	BigNum bn2( "7057103224.095764" ); // #4
	int in = bn1; // #6
}
