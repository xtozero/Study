# 특수화와 오버로딩
## 개요
- 특정 템플릿 파라미터에서는 연산에 대한 일반적인 형태가 최적의 연산이 아닐 수 있다.
- c++은 일반적인 정의를 좀 더 특수화된 기능으로 바꿀 수 있는 많은 기능을 제공한다.

## 일반적인 코드가 별로 좋지 않을 때
```c++
// SAO_01.cpp
template <typename T>
class Array
{
private:
	T* data = nullptr;

public:
	//...

	void exchange_with( Array<T>* args )
	{
		T* tmp = data;
		data = args->data;
		args->data = tmp;
	}
};

template <typename T>
inline void exchange( T* lhs, T* rhs )
{
	T tmp( *a );
	*a = *b;
	*b = tmp;
}
```
- 위의 코드에서 exchange 함수는 대부분의 자료형에 잘 동작하지만, Array의 경우는 1번의 복사 생성자와 2번의 복사 연산자가 호출되고 깊은 복사가 일어나 상대적으로 많은 양의 메모리를 복사한다.
- 하지만 Array의 exchange_with 함수를 호출한다면 포인터를 교환하는 것만으로도 충분하다.

## 보이지 않는 커스터마이징
- 이전 코드에서 일반 exchange 함수 대신 exchange_with 함수를 쓰면 더 효율적이지만 다음과 같은 불편함을 감수해야 한다.

1\. Array 클래스의 사용자는 다른 인터페이스를 기억하고 가능한 적절한 것을 선택하게 주의를 기울여야 한다.

2\. 일반 알고리즘은 일반적으로 다양한 가능성을 분간할 수 없다.
```c++
// SAO_01.cpp
template <typename T>
void generic_algorithm( T* x, T* y )
{
	exchange( x, y );			// 올바른 알고리즘을 어떻게 선택할 것인가?
}
```
- 이런 고려사항들로 인해 C++ 템플릿은 함수 템플릿과 클래스 템플릿을 보이지 않게 커스터마이징하는 방법을 제공한다.
- **함수 템플릿의 경우에는 오버로딩을 통해 구현**될 수 있다.
```c++
// SAO_02.cpp
template <typename T>
inline void quick_exchange( T* a, T* b )                // 1
{
	T tmp( *a );
	*a = *b;
	*b = tmp;
}

template <typename T>
inline void quick_exchange( Array<T>* a, Array<T>* b )  // 2
{
	a->exchange_with( b );
}

int main( )
{
	int x = 42, y = -7;
	quick_exchange( &x, &y );

	Array<int> arr1, arr2;
	quick_exchange( &arr1, &arr2 );
}
```
- quick_exchange의 첫 번째 호출은 int*의 인자를 가지고 있고 인자 추론이 T를 int로 치환했을 때만 성공하므로 1번 함수가 불리게 된다.
- 두 번째 호출은 두 템플릿 모두 완전하게 일치하는데 C++에서는 2번 함수가 좀 더 특수화됐다고 간주하고 다른 조건이 모두 같으면 오버로딩 해석은 좀 더 특수화된 템플릿을 선호하므로 2번 함수가 불리게 된다.

## 의미 구조 투명성
- 앞서 알아본 오버로딩의 사용은 인스턴스화 과정에서 투명한 커스터마이징을 할 수 있어서 매우 유용하지만 이런 투명성은 구현의 자세한 부분에 매우 종속돼 있다.
- 일반 알고리즘과 Array\<T\>형에 커스터마이징된 두 방식은 가리켜진 값을 서로 바꾸지만, 연산의 영향은 매우 다르다.
```c++
// SAO_03.cpp
struct S
{
	int x = 0;
};

S s1, s2;

Array<int> a1( 5 );
Array<int> a2( 5 );

int* p = &a1[0];
int* q = &s1.x;

std::cout << *p << ", " << *q << std::endl;

a1[0] = s1.x = 1;
a2[0] = s2.x = 2;

quick_exchange( &a1, &a2 );
quick_exchange( &s1, &s2 );

std::cout << *p << ", " << *q << std::endl;
```
- 위 코드에서 quick_exchange() 가 호출된 후 첫 번째 Array에 대한 포인터 p가 두번째 배열에 대한 포인터로 바뀐다. 하지만 Array가 아닌 s1에 대한 포인터인 s1은 교환 연산이 이뤄진 이후에도 여전히 s1을 가리키고 있다.
- 이 둘의 차이는 엄청나므로 템플릿 구현의 사용자는 매우 혼란스러울 수 있다. quick_exchange()를 사용한 방법 외에 일반 exchange() 템플릿으로도 Array<T>의 유용한 최적화를 제공할 수 있다.
```c++
// SAO_03.cpp
template <typename T>
inline void exchange( Array<T>* a, Array<T>* b )
{
	T* p = &( *a )[0];
	T* q = &( *b )[0];

	for ( size_t k = a->size( ); k-- != 0; )
	{
		exchange( p++, q++ );
	}
}
```
- 이 버전은 임시 Array<T> 없이 실제 값을 교환한다.

## 함수 템플릿 오버로딩
- 함수 템플릿의 경우 두 함수 템플릿이 공존할 수 있고 이 함수들이 인스턴스화되었을 때 같은 파라미터를 가질 수도 있다.
```c++
// SAO_04.cpp
template <typename T>
int f( T )
{
	return 1;
}

template <typename T>
int f( T* )
{
	return 2;
}
```
- 첫 번째 함수 템플릿의 파라미터를 int*로 치환하면 두 번째 함수 템플릿을 int로 치환했을 때 얻을 수 있는 함수와 같은 파라미터를 갖는다.
- 이런 템플릿들도 공존할 수 있고 이들이 같은 파라미터와 반환형을 가져도 각각의 인스턴스로 공존할 수 있다.
```c++
// SAO_04.cpp
std::cout << f<int*>( (int*)0 ) << std::endl;
std::cout << f<int>( (int*)0 ) << std::endl;
````
- f\<int\*\>( (int\*)0 ) 는 인자 추론 없이 템플릿 파라미터를 바로 int\*로 치환한다.
- 이 경우 템플릿 f는 하나가 아니므로  f\<int\*\>( int\* ), f\<int\*\*\>( int\*\* ) 가 생성되고 두 함수는 오버로딩 집합에 속하게 된다. 여기서 f함수의 호출 인자는 int\*형이므로 f\<int\*\>( int\* )에만 일치하고 해당 함수가 호출된다.

## 서명
- 두 함수가 각기 다른 서명(signature)을 가진다면 한 프로그램 내에서 공존할 수 있다. 함수의 서명은 다음 정보를 통해 정의된다.

1\. 함수의 한정되지 않은 이름

2\. 해당 이름의 클래스 혹은 네임스페이스 영역과 이름이 내부 링크를 가진다면 이름이 선언된 번역 단위

3\. 함수의 const, volatile이나 const volatile 한정자( 이런 한정사를 가진 멤버 함수일 경우 )

4\. 함수 파라미터의 데이터형( 함수 템플릿에서 생성된 함수라면 템플릿 파라미터가 치환되기 전 )

5\. 이 함수가 함수 템플릿에서 생성됐다면 반환형

6\. 이 함수가 함수 템플릿에서 생성됐다면 템플릿 파라미터와 템플릿 인자

- 따라서 다음 템플릿과 인스턴스는 원칙상 한 프로그램 내에서 공존할 수 있다.
```c++
// SAO_05.cpp
template <typename T1, typename T2>
void f1( T1, T2 ) {}

template <typename T1, typename T2>
void f1( T2, T1 ) {}

template <typename T>
long f2( T ) {}

template <typename T>
char f2( T ) {}
```
- 하지만 인스턴스화하면 오버로딩의 모호함이 발생해 같은 영역에서 정의하면 이들을 항상 사용할 수 없다.
```c++
f1<char, char>( 'a', 'b' ); // f1( T1, T2 )과 f1( T2, T1 )의 인스턴스화 결과 f1( char, char )의 같은 함수가 생성되기 때문에 모호하다.
```
- 여기서 f1\<T1 = char, T2 = char\>(T1, T2) 함수는 f1\<T1 = char, T2 = char\>(T2, T1) 함수와 공존할 수 있지만 오버로딩 해석은 둘 중 어느 것을 더 선호할 수 없다.
- 두 템플릿이 다른 번역 단위에 있었다면 두 인스턴스는 같은 프로그램에 공존할 수 있다. 그리고 링크과정에서 인스턴스의 서명이 다르므로 중첩된 정의라고 오류를 발생시키지 않는다.
```c++
// SAO_06_TR1.cpp
template <typename T1, typename T2>
void f1( T1, T2 )
{
	std::cout << "void f1( T1, T2 ) " << std::endl;
}

void g( )
{
	f1<char, char>( 'a', 'b' );
}

// SAO_06_TR2.cpp
template <typename T1, typename T2>
void f1( T2, T1 ) 
{
	std::cout << "void f1( T2, T1 ) " << std::endl;
}

extern void g( ); // 번역 단위 1에서 정의

int main( )
{
	f1<char, char>( 'a', 'b' );
	g( );
}

```

## 오버로딩된 함수 템플릿의 부분 정렬
- 아래의 코드는 명시적인 템플릿 인자를 제공하여 함수 템플릿이 인스턴스화되고 오버로딩 해석이 일어난다.
```c++
// SAO_04.cpp
template <typename T>
int f( T )
{
	return 1;
}

template <typename T>
int f( T* )
{
	return 2;
}

std::cout << f<int*>( (int*)0 ) << std::endl;
std::cout << f<int>( (int*)0 ) << std::endl;
```
- 하지만 명시적으로 템플릿 인자를 전달하지 않아도 함수는 선택되어야 한다. 이 경우 템플릿 인자 추론이 일어난다.
```c++
// SAO_07.cpp
template <typename T>
int f( T )
{
	return 1;
}

template <typename T>
int f( T* )
{
	return 2;
}

std::cout << f( 0 ) << std::endl;
std::cout << f( (int*)0 ) << std::endl;
```
- 첫 번째 호출 f( 0 )은 인자의 데이터형이 int형이므로 첫 번째 템플릿의 T를 int로 치환하여 호출된다.
> 두 번째 템플릿의 경우 파라미터형이 언제나 포인터형이므로 첫 번째 템플릿만 알맞은 인스턴스를 생성할 수 있다.

- 두 번째 호출 f( (int\*)0 )의 인자추론은 두 템플릿에서 모두 성공하고 f\<int\*\>( int\* ), f\<int\>( int )가 인스턴스화될 수 있다. 둘 다 int\*로 호출될 수 있으므로 이 호출은 모호할 수 있으나 부가적인 오버로딩 해석 기준이 사용되어 **좀 더 특수화된 템플릿에서 생성된 함수가 선택된다.** 여기서는 두 번째 템플릿이 좀 더 특수화된 템플릿으로 고려된다.

## 공식 정렬 법칙
- 이전 코드의 두 번째 템플릿이 첫 번째보다 더 특수한 이유는 첫 번째 템플릿은 어떤 인자형이라도 수용할 수 있지만 두 번째 템플릿은 포인터형만 허용하기 때문이라는 것을 알 수 있다.
- 어떤 함수의 템플릿이 다른 것보다 더 특수화됐는지를 결정할 수 없을 때도 있는 이때는 어떤 것도 선택할 수 없으므로 프로그램은 모호함 오류를 낼 것이다.
- 특수화 정도를 판단하기 위해서는 우선 모든 템플릿 파라미터를 다음과 같이 치환해야 한다.

1\. 각 템플릿형 파라미터를 고유한 생성된 형으로 바꿈

2\. 각 템플릿 템플릿 파라미터를 고유한 생성된 클래스 템플릿으로 바꿈

3\. 각 데이터형이 아닌 템플릿 파라미터를 적절한 데이터형의 고유한 생성된 값으로 바꿈

- 템플릿 인자 추론의 결과가 다른 템플릿의 추론 결과보다 정확하게 일치하면 해당 템플릿을 좀 더 특수화된 것으로 취급된다.
```c++
// SAO_07.cpp
template <typename T>
void t( T*, const T* = 0, ... ) {}

template <typename T>
void t( const T*, T*, T* = 0 ) {}

void example( int* p )
{
	t( p, p );
}
```
- 위의 코드에서 인자 데이터형의 조합 목록은 (A1\*, const A1\*)과 (const A2\*, A2\*) 이다. 첫 번째 함수의 경우 두 번째 인자가 const로 인해 완벽하게 일치하지 않고 두 번째 함수는 첫 번째 인자가 const로 인해서 완벽하게 일치하지 않는다. 따라서 어떤 것이 더 특수화되었는지 우열을 가릴 수 없으므로 모호한 호출이 된다.

## 템플릿과 템플릿이 아닌 것
- 함수 템플릿은 템플릿이 아닌 함수로 오버로딩 될 수 있다. 다른 것이 모두 같다면 실제 함수 호출 시 **템플릿이 아닌 함수가 선호된다.**
```c++
// SAO_08.cpp
#include <string>
#include <iostream>

template <typename T>
std::string f( T )
{
	return "Templates";
}

std::string f( int& )
{
	return "Not Templates";
}

int main( )
{
	int x = 7;
	std::cout << f( x ) << std::endl; // 템플릿이 아닌 함수가 선호된다. "Not Templates" 출력
}
```

## 명시적 특수화
- 함수 템플릿의 경우 오버로딩을 부분 정렬을 통해 최적의 함수 템플릿을 선택하는 기능과 함께 사용하여 특수화된 구현을 제공할 수 있다.
- 클래스 템플릿에서는 오버로딩이 불가능한데 명시적 특수화(explicit specialization)를 통해서 템플릿을 커스터마이징 할 수 있다.
- **명시적 특수화는 전체 특수화라고 불리는 언어 특성**을 가리키는 말이다. 전체 특수화를 통해 **템플릿의 어떤 파라미터도 남기지 않고 모든 파라미터를 치환한 구현을 제공**할 수 있다.
- 전체 특수화 외에 부분 특수화도 존재하는데 일부 파라미터를 남겨둬 템플릿을 구현하는 방식을 말한다.
- 전체 특수화든 부분 특수화든 **완전히 새로운 템플릿이나 템플릿 인스턴스를 도입하지 않는다.** 대신 이들은 이미 일반 템플릿에서 묵시적으로 선언된 인스턴스를 위한 **대한 정의를 제공**한다. 이것이 템플릿 오버로딩과의 가장 큰 차이점이다.

## 전체 클래스 템플릿 특수화
- 전체 특수화는 template, \<, \> 의 연속으로 만들어진다. 게다가 클래스 이름 선언자 뒤에 특수화가 선언될 템플릿 인자가 따라온다.
```c++
// SAO_09.cpp
template <typename T>
class S
{
public:
	void info( )
	{
		std::cout << "generic (S<T>::info())" << std::endl;
	}
};

template <>
class S<void>
{
public:
	void msg( )
	{
		std::cout << "fully specialized (S<T>::msg())" << std::endl;
	}
};
```
- 전체 특수화의 구현은 일반 정의와 어떤 방식으로든 관계가 있을 필요는 없다.
> 다른 이름을 가진 멤버 함수를 가질 수도 있다.

- 명시된 템플릿 인자 목록은 템플릿 파라미터의 목록에 대응돼야 한다. 템플릿형 파라미터에 데이터형이 아닌 인자를 명시할 수 없다. 다만 기본 템플릿 인자를 가지는 파라미터를 위한 인자는 옵션이다.
```c++
// SAO_09.cpp
template <typename T>
class Types
{
public:
	typedef int I;
};

template <typename T, typename U = typename Types<T>::I>
class FS;

template <>
class FS<void> 
{
public:
	void f( );
};

template <>
class FS<char, char>;

template <>
class S<char, 0>;		// error

FS<int>* pi;		// ok
FS<int>	e1;			// error : 정의 없음
FS<void>* pv;		// ok
FS<void, int> sv;	// ok
FS<void, char> e2;	// error : 정의 없음
FS<char, char> e3;	// error : 정의 없음
```
- 위의 코드에서 보이듯 전체 특수화의 선언이 꼭 정의여야 할 필요는 없다. 하지만 **전체 특수화가 선언되면 주어진 템플릿 인자들 집합에 대해서 일반 정의가 사용되지 않으므로** 정의가 필요한데도 없다면 오류가 발생한다.
- 전체 특수화 선언은 일반 클래스 선언과 완전히 같다. 차이점이라면 문법이 다르며 선언이 이전 템플릿 선언과 정확히 일치해야 한다는 점이다.
- 템플릿 선언이 아니므로 일반적인 클래스 밖 멤버 정의 문법을 사용해 전체 클래스 템플릿 특수화의 멤버를 정의할 수 있다.
> 즉 template<> 접두사를 붙이지 않는다.

```c++
// SAO_09.cpp
template<>

class S<char**>
{
public:
	void print( ) const;
};

void S<char**>::print( ) const
{
	std::cout << "Pointer to pointer to char" << std::endl;
}
```
- 이해를 높일 수 있는 좀 더 복잡한 예제를 살펴보자
```c++
// SAO_10.cpp
template <typename T>
class Outside
{
public:
	template <typename U>
	class Inside
	{
	};
};

template <>
class Outside<void>
{
	template <typename U>
	class Inside
	{
	private:
		static int count;
	};
};

// template<>이 올 수 없다.
template <typename U>
int Outside<void>::Inside<U>::count = 1;
```
- 전체 특수화는 특정 일반 템플릿의 인스턴스를 치환하며 한 프로그램에서 명시적인 것과 생성된 버전의 템플릿이 공존하는 것은 유효하지 않다. 같은 파일에서 둘 다 사용하려고 하면 컴파일 중에 오류가 발생한다.
```c++
// SAO_10.cpp
template <typename T>
class Invalid
{

};

Invalid<double> x1;

template<>
class Invalid<double>; // error : 이미 인스턴스화 됐음
```
- 다른 번역 단위에서 둘 다 사용하는 경우에는 이 문제를 알아차리기 힘들다.
```c++
// SAO_11_TR1.cpp
template <typename T>
class Danger
{
public:
	enum { max = 10 };
};

char buffer[Danger<void>::max]; // 여기서는 max가 10

extern void clear( char* const );

int main( )
{
	clear( buffer ); // 다른 번역 단위의 함수 내에서 max가 100이다.
}

// SAO_11_TR2.cpp
template <typename T>
class Danger;

template <>
class Danger<void>
{
public:
	enum { max = 100 };
};

void clear( char* const buf )
{
	for ( int i = 0; i < Danger<void>::max; ++i )
	{
		buf[i] = '\0';
	}
}
```
- 헤더 파일에서 템플릿의 선언 다음에 특수화 선언이 오지 않으면 위와 같이 찾기 어려운 오류를 내포할 수 있다. 일반적으로 그러한 목적으로 설계됐다고 표시되지 않는 한 외부 소스에서 온 특수화 템플릿은 피하는 편이 좋다.

## 전체 함수 템플릿 특수화
- 전체 함수 템플릿 특수화는 전체 클래스 템플릿 특수화와 거의 비슷하나 오버로딩과 인자 추론이 더 추가됐다.
- 특수화될 템플릿이 인자 추론과 부분 정렬을 통해 결정될 수 있을 때 전체 특수화 선언은 명시적인 템플릿 인자를 생략할 수 있다.
```c++
// SAO_12.cpp
template <typename T>		// 1
int f( T )
{
	return 1;
}

template <typename T>		// 2
int f( T* )
{
	return 2;
}

template<> int f( int )		// 1의 특수화
{
	return 3;
}

template<> int f( int* )	// 2의 특수화
{
	return 4;
}
```
- 전체 함수 템플릿 특수화는 **기본 인자 값이 포함될 수 없다.** 하지만 템플릿에서 기본 인자가 명시됐다면 명시적 특수화가 이뤄진 후에도 사용할 수 있다.
```c++
// SAO_12.cpp
template <typename T>
int f( T, T x = 42 )
{
	return x;
}

template <>
int f( int, int = 35 ) // error : 전체 함수 템플릿 특수화에서 기본 인자를 사용할 수 없다.
{
	return 0;
}

template <typename T>
int g( T, T x = 42 )
{
	return x;
}

template <>
int g( int, int y )
{
	return y / 2;
}

int main( )
{
	std::cout << g( 0 ) << std::endl; // 21
}
```
- 전체 특수화는 일반 선언과 유사하다. 다만 전체 특수화의 선언은 템플릿에서 생성된 함수를 사용하는 시도를 막기 위해 항상 템플릿 뒤에 따라 나와야 한다.
```c++
// SAO_13.hpp
#pragma once

template <typename T>
int g( T, T x = 42 )
{
	return x;
}

template<> int g( int, int y );

// SAO_13.cpp
#include "SAO_13.hpp"

template <> 
int g( int, int y )
{
	return y / 2;
}
```
- 혹은 특수화를 인라인으로 만들고 그 정의를 헤더 파일에 위치시킬 수 있다.

## 전체 멤버 특수화
- 멤버 템플릿뿐만 아니라 일반적인 정적 데이터 멤버와 멤버 함수도 전체를 특수화할 수 있다. 멤버 템플릿이 특수화되면 template\<\>를 추가해 이것이 특수화됐음을 알려야 한다.
```c++
// SAO_14.cpp
#include <iostream>

template <typename T>
class Outer
{
public:
	template <typename U>
	class Inner
	{
	private:
		static int count;
	};

	static int code;
	void print( ) const
	{
		std::cout << "generic" << std::endl;
	}
};

template <typename T>
int Outer<T>::code = 6;

template <typename T>
template <typename U>
int Outer<T>::Inner<U>::count = 7;

template <>
class Outer<bool>
{
	template<typename U>
	class Inner
	{
	private:
		static int count;
	};
	void print( ) const {}
};
```
- 일반적인 Outer 템플릿의 일반 멤버 code와 print()를 둘러싼 클래스 템플릿은 하나이기 때문에 특정 템플릿 인자로 이들을 특수화할 때에는 template\<\>을 하나만 쓰면 된다.
```c++
// SAO_14.cpp
template <>
int Outer<void>::code = 12;

template <>
void Outer<void>::print() const
{
	std::cout << "Outer<void>" << std::endl;
}
```
- 이런 정의는 클래스 Outer\<void\>를 위한 일반적인 멤버 대신에 사용되지만 다른 멤버는 기존의 Outer\<T\>에서 생성된다. 또한 **이런 선언을 한 이후 Outer\<void\>의 명시적 특수화를 제공할 수 없다.**
- 다중 선언을 방지하기 위해서 정의를 명시하지 않고 클래스 템플릿의 일반 멤버의 특수화를 선언할 방법이 필요하다.
- **일반 클래스의 멤버 함수와 정적 데이터 멤버에 대해 클래스 밖에서 선언하는 것은 C++에서 허용되지 않지만 클래스트 템플릿 멤버를 특수화할 때는 예외**이다.
```c++
// SAO_14.cpp
template <>
int Outer<void>::code;

template <>
void Outer<void>::print( ) const;
```
- 위 코드의 int Outer\<void\>::code 는 기본 생성자로 초깃값을 정의하는 문법과 똑같은데 이런 선언은 항상 정의되지 않은 선언으로만 해석된다.
- 그러므로 **기본 생성자를 사용해서만 초기화할 수 있는 데이터형을 가진 정적 데이터 멤버의 전체 특수화를 위해 정의를 제공할 방법은 없다.**
```c++
// SAO_14.cpp
class DefaultInitOnly
{
public:
	DefaultInitOnly() {}

	int value;
private:
	DefaultInitOnly( const DefaultInitOnly& ); // 복사 불가
};

template <typename T>
class Statics
{
public:
	static T sm;
};

// 다음은 선언이다.
// 정의를 제공할 방법이 없다.
template<>
DefaultInitOnly Statics<DefaultInitOnly>::sm;
```
- 멤버 템플릿 Outer\<T\>::Inner는 멤버 템플릿을 특수화하고자 하는 Outer\<T\>에 대한 특정 인스턴스의 다른 멤버에게 영향을 미치지 않으면서도 주어진 템플릿 인자에 특수화될 수 있다.
```c++
// SAO_14.cpp
template <>
template <typename X>
class Outer<wchar_t>::Inner
{
public:
	static long count;	// 멤버 데이터형이 바뀌었음
};

template <>
template <typename X>
long Outer<wchar_t>::Inner<X>::count;
```
- Outer\<T\>::Inner는 전체가 특수화될 수도 있으나 Outer\<T\>의 주어진 인스턴스에 대해서만 특수화될 수 있다. 이제는 두 개의 template\<\>가 필요하다.
```c++
// SAO_14.cpp
template<>
template<>
class Outer<char>::Inner<wchar_t>
{
public:
	enum { count = 1 };
};

template <typename X>
template <>
class Outer<X>::Inner<void>; // error : tempalte<>는 템플릿 파라미터의 목록 뒤에 위치할 수 없음
```
- 위의 코드를 Outer\<bool\>의 멤버 템플릿 특수화와 대조해보면 이후의 것은 벌써 전체가 특수화됐고 둘러싼 템플릿이 없으므로 template\<\> 접두사는 하나면 충분하다.
```c++
// SAO_14.cpp
template <>
class Outer<bool>::Inner<wchar_t>
{
public:
	enum { count = 2 };
};
```

## 부분 클래스 특수화
- 전체 템플릿 특수화가 유용하긴 하지만 특정 템플릿 인자 집합에 대해서만 클래스 템플릿을 특수화하는 것보다는 템플릿 인자 군에 대해 특수화하는 편이 더 자연스러울 때가 있다.
- 아래와 같이 연결 리스트를 구현한다고 가정해보자
```c++
// SAO_15.cpp
template <typename T>
class List
{
public:
	void append( const T& );
	inline size_t length( ) const;
};
```
- 큰 프로젝트에서는 이 템플릿을 여러 가지 데이터형을 멤버로 가지게 인스턴스화시킬 수 있는데 그럴 경우 목적 코드가 엄청나게 증가할 것이다. 하지만 낮은 수준에서 List\<int*\>, List<\void*\>의 코드는 같을 것이므로 포인터의 모든 List가 하나의 구현을 공유하면 좋을 것이다.
```c++
// SAO_15.cpp
template <typename T>
class List<T*>
{
private:
	List<void*> impl;

public:
	void append( T* p )
	{
		impl.append( p );
	}

	size_t length( ) const
	{
		return impl.length( );
	}
};
```
- 이 코드에는 List\<void*\>가 같은 List\<void*\>형의 멤버를 재귀적으로 갖는다는 문제가 있는데 이런 순환을 전체 특수화로 끊을 수 있다.
```c++
// SAO_15.cpp
template <>
class List<void*>
{
	void append( void* p );
	inline size_t length( ) const;
};
```
- 전체 특수화와 부분 특수화 모두에 일치한다면 전체 특수화가 선호되므로 위 코드는 잘 동작한다.
- 부분 특수화 선언의 파라미터와 인자 목록에는 몇 가지 제약이 있는데 다음과 같다.

1\. 부분 특수화 인자는 기본 템플릿의 대응되는 파라미터와 같은 종류여야 한다.
> 데이터형, 데이터형이 아닌, 혹은 템플릿 템플릿 파라미터

2\. 부분 특수화의 파라미터 목록은 기본 인자를 가질 수 없다. 대신 원래 클래스 템플릿의 기본 인자는 사용할 수 있다.

3\. 부분 특수화의 데이터형이 아닌 인자는 비 종속적인 값이거나 평범해야 한다.
> 2 * N 처럼 복잡한 종속 표현식이 될 수 없다.

4\. 부분 특수화의 템플릿 인자 목록은 항상 기본 템플릿의 파라미터 목록과 같지 않아야 한다.
> 새 이름을 붙이는 것은 무시된다.

```c++
// SAO_16.cpp
template <typename T, int I = 3>
class S;							// 기본 템플릿

template <typename T>
class S<int, T>;					// error : 파라미터 종류 불일치

template <typename T = int>
class S<T, 10>;						// error : 기본인자 사용 불가

template <int I>
class S<int, I * 2>;				// error : 데이터형이 아닌 표현식을 허용하지 않음

template <typename U, int X>
class S<U, X>						// error : 기본 템플릿과 차이 없음
````
- 모든 부분 특수화는 기본 템플릿과 연관돼 있다. 일단 기본 템플릿이 먼저 룩업되며 그 후에 연결된 특수화의 인자를 비교해 어떤 템플릿 특수화를 선택할지 결정한다.
- 마지막으로 클래스 템플릿의 특수화가 기본 템플릿에 비해 더 많거나 적은 파라미터를 가질 수 있다는 점을 살펴보자
```c++
// SAO_17.cpp
// void* 형 멤버 접근 포인터에 대한 특수화
template <typename C>
class List<void* C::*>
{
public:
	typedef void* C::*ElementType;

	void append( ElementType pm );
	inline size_t length( ) const;
};

// 멤버 접근 포인터 포인터형을 위한 부분 특수화
// void* 형 멤버 접근 포인터는 이미 처리됐으므로 여기서는 제외된다.
// 이 부분 특수화는 두 템플릿 파라미터를 가지는데 기본 템플릿은 하나의 파라미터를 가진다.
template <typename T, typename C>
class List<T* C::*>
{
private:
	List<void* C::*> impl;

public:
	typedef T* C::*ElementType;

	void append( ElementType pm )
	{
		impl.append( ( void* C::* )pm );
	}

	inline size_t length( ) const
	{
		return impl.length( );
	}
};
```