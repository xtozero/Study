# 데이터형이 아닌 템플릿 파라미터
## 개요
- 함수 템플릿, 클래스 템플릿에서 템플릿 파라미터를 데이터형이 아닌 일반적인 값으로 명시할 수 있다.

## 데이터형이 아닌 클래스 템플릿 파라미터
- 데이터형이 아닌 템플릿 파라미터를 통해 고정된 크기의 배열을 사용한 스택을 구현할 수 있다.
```c++
// NTP_01.cpp
template <typename T, int MAXSIZE>
class Stack
{
private:
	T m_elems[MAXSIZE];
	int m_numElems = 0;

public:
	void push( const T& value );
	void pop( );
	T top( ) const;

	bool empty( ) const
	{
		return m_elems.empty( );
	}

	Stack( ) = default;
	Stack( const Stack<T, MAXSIZE>& stack );
	Stack( Stack<T, MAXSIZE>&& stack ) = delete;
	Stack<T, MAXSIZE>& operator=( const Stack<T, MAXSIZE>& stack );
	Stack<T, MAXSIZE>& operator=( Stack<T, MAXSIZE>&& stack ) = delete;
};

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push( const T& value )
{
	if ( m_numElems == MAXSIZE )
	{
		throw std::out_of_range( "Stack<>::push() : stack is full" );
	}

	m_elems[m_numElems] = value;
	++m_numElems;
}

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::pop( )
{
	if ( m_numElems <= 0 )
	{
		throw std::out_of_range( "Stack<>::pop() : empty stack" );
	}

	--m_numElems;
}

template <typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::top( ) const
{
	if ( m_numElems <= 0 )
	{
		throw std::out_of_range( "Stack<>::top() : empty stack" );
	}

	return m_elems[m_numElems - 1];
}

template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>::Stack( const Stack<T, MAXSIZE>& stack )
{
	*this = stack;
}

template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>& Stack<T, MAXSIZE>::operator=( const Stack<T, MAXSIZE>& stack )
{
	m_numElems = stack.m_numElems;
	memcpy_s( m_elems, MAXSIZE, stack.m_numElems, stack.m_numElems );
	return *this;
}
```
- 데이터형이 아닌 템플릿 파라미터 MAXSIZE는 int형으로 스택 요소의 배열 크기를 결정한다.
- 또한 스택이 꽉 찼는지 검사할 때도 사용된다.
- 이 Stack클래스를 사용하려면 요소의 데이터형과 함께 최대 크기도 명시해야 한다.
```c++
// NTP_01.cpp
int main( )
{
	try
	{
		Stack<int, 20> int20Stack;
		Stack<int, 40> int40Stack;
		Stack<std::string, 40> stringStack;

		int20Stack.push( 7 );
		std::cout << int20Stack.top( ) << std::endl;
		int20Stack.pop( );

		stringStack.push( "hello" );
		std::cout << stringStack.top( ) << std::endl;
		stringStack.pop( );
		stringStack.pop( );
	}
	catch ( std::exception ex )
	{
		std::cerr << "Exception" << ex.what( ) << std::endl;
		return EXIT_FAILURE;
	}
}
```
- 각 템플릿 인스턴스는 자신만의 데이터형을 갖는다.
> int20Stack, int40Stack은 서로 다른 데이터형이므로 둘 사이에 묵시적이거나 명시적인 형변환이 이루어질 수 없다.

- 데이터형이 아닌 템플릿 파라미터도 기본값을 명시할 수 있다.
```c++
// NTP_01.cpp
template <typename T = int, int MAXSIZE = 100>
class Stack
{
    ...
};
```
## 데이터형이 아닌 함수 템플릿 파라미터
- 함수 템플릿에도 데이터형이 아닌 템플릿 파라미터를 사용할 수 있다.
```c++
template <typename T, int VAL>
T addValue( const T& x )
{
	return x + VAL;
}
```
- 이런 종류의 함수는 함수나 연산이 파라미터로 사용될 때 유용하다.
> 함수를 인자로 받는 함수를 고계함수(higher-order function) 라 한다.

```c++
std::vector<int> source = { 10, 20, 30, 40, 50, 60 };
std::vector<int> dest( source.size() );

std::transform( source.begin( ), source.end( ), dest.begin( ), addValue<int, 5> );
```
## 데이터형이 아닌 함수 파라미터에 대한 제약
- 데이터형이 아닌 함수 파라미터에는 몇 가지 제약이 있다. [(참고 사이트)](http://en.cppreference.com/w/cpp/language/template_parameters#Template_template_parameter)
- C++17 이전 까지는 아래와 같다.

1\. 정수형이고 [산술타입](http://en.cppreference.com/w/c/language/arithmetic_types)의 경우 컴파일 시간에 평가되어야 한다.
```c++
// NTP_03.cpp
template <typename T, int N>
class IntegralArithmetic {};

// 정수이고 산술 타입인 경우
IntegralArithmetic<int, 10> intLiteral;

//int n = 10;
//IntegralArithmetic<int, n> intVariable; // error

const int cn = 10;
IntegralArithmetic<int, cn> constInt;
```

2\. 포인터형의 경우 null 포인터나 std::nullptr_t 타입으로 컴파일 시간에 평가되거나 정적 지속성( static storage duration )과 링크( externel 혹은 internel )를 가져야 한다.
> 특히 문자열 리터럴, 배열 요소의 주소, 비정적 멤버 변수의 주소는 템플린 인자로 사용될 수 없다.

> 정적 지속성( static storage duration )은 프로그램이 시작될 때 자동으로 할당되어 프로그램이 끝나면 자동으로 해제되는 생명주기를 같는 객체를 뜻한다. ex) 전역 변수, static 변수


```c++
// NTP_04.cpp
template <char* P>
class PointerType {};

// 전역 변수
char g_c;
extern char g_ec;
constexpr char* pNull = nullptr;
//const char* pNull = nullptr; -> const는 error
constexpr char* gStringLiteral = "Hello";
char gArray[10] = {};

class ClassA
{
public:
	static char success;
	char error;
};

ClassA errorClass;

...

// 포인터 형일 경우
PointerType<&g_c> globalChar;
PointerType<&g_ec> externGlobalChar;
PointerType<pNull> nullPointer;
// PointerType<nullptr> nullptrValue; // -> gcc에서는 성공, vs2015 community 버전에서 error

PointerType<gStringLiteral> stringLiteral; // error
PointerType<&gArray[0]> AddressofArray; // error

PointerType<&errorClass.error> AddressofNonStaticMember; // error
PointerType<&errorClass.success> AddressofStaticMember; // gcc에서 error, vs2015 community 버전에서 성공
PointerType<&ClassA::success> AddressofStaticMember;
```

3\. 함수포인터형의 경우 컴파일 시간에 null 포인터로 평가되거나 링크를 가져야 한다.
```c++
// NTP_05.cpp
constexpr void( *globalNullFuncPtr )() = nullptr;
void normalFunc( ) {}

...

// 함수 포인터 형일 경우
FunctionPointerType<globalNullFuncPtr> NullFuncPtr;
FunctionPointerType<&normalFunc> AddressOfFunc;
}
```

4\. lvalue 참조형의 경우 임시 변수이거나 이름이 없는 lvalue이거나 링크가 없는 lvalue이면 안된다.( 즉 인자는 반드시 링크가 있어야 한다. )
```c++
// NTP_06.cpp
int Foo( ) { return 1; }
int gn = 0;

...

LvalueReference<Foo( )> FunctionReturn; // error
	
int n;
LvalueReference<n> Nolinkage; // error
LvalueReference<gn> linkage;
```

5\. 클래스 멤버에 대한 포인터형의 경우 &Class::Member로 표현되거나 null 포인터나 std::nullptr_t 타입으로 컴파일 시간에 평가되어야 한다.
```c++
// NTP_07.cpp
class ClassA
{
public:
	char member;
};

ClassA errorClass;

template <char ClassA::*P>
class MemberPointer {};

...

// 클래스 멤버 포인터일 경우
MemberPointer<&ClassA::member> AddressofMember;
MemberPointer<nullptr> nullPointer;
```
- 그 외 템플릿 인자로 사용할 수 없는 경우를 예를 들면 아래와 같다.
```c++
// NTP_08.cpp
// 실수형은 불가
template <double VAT>
double process( double v )
{
	return v * VAT;
}

// 클래스형 객체는 불가
template <std::string name>
class MyClass {};
``` 

- C++17 이후 부터는 아래와 같다.

1\. 기본적으로 컴파일 시간에 평가될 수 있는 어떤 타입도 가능하다.

2\. 다만 한가지 예외가 있는데 참조와, 포인터 타입의 데이터형이 아닌 함수 파라미터는 아래의 변수들을 인자로 사용할 수 없다.
	
1. SubObject
	> SubObject는 다른 객체에 포함된 객체이다, ex ) 클래스의 멤버, 배열의 요소, 

2. 임시 객체
3. 문자열 리터럴
4. typeid의 결과
5. 미리 정의된 변수 \_\_func\_\_