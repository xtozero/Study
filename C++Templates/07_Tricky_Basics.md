# 고급 기능
## 개요
- 템플릿을 사용하는데 필요한 기본적인 템플릿의 기능을 알아본다.
- typename 키워드의 용도, 멤버 함수와 중첩된 클래스를 템플릿으로 정의하는 법, 템플릿 템플릿 파라미터, 0 초기화, 문자열을 인자로 사용하는 방법에 대한 세부 사항을 알아본다.

## typename 키워드
- typename 키워드는 템플릿 내에서 식별자가 **데이터형임을 명시**하기 위해서 사용된다.
```c++
// TB_01.cpp
#include <iostream>
#include <typeinfo>

class Type
{
public:
	using SubType = int;
};

template <typename T>
class MyClass
{
public:
	typename T::SubType* ptr;
};

int main( )
{
	MyClass<Type> v;
	std::cout << typeid(v.ptr).name( ) << std::endl;
}
```
- 만약 식별자가 데이터형을 명시하지 않는다면 SubType은 **정적 멤버로 간주**될 수 있다.
- 그러면 SubType은 실제 변수나 객체가 될 수 있고 T::SubType * ptr는 클래스 T의 **정적 멤버인 SubType을 ptr과 곱하는 연산**이 된다.
- 템플릿 코드내에서 STL 컨테이너의 반복자에 접근할 때가 전형적인 typename 사용 예이다.
```c++
// TB_01.cpp
template <typename T>
void printcoll( const T& coll )
{
	typename T::const_iterator pos;

	typename T::const_iterator end( coll.end( ) );

	for ( pos = coll.begin( ); pos != end; ++pos )
	{
		std::cout << *pos << ' ';
	}
	std::cout << std::endl;
}

...

std::vector<int> collection = { 1, 1, 2, 3, 5, 8, 13, 21 };
printcoll( collection );
```

## .template 생성
- .template를 사용한 생성방법이 필요할 때가 있다. 아래 코드는 vs 2015 community에서 정상 컴파일되지만, gcc에서는 컴파일 에러이다.
```c++
// TB_02.cpp
#include <bitset>
#include <iostream>

template <int N>
void printBitset( const std::bitset<N>& bs )
{
	// .template로 사용하지 않으면 gcc에서 컴파일 에러
	std::cout << bs.to_string<char, std::char_traits<char>, std::allocator<char>>( ) << std::endl;
}

int main( )
{
	std::bitset<10> bs = 1;
	// gcc에서 인자를 통해서 추론 실패
	printBitset( bs );
}

/*
// gcc에서 컴파일되는 코드
#include <bitset>
#include <iostream>

template <int N>
void printBitset( const std::bitset<N>& bs )
{
	std::cout << bs.template to_string<char, std::char_traits<char>, std::allocator<char>>( ) << std::endl;
}

int main( )
{
	std::bitset<10> bs = 1;
	printBitset<10>( bs );
}
*/
```
- 마침표 앞의 객체가 템플릿 파라미터에 종속된 경우 ( bs는 템플릿 파라미터 N에 종속되어 있다. )에는 "<" 토큰이 템플릿 인자 목록의 시작을 나타내지 않고 "작다"라는 의미로 사용된다.
- 따라서 .template 표기법은 템플릿 내에서만 사용되며, 템플릿 파라미터에 종속된 무언가의 뒤에서만 사용된다.

## this-> 사용
- 기본 클래스가 있는 클래스 템플릿에서 기본 클래스로부터 상속받은 x가 있을 때 x라는 이름이 항상 this->x를 의미하진 않는다.
```c++
//TB_03.cpp
#include <iostream>

void bar( ) { std::cout << "bar()" << std::endl; }

template <typename T>
class Base
{
public:
	void bar( ) { std::cout << "Base::bar()" << std::endl; }
};

template <typename T>
class Derived : Base<T>
{
public:
	void foo( )
	{
		bar( ); // 외부의 bar가 호출되거나 오류가 발생한다.
				// vs 2015 community 버전 gcc에서 외부 bar가 호출
	}
};

int main( )
{
	Derived<int> d;
	d.foo( );
}
```
- 위의 예제에서 foo() 내의 bar라는 기호를 해석할 때, Base에서 정의된 bar()는 절대로 고려되지 않는다. 따라서 오류가 발생하거나, 다른 bar가 호출된다.
- 기본 클래스에서 선언된 기호를 사용할 때에는 this->나 Base<T>::를 붙여 한정함으로써 해당 기호가 템플릿 파라미터에 종속되도록 하는 것이 좋다.
```c++
//TB_03.cpp
template <typename T>
class Derived : Base<T>
{
public:
...

	void goo( )
	{
		this->bar( );
		Base<T>::bar( );
	}
};

...

d.goo( );
```
- 템플릿 클래스에서 **모든 모호함을 피하고 싶다면 모든 멤버에 접근할 때마다 이와 같은 방식으로 한정**시키는 것이 좋다.

## 멤버 템플릿
- 클래스 멤버도 템플릿이 될 수 있다. 중첩된 클래스나 멤버 함수도 템플릿도 될 수 있다.
```c++
// TB_04.cpp
// 만약 멤버 템플릿 할당 연산자가 없었다면
Stack<int> intStack1, intStack2;	// int를 위한 스택
Stack<float> floatStack;			// float 를 위한 스택

intStack1 = intStack2;				// OK : 같은 데이터형의 스택
floatStack = intStack1;				// ERROR : 다른 데이터형의 스택
```
- 멤버 함수에 템플릿을 사용하면 위와 같은 예제에서 다른 데이터형의 스택을 대입하지 못하는 현상을 해결할 수 있다.
```c++
// TB_04.cpp
template <typename T>
class Stack
{

	...

	template <typename U>
	Stack<T>& operator= ( const Stack<U>& stack )
};

template <typename T>
template <typename U>
Stack<T>& Stack<T>::operator=( const Stack<U>& stack )
{
	if ( this == &stack )
	{
		return *this;
	}

	m_elems.clear( );
	Stack<U> copy( stack ); // 서로 다른 데이터형이므로 private에 접근할 수 없어 카피해서 복사한다.
	std::deque<U> temp; // 순서를 맞추기 위해서 deque을 임시 저장 컨테이너로 이용한다.

	while ( !copy.empty( ) )
	{
		temp.push_front( copy.top( ) );
		copy.pop( );
	}

	for ( const auto& elem : temp )
	{
		m_elems.push_back( elem );
	}

	return *this;
}

...

Stack<int> intStack;	// int를 위한 스택
intStack.push( 1 );
intStack.push( 2 );
intStack.push( 3 );
intStack.push( 4 );
intStack.push( 5 );

Stack<float> floatStack;			// float 를 위한 스택

floatStack = intStack;				// OK : 다른 데이터형의 스택
```
- 멤버 템플릿을 정의하는 문법은 아래와 같이 탬플릿 파라미터 T를 사용하는 템플릿 안에 템플릿 파라미터 U를 쓰는 내부 템플릿을 정의하였다.
```c++
// TB_04.cpp
template <typename T>
template <typename U>
...

```
- 이렇게 구현된 스택은 어떤 데이터형의 스택이라도 할당할 수 있는 것처럼 보이겠지만 원래 스택의 요소를 목적 스택에 옮길때 데이터형 검사가 이루어진다.
```c++
// TB_04.cpp
Stack<double> doubleStack;
Stack<std::string> stringStack;	

doubleStack = stringStack; // std::string은 double로 변환될 수 없음. operator=의 m_elems.push_back( elem ); 에서 검사가 이루어진다.
```
- **하지만 템플릿 할당 연산자가 기본 할당 연산자를 대신하지는 않는다.** 같은 데이터형을 스택에 할당할 때에는 기본 할당 연산자가 호출된다.
```c++
// TB_04.cpp

Stack<char> charStack1;
Stack<char> charStack2;

charStack1 = charStack2; // 기본 할당 연산자가 호출
```

## 템플릿 템플릿 파라미터
- 템플릿 템플릿 파라미터는 템플릿 파라미터 자체가 클래스 템플릿인 경우이다.
- 이전의 스택 코드를 보면 다양항 내부 컨테이너를 사용할 수 있게 하기 위해서 요소의 데이터형을 두번 명시해야 했다.
```c++
Stack<int, std::vector<int>> vStack;
```
- 템플릿 템플릿 파라미터를 사용하면 요소의 데이터형을 중복해서 명시하지 않아도 된다.
```c++
Stack<int, std::vector> vStack;
```
- 템플릿 템플릿 파라미터를 사용한 스택은 아래와 같다.
```c++
// TB_05.cpp

template <typename T, template<typename ELEM> class CONT = std::deque>
class Stack
{
private:
	CONT<T> m_elems;

public:
	void push( const T& elems );
	void pop( );
	T top( ) const;
	bool empty( ) const
	{
		return m_elems.empty( );
	}

	Stack( ) = default;
	Stack( const Stack<T, CONT>& stack );
	Stack( Stack<T, CONT>&& stack );
	Stack<T, CONT>& operator=( const Stack<T, CONT>& stack );
	Stack<T, CONT>& operator=( Stack<T, CONT>&& stack );
};
```
- 템플릿 템플릿 파라미터를 위해서 typename을 사용할 수도 있으나 CONT는 클래스를 정의하기 위해 사용됐으므로 class 키워드를 사용해서 선언해야만 한다. ( [c++ 17 이전](http://en.cppreference.com/w/cpp/language/template_parameters) )
- 멤버 함수도 템플릿 템플릿 파라미터에 맞게 작성해야 한다.
```c++
template <typename T, template<typename> class CONT>
void Stack<T, CONT>::push( const T& value )
{
	m_elems.push_back( value );
}
```
- 하지만 위 예제의 Stack을 사용하려고 하면 에러가 발생한다. 이는 템플릿 템플릿 인자의 파라미터가 자신이 치환할 템플릿 템플릿 파라미터의 파라미터들과 정확하게 일치해야만 하기 때문이다.
- **템플릿 템플릿 인자의 기본 인자는 이 같은 검사에서 고려되지 않으므로 기본 인자를 가진 파라미터에 명시적으로 인자를 제공**하지 않으면 템플릿 템플릿 인자와 템플릿 템플릿 파라미터가 정확히 일치할 수 없다.
- 이 예제에서 STL deque는 하나 이상의 템플릿 파라미터(Allocator 파라미터) 를 가진다.
```c++
// deque

// TEMPLATE CLASS deque
template<class _Ty,
	class _Alloc = allocator<_Ty> >
	class deque
		: public _Deque_alloc<_Deque_base_types<_Ty, _Alloc> >
	{	// circular queue of pointers to blocks

	...
```
- 따라서 다음과 같이 Allocator 파라미터를 제공해야 정상적으로 동작한다.
```c++
template <typename T,
		template<typename ELEM, typename Alloc = std::allocator<ELEM> >
		typename CONT = std::deque> // c++11 지원 컴파일러에서 typename을 사용해도 정상적으로 컴파일. gcc, vs 2015 community 동일
class Stack
{

...

};

int main( )
{
	Stack<int, std::vector> vStack;
	vStack.push( 42 );
	vStack.push( 7 );
	std::cout << vStack.top( ) << std::endl;
	vStack.pop( );
}
```

## 0 초기화
- int, double과 같은 내장 데이터형(built-in type)에는 기본값으로 초기화하는 기본생성자가 없다. 따라서 지역 변수는 초기화되기 전까지는 쓰레기값을 가진다.
- 템플릿형 변수가 기본값으로 적절하게 초기화되기 원한다면 이러한 특성은 문제가 된다.
```c++
// TB_07.cpp
template <typename T>
T foo( )
{
	T x; // 적절할 초깃값을 정하기 곤란하다.
	return x;
}
```
- 이와 같은 문제를 해결하기 위해 **내장 데이터형에 대해서 0으로 초기화하는 기본 생성자를 명시적으로 호출**할 수 있다.
```c++
template <typename T>
T goo( )
{
	T x( ); // 내장 데이터형에 대해서 0으로 초기화된다.
	return x;
}
```
- 파라미터화된 클래스의 멤버 변수를 적절히 초기화하는데 이를 이용할 수 있다.
```c++
// TB_07.cpp
template <typename T>
class MyClass
{
public:
	T x;

	MyClass( ) : x( )
	{

	}

	//or in c++11

	T y = T( );
};
```

## 함수 템플릿에 문자열 리터럴을 인자로 사용
- 함수 템플릿에 문자열 리터럴을 인자로 사용할 경우 문제가 되는 경우가 있다.
```c++
// TB_08.cpp
#include <string>

template <typename T>
const T& max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

int main( )
{
	std::string s;

	max( "apple", "peach" ); // ok
	max( "apple", "banana" ); // error
	max( "apple", s ); // error
}
```
- 문자열 리터럴의 길이에 따라 다른 배열형으로 정의되어 error가 발생한다. 하지만 참조자가 아닌 파라미터를 선언하면 다른 크기를 가지는 문자열 리터럴도 사용할 수 있다.
```c++
// TB_08.cpp
template <typename T>
const T maxByValue( const T lhs, const T rhs )
{
	return lhs < rhs ? rhs : lhs;
}

maxByValue( "apple", "banana" ); // ok
maxByValue( "apple", s ) // error
```
- **인자 추론 단계에서 배열->포인터 변환 (decay) 는 파라미터가 참조자가 아닐때만 발생**하기 때문이다.
```c++
// TB_09.cpp
#include <typeinfo>
#include <iostream>

template <typename T>
void ref( const T& x )
{
	std::cout << "void ref( const T& x ): " << typeid(x).name( ) << '\n' << std::endl;
}


template <typename T>
void nonref( const T x )
{
	std::cout << "void nonref( const T x ): " << typeid(x).name( ) << '\n' << std::endl;
}

int main( )
{
	ref( "hello" ); //  char[6]
	nonref( "hello" ); // char*
}
```
- typeid 연산자는 typeid로 건네진 표현식의 데이터형에 대한 std::type_info 데이터형의 lvalue를 반환하고 멤버 함수 name()을 통해서 데이터형을 사람이 읽을 수 있는 텍스트 형태로 반환한다.
- 문자열 리터럴에 대한 이런 동작은 일반적인 해결책은 없지만 다음과 같은 방식을 통해서 해결해 볼 수 있다.

1\. 참조자 대신에 참조자가 아닌 것을 사용. ( 불필요한 복사가 일어날 수 있다. )

2\. 참조자와 참조자가 아닌 파라미터 모두에 대해서 오버로딩한다. ( 하지만 이 경우는 호출이 모호할 수 있다. )
```c++
// TB_10.cpp
#include <string>

template <typename T>
const T& max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

template <typename T>
const T max( const T lhs, const T rhs )
{
	return lhs < rhs ? rhs : lhs;
}

int main( )
{
	max( "apple", "peach" ); // 모호한 호출
}
```
3\. 실제 데이터형으로 오버로딩한다 ( std::string 과 같은 형으로 )

4\. 배열형으로 오버로딩한다.
```c++
template <typename T, int N, int M>
const T* max( const T (&lhs)[N], const T (&rhs)[M] )
{
	return lhs < rhs ? rhs : lhs;
}

```
5\. 프로그래머가 항상 명시적으로 변환하게 한다.