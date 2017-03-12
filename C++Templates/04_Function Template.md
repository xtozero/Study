# 함수 템플릿
## 개요
- 함수 템플릿은 다양한 데이터형에 대해 호출될 수 있는 함수이다.
- 즉 함수 템플릿은 함수 군을 대표한다.
- 함수의 일부 요소가 정해지지 않았을 뿐 일반 함수와 거의 같으며 이렇게 정해지지 않고 남은 요소를 파라미터화됐다고 한다.

## 함수 템플릿 정의
```c++
template <typename T>
T add( T lhs, T rhs )
{
    return lhs + rhs;
}
```
- 이 함수의 파라미터 데이터형은 템플릿 파라미터 T로서 아직 정해지지 않았다.
- 템플릿 파라미터는 다음과 같은 문법을 사용해 명시돼야 한다.
> template < parameter-list >

- T는 데이터형 파라미터로 어떤 이름을 사용해도 좋지만 주로 T를 사용한다.
- 데이터형 파라미터는 임의의 데이터형을 대변하기 위해 사용되며 템플릿이 사용하는 동작을 제공한다면 이 함수의 인자로 어떠한 데이터형이든 사용할 수 있다.
> 위 함수는 + 연산자를 제공해야 한다.

- 데이터형 파라미터를 정의할 때 typename 대신 class를 사용할 수 있다.
> struct를 typename 대신 사용할 수 없다.

```c++
template <class T>
T add( T lhs, T rhs )
{
    return lhs + rhs;
}
```

## 함수 템플릿 사용법
- add 함수 템플릿은 다음과 같이 사용할 수 있다.
```c++
int main()
{
	cout << add( 1, 2 ) << endl; // 3이 출력
	cout << add( 3.1, 4.1 ) << endl; // 7.2이 출력
	cout << add( string( "hello " ), string( "world" ) ) << endl; // "hello world" 출력
}
```
- 일반적으로 템플릿은 어떤 데이터형이라도 다룰 수 있는 하나의 실체를 생성하지 않는다.
- 위의 예제는 세 가지 데이터형에 맞는 함수가 생성된다.
```c++
// int형으로 호출하는 경우 아래와 같은 함수가 생성된다.
inline int add( int lhs, int rhs )
{
	return lhs + rhs;
}
```
- 템플릿 파라미터를 실제 데이터형으로 바꾸는 작업을 인스턴스화( instantiation )이라고 한다. 이를 통해 템플릿의 인스턴스가 생성된다.
> OOP에서 인스턴스는 클래스의 객체를 의미한다.

- 함수 템플릿 내에서 사용된 모든 연산자를 지원하지 않는 데이터형에 대해서 템플릿을 인스턴스화하면 컴파일 오류가 발생한다.
```c++
UnsurpportedOperator lhs;
UnsurpportedOperator rhs;

// + 연산자를 지원하지 않아 에러
add( lhs, rhs );
```
- 이를 위해 템플릿은 두 번 컴파일된다.
	
	1\. 인스턴스화 없이 템플릿의 문법을 검사. ex) 세미콜론이 빠졌는지 등을 확인

	2\. 인스턴스화되는 시점에서 호출이 유효한지 확인하기 위해서 템플릿 코드를 검사. ex) 지원하지 않는 함수 호출과 같은 잘못된 호출이 있는지 확인

- 이렇게 두 번 컴파일되기 때문에 인스턴스화되는 시점에서 템플릿의 정의를 알아야 한다.
> 일반 함수에서는 컴파일과 링크가 분리되어 함수의 선언만으로도 함수를 컴파일하기에 충분하다.

## 인자 추론
- 함수 템플릿을 호출하면 인자를 기반으로 템플릿 파라미터가 결정된다.
- 인자 추론 과정에서 데이터형 변환은 적용되지 않는다.
```c++
add( 4, 7 ); // ok T는 두 인자에 대해 int
add( 4, 4.2 ); // error 첫 번째 T는 int 두 번째 T는 double

// 정상적으로 호출하기 위해서는 아래와 같이 호출하여야 한다.
cout <<  add( static_cast<double>(4), 4.2 ) << endl; // 두 인자가 일치하도록 명시적으로 형 변환
cout <<  add<double>( 4, 4.2 ) << endl; // T의 데이터형을 명시

template <typename T, typename U>
decltype( T() + U() ) new_add( T lhs, U rhs )
{
	return lhs + rhs;
}

cout <<  new_add( 4, 4.2 ) << endl; // 파라미터가 다른 데이터형을 가질 수 있도록 명시
```

## 템플릿에서의 인자 추론 방식
- 함수 템플릿의 선언은 대체로 이런 모습이다.
```c++
template <typename T?
void f(ParamType param) {}

f(expr) // 어떤 표현식으로 f를 호출
```
- 컴파일러는 expr을 통해서 함수 템플릿의 T와 ParamType을 추론한다.
> ParamType에 const와 같은 수식어가 붙기 때문에 T와 ParamType은 다를 수 있다.

- 템플릿의 추론 방식은 ParamType의 모양에 따라 3가지로 나눌 수 있다.

	- **ParamType이 reference 형식(T&)**일 경우

		1\. expr이 reference 형식이면 reference 부분을 무시한다. <br>
		
		2\. expr형식을 ParamType에 대해서 pattern-matching 방식으로 대응시켜 T를 결정한다.
		
		```c++
		template <typename T>
		void CallByReference( T& param ) {}

		int x = 27;
		int& rx = x;
		const int cx = x;
		const int& crx = x;

		CallByReference( x );		// T: int ParamType : int&
		CallByReference( rx );		// T: int ParamType : int&
		CallByReference( cx );		// T: const int, ParamType : const int&
		CallByReference( crx );		// T: const int, ParamType : const int&
		```

	- **ParamType이 forwarding reference 형식(T&&)**일 경우

		1\. expr이 lvalue이면 T와 ParamType 모두 왼 값 참조로 추론된다. <br>
		
		2\. expr이 rvalue이면 1의 규칙이 적용된다.
	
		```c++
		template <typename T>
		void CallByForwardReference( T&& param ) {}

		// T&& 인 경우
		CallByForwardReference( x );		// T: int& ParamType : int&
		CallByForwardReference( rx );		// T: int& ParamType : int&
		CallByForwardReference( cx );		// T: const int&, ParamType : const int&
		CallByForwardReference( crx );		// T: const int&, ParamType : const int&
		CallByForwardReference( 27 );		// T: int, ParamType : int&&
		```

	- **1, 2에 해당하지 않는 경우**

		1\. expr이 reference 형식이면 reference 부분을 무시한다. <br>
		
		2\. expr에 const volatile mutable 키워드가 존재하면 해당 키워드를 무시한다.
		
		```c++
		template <typename T>
		void CallByValue( T param ) {}

		class TypeDeduction
		{
		public:
			mutable int m_value;
		};

		// T인 경우
		CallByValue( x );		// T: int ParamType : int
		CallByValue( rx );		// T: int ParamType : int
		CallByValue( cx );		// T: int, ParamType : int
		CallByValue( crx );		// T: int, ParamType : int

		TypeDeduction t = { 0 };
		auto deducted = t.m_value; // T: int ParamType : int
		```
## 템플릿 파라미터
- 함수 템플릿은 두 종류의 파라미터를 가진다.

1\. 템플릿 파라미터 : 함수 템플릿 이름 앞 꺾쇠 내에 선언된 것
> template <typename T>

2\. 호출 파라미터 : 함수 템플릿 이름 뒤 괄호 안에 선언된 것
> ...add( T lhs, T rhs )

- 템플릿 파라미터는 원하는 대로 얼마든지 사용할 수 있지만 함수 템플릿에서는 기본 템플릿 인자를 명시할 수 없다. ( c++ 11 지원 이전 컴파일러까지 )
- 두 호출 파라미터를 다르게 사용하여 add 함수를 정의하면 아래와 같이 정의할 수 있다.
```c++
template <typename T1, typename T2>
T1 add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

add( 1.0f, 1 );
```
- 두 호출 파라미터를 사용한 add는 서로 다른 자료형을 사용하여 호출할 수 있지만, 반환형이 선언되어야만 한다는 문제가 있다.
- 이 문제를 개선하기 위해서 아래와 같이 템플릿 파라미터를 추가하여 반환형을 결정할 수 있다.
```c++
template <typename T1, typename T2, typename R>
R add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

// 반환형을 지정할 수 있도록 한 add 버전 1
add<int, double, double>( 1, 1.f );
```
- 템플릿과 호출 파라미터 사이에 어떤 관계도 없거나 템플릿 파라미터가 결정될 수 없으면 템플릿 인자를 함수 호출 시에 명시적으로 지정해야 한다.
- 함수를 호출할 때마다 매번 모든 파라미터를 지정하는 것은 매우 번거로운 일인데 파라미터의 순서를 바꾸는 것으로 이를 개선할 수 있다.
```c++
template <typename R, typename T1, typename T2>
R add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

// 반환형을 지정할 수 있도록 한 add 버전 2
add<double>( 1, 1.f );
```
- 첫 번째 파라미터는 명시적으로 지정하고 나머지는 인자를 통해 int와 double로 추론된다.
- c++14 에서는 다음과 같이 좀 더 간결한 방법이 가능하다.
```c++
template <typename T1, typename T2>
decltype( T1() + T2() ) new_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

template <typename T1, typename T2>
decltype( auto ) auto_add( T1 lhs, T2 rhs )
{
	return lhs + rhs;
}

new_add( 5.1234, 1 );
auto_add( 2.f, 2L );
```
## 오버로딩 함수 템플릿
- 일반 함수처럼 함수 템플릿도 오버로딩 할 수 있다.
```c++
int max( const int& lhs, const int& rhs )
{
	cout << "max( int, int )" << endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& lhs, const T& rhs )
{
	cout << "max( T, T )" << endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T max( const T& first, const T& second, const T& third )
{
	cout << "max( T, T, T )" << endl;
	return max( max( first, second ), third );
}

// 함수 템플릿의 오버로딩
max( 7, 42, 68 );			// 세 인자를 위한 템플릿 호출
max( 7.0, 42.0 );			// max<double> 호출
max( 'a', 'b' );			// max<char> 호출
max( 7, 42 );				// nontemplate 함수 max 호출
max<>( 7, 42 );				// max<int> 호출
max<double>( 7, 42 );		// max<double> 호출
max( 'a', 42.7 );			// nontemplate 함수 max 호출
```
- 함수 템플릿이 템플릿이 아닌 함수와 같은 자료형을 가지고 인스턴스화된 경우에는 템플릿이 아닌 함수가 선호된다.
> max( 7, 42 );				// nontemplate 함수 max 호출

- 함수 템플릿이 호출 인자에 좀 더 잘 맞는 함수를 생성한 경우에는 템플릿을 선택한다.
> max( 7.0, 42.0 );			// max<double> 호출 <br>
> max( 'a', 'b' );			// max<char> 호출

- 빈 템플릿 인자 목록을 명시하거나 명시적으로 인자를 지정할 수도 있다.
> max<>( 7, 42 );				// max<int> 호출 템플릿 함수만 고려되고 호출 인자에서 템플릿 파라미터가 추론되어야 한다. <br>
> max<double>( 7, 42 );		// max<double> 호출

- 템플릿에서는 일반 함수와 달리 자동으로 데이터형을 변환하지 않기 때문에 아래 함수는 템플릿이 아닌 함수가 호출된다.
> max( 'a', 42.7 );			// nontemplate 함수 max 호출 <br>
> max( const T& lhs, const T& rhs )는 자동으로 데이터형을 변환하지 않아 템플릿 파라미터는 하나지만 char 혹은 double인 템플릿 인자를 가질 수 있어 모호하다.

- 포인터와 일반 C 문자열에 대한 최댓값 템플릿을 오버로딩하는 예제를 살펴보자
```c++
template <typename T>
T max( const T& lhs, const T& rhs )
{
	cout << "max( T, T )" << endl;
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
T* const& max( T* const & a, T* const & b )
{
	cout << "T* const & a, T* const & b" << endl;
	return *a < *b ? b : a;
}

const char* const& max( const char* const& a, const char* const& b )
{
	cout << "max( const char* const& a, const char* const& b )" << endl;
	return strcmp( a, b ) < 0 ? b : a;
}

string hey = "hey";
string you = "you";

max( hey, you );

int a = 1;
int b = 2;
int* p1 = &b;
int* p2 = &a;

max( p1, p2 );

const char* s1 = "Alpha";
const char* s2 = "Bong";
max( s1, s2 );
```

- 일반적으로 함수 템플릿을 오버로딩할 때는 필요 이상으로 수정하지 않는 것이 좋다.
- 파라미터의 수를 바꾼다든지, 템플릿 파라미터를 명시하는 것 정도만 수정하는 편이 낫다.
- 예를 들어 **참조자를 넘겨받는 max() 템플릿을 오버로딩하여 두 C 문자열을 값으로 넘겨받게 했다고 하면 세 개의 C 문자열에서의 최대값을 계산하는 버전의 max를 사용할 수 없다.**
```c++
template <typename T>
const T& new_max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

const char* new_max( const char* lhs, const char* rhs )
{
	return strcmp( lhs, rhs ) < 0 ? rhs : lhs;
}

template <typename T>
const T& new_max( const T& first, const T& second, const T& third )
{
	return new_max( new_max( first, second ), third ); // max( first, second )가 만든 임시 지역 변수가 함수에 의해 참조자로 반환될 수도 있다. )
}

const char* st1 = "Template";
const char* st2 = "Study";
const char* st3 = "Successfull";
cout << new_max( st1, st2, st2 ) << endl;
```

- 또 다른 예로 함수를 호출했을 때 모든 오버로딩 함수가 사용 가능한지 여부가 문제가 될 수도 있다.
```c++
template <typename T>
const T& min( const T& lhs, const T& rhs )
{
	cout << "min( T, T )" << endl;
	return lhs < rhs ? lhs : rhs;
}

template <typename T>
const T& min( const T& first, const T& second, const T& third )
{
	cout << "min( T, T, T )" << endl;
	return min( min( first, second ), third ); // int를 위해서라도 템플릿 버전이 사용될 수 있다.
											   // 비 템플릿 함수 선언이 너무 늦게 나왔기 떄문
}

const int& min( const int& lhs, const int& rhs )
{
	cout << "min( const int& lhs, const int& rhs )" << endl;
	return lhs < rhs ? lhs : rhs;
}

min( 1, 2, 3 ); // vs 2015 community에서는 min( const int& lhs, const int& rhs )호출 g++에서는 빌드 에러
```