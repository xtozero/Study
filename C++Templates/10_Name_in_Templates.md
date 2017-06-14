# 템플릿에서의 이름
## 개요
- 이름이란 프로그래머가 이전에 만든 실체를 가리키기 위한 수단이다.
- C++ 컴파일러가 이름을 만나면 컴파일러는 이 이름이 지칭하는 실체를 식별하기 위해 *찾아보아야( look it up )* 한다. C++은 이런 이름 찾기를 구현하기 어려운 언어이다.
> x*y라는 표현이 있다면 x와 y가 변수명이라면 이 문장은 곱셈이지만 x가 자료형이라면 x에 대한 포인터 변수 y를 선언하는 것이다.

- C++(과 C)는 문맥 민감 언어( context-sensitive language )라는 것을 알 수 있다. 더 넓은 문맥을 이해하지 않으면 코드를 이해할 수 없다.
- 템플릿은 다음과 같은 더 넓은 문맥에서 처리되어야 한다.

1\. 템플릿이 나타난 곳에서의 문맥

2\. 템플릿 인스턴스화된 곳의 문맥

3\. 템플릿이 인스턴스화된 곳에서 템플릿 인자들과 연관된 문맥

- 따라서 **C++에서 이름은 매우 조심스럽게 다뤄져야 한다.**

## 이름 분류
- C++은 이름을 매우 다양한 방식으로 분류한다. 하지만 다음 두 가지 이름 개념에 익숙해진다면 대부분의 C++ 템플릿과 관련된 문제는 쉽게 이해할 수 있다.

1\. 한정된 이름 ( qualified name ) : 해당 이름이 속한 영역을 영역 해석 연산자(::)나 멤버 접근 연산자('.' 혹은 -\>)를 사용하여 명시적으로 나타낸 경우의 이름이다.
> 예를 들어 this-\>count는 한정된 이름이지만 count는 한정된 이름이 아니다.

2\. 종속 이름 ( dependent name ) : 이름이 템플릿 파라미터에 어떤 방식으로든 종속된 경우를 말한다.
> 예를 들어 std::vector\<T\>::iterator는 T가 템플릿 파라미터일 경우 종속 이름이지만 typedef 라면 종속되지 않은 이름이다.

- 이 밖의 이름 분류를 살펴보면 다음과 같다.

1\. **식별자 ( identifier )** : 영문자와 '_'와 숫자가 연속적으로 나와 이루어진 이름. 숫자로 시작할 수 없으며 일부 식별자는 구현을 위해 예약되어 있다.
```c++
// NIT_02.cpp
class _Idenfitier1 {};

class 1Idenfitier {};

// 1. identifier
_Idenfitier1 valid;	// identifier
Idenfitier invalid;	// error
int reserved		// reserved
```

2\. **연산자-함수-식별자 ( operator-function-id )** : 키워드인 operator 다음에 operator를 가리키는 기호가 나오는 경우
> 예를 들어 operator new 나 operator [] 가 이에 속한다.
```c++
// NIT_02.cpp
class BigInt
{
public:
	// 2. operator-function-id
	BigInt& operator=( const BigInt& );

	// ...
};
```

3\. **변환-함수-식별자 ( conversion-function-id )** : 사용자 정의 묵시적 변환 연산자
> operator int&를 예로 들 수 있다.
```c++
// NIT_02.cpp

class BigInt
{
public:
	// ...

	// 3. conversion-function-id
	operator int( );
};
```

4\. **템플릿-식별자 ( template-id )** : 꺾쇠로 둘러싸인 템플릿 인자가 뒤따라 나오는 템플릿 이름
> List\<T, int, 0\>을 예로 들 수 있다.
```c++
// NIT_02.cpp

// 4. template-id
Stack<int> intStack;
```

5\. **한정되지 않은 식별자 ( unqualified-id )** : 일반화된 식별자

6\. **한정된 식별자 ( qualified-id )** : 클래스 이름이나 네임스페이스 혹은 전역 해석 연산자로 한정된 식별자
> ::X, S::x, Array\<T\>::y와 N::A\<T\>::z 등이 한정된 식별자다.
```c++
// NIT_02.cpp

Stack<float>::Type floatStackType;
```

7\. **한정된 이름( qualified name )** : 표준에는 정의되지 않았지만 한정된 룩업을 거치는 이름을 가리키기 위해서 사용 명시적인 멤버 접근 연산자 ('.' 이나 -\>) 뒤에 사용되는 한정된 식별자 한정되지 않는 식별자가 이에 속한다.
> S::x, this-\>f, p-\>A::m
```c++
// NIT_02.cpp

intStack.element;
```

8\. **한정되지 않은 이름( unqualified name )** : 한정된 이름이 아닌 식별자이다. 표준 용어는 아니다.

9\. **이름( name )** : 한정되거나 한정되지 않은 이름

10\. **종속 이름 ( dependent name )** : 템플릿 파라미터에 종속된 이름. 한정되거나 한정되지 않은 이름이 템플릿 파라미터를 명시적으로 포함한다면 그 이름은 종속적이다. 또한 멤버 접근 연산자로 한정된 이름에서 접근 연산자의 왼쪽 표현식의 데이터형이 템플릿 파라미터에 종속돼 있다면 역시 종속적이다. ~~마지막으로 f( x, y, z )라는 형태의 호출에서 인자 표현식중 어떤 것이라도 템플릿 파라미터에 종속돼 있다면 f라는 식별자는 종속 이름이다.~~
```c++
// NIT_02.cpp

// 10. dependent name
Stack<float> floatStack;
```

11\. **종속되지 않은 이름 ( nondependent name )** : 종속 이름이 아닌 이름

## 이름 룩업
- **한정된 이름을 찾아볼 때**는 한정된 생성 때문에 묵시적으로 알려진 영역만 찾는다. 영역이 클래스라면 기본 클래스도 찾아야 할 수 있다. 하지만 한정된 이름을 찾는 중에는 *해당 영역을 둘러싸는 외부 영역에 대해 고려하지 않는다.*
```c++
// NIT_01.cpp
int x;

class B
{
public:
	int i;
};

class D : public B {};

void f( D* pd )
{
	pd->i = 3;		// B::i 찾음
	D::x = 2;		// error 둘러싼 영역에서 ::x를 찾지 못함
}
```
- 이와 대조적으로 한정되지 않는 이름은 현재 영역을 둘러싼 더 큰 영역들을 차례로 룩업한다. 이것을 *일반 룩업( ordinary lookup )* 이라고 한다.
```c++
// NIT_01.cpp
int count = -1;			    			// 1

int lookup_example( int count )			// 2
{
	if ( count < 0 )
	{
		std::cout << count << std::endl;	// -2
		std::cout << ::count << std::endl;	// -1

		int count = 0;					// 3

		std::cout << count << std::endl;	// 0
		std::cout << ::count << std::endl;	// -1
		lookup_example( count );		// 한정되지 않은 count는 3을 가리킴
	}

	std::cout << count << std::endl;		// -2
	std::cout << ::count << std::endl;		// -1
	return count + ::count;				// 첫 번째 한정되지 않은 카운트는 2를 가리킴
}

int main( )
{
	lookup_example( -2 );
}
```
- 한정되지 않은 이름을 찾는 룩업에는 또한 인자 종속 룩업( ADL : argument-dependent lookup )이 있다. 인자 종속 룩업은 아래와 같은 상황을 해결하기 위한 특별한 규칙이다.
> 또는 제안한 사람인 앤드류 코니그( Andrew Koenig )의 이름을 따 코니그 룩업이라고 부른다.

```c++
template <typename T>
inline const T& max( const T& a, const T& b )
{
	return a < b ? b : a;
}

// 위의 템플릿을 다른 네임스페이스에 정의한 데이터형에 적용해야 한다고 하면...
namespace BigMath
{
	class BigNumber
	{

	};

	bool operator< ( const BigNumber&, const BigNumber& ) { return true; }
}

void g( const BigMath::BigNumber& a, const BigMath::BigNumber& b )
{
	BigMath::BigNumber x = max( a, b );
}
```
- 문제는 max()는 BigMath 네임스페이스를 모르는데 일반 룩업으로는 BigNumber형의 '\<' 연산자를 찾을 수 없다. 특별한 법칙이 없다면 C++ 네임스페이스의 문맥에서 템플릿의 사용성이 크게 줄어든다. ADL은 이와 같은 상황에서 필요한 특별한 법칙이다.

## 인자 종속 룩업
- ADL은 **한정되지 않은 이름들에만 적용**되는 법칙으로 멤버가 아닌 함수를 찾는 것으로 생각할 수 있다. 일반 룩업으로 멤버 함수의 이름이 데이터형의 이름을 찾았다면 ADL은 일어나지 않는다.
- ~~또한 ADL은 호출해야 할 함수의 이름이 괄호로 둘러싸여 있을 경우에도 사용되지 않는다.~~
- ADL은 호출 인자의 **데이터 형과 연관된 네임스페이스와 클래스** 안에서 이름을 계속해서 찾는다. 직관적으로 생각하면 주어진 데이터형에 직접 연관된 모든 네임스페이스와 클래스를 대상으로 한다고 생각할 수 있다.
- 특정 데이터형에 연관된 네임스페이스와 클래스 집합에 대한 정의는 다음과 같은 법칙에 따라 정해진다.

1\. **내장( builit-in ) 데이터형** : 빈 집합이다.

2\. **포인터와 배열형** : 포인터나 배열이 가리키는 데이터형에 연관된 네임스페이스와 클래스의 집합과 같다.

3\. **열거형** : 열거형이 선언된 네임스페이스이다.

4\. **클래스 멤버** : 자신을 둘러싼 클래스가 연관된 클래스다.

5\. **클래스형(공용체 포함)** : 자기 자신과 자신을 둘러싼 클래스와 직접 혹은 간접적인 기본 클래스, 연관된 클래스가 선언된 네임스페이스가 해당한다. 클래스가 클래스 템플릿 인스턴스라면 *템플릿형 인자의 데이터형*과 *템플릿 템플릿 인자가 선언된 클래스와 네임스페이스*도 포함된다.

6\. **함수** : 모든 파라미터형과 반환형에 관련된 네임스페이스와 클래스를 모두 포함한다.

7\. **클래스 멤버에 대한 포인터형** : 클래스에 연관된 것뿐만이 아니라 멤버의 데이터형에 연관된 모든 것들도 포함된다.
> 멤버 함수에 대한 포인터형이라면 파라미터와 반환형에 관련된 것들도 고려된다.

- ADL은 관련된 모든 네임스페이스, 클래스를 순서대로 방문하여 그 안에서 찾으려는 이름이 해당 네임스페이스에 속한 것처럼 룩업한다. **다만 사용 지시자( using-directive )는 무시한다**
```c++
// NIT_03.cpp
#include <iostream>

namespace X
{
	template<typename T> void f( T );
}

namespace N
{
	using namespace X;
	enum E { el };
	void f( E )
	{
		std::cout << "N::f(N::E) called" << std::endl;
	}
}

void f( int )
{
	std::cout << "::f(int) called" << std::endl;
}

int main( )
{
	::f( N::el );  // 한정된 함수 이름 : ADL 아님
	f( N::el ); // 일반적인 룩업은 ::f()를 찾고 ADL은 N::f()를 찾음
}
```
- 위의 예제에서 ADL이 수행될 때 네임스페이스 N에서 사용 지시자( using namespace X )가 무시된것을 확인할 수 있다. 따라서 X::f()는 main에서 호출되는 함수들의 후보조차 될 수 없다.

## 프렌드 이름 주입
- 프렌드 함수 선언이 해당 함수에 대한 첫 번째 선언일 수 있다. 그렇다면 프렌드 선언을 포함하는 클래스를 둘러싸고 있는 가장 가까운 네임스페이스에 해당 함수가 선언됐을 것으로 가정된다.
- 프렌드 함수가 이처럼 주입됐을 경우 그 영역에서 선언이 가시화돼야 하는가는 템플릿에서 중요하다.
```c++
// NIT_04.cpp
template <typename T>
class C
{
	friend void f( ) {}
	friend void f( const C<T>& ) {}
};

void g( C<int>* p )
{
	f( );		// error
	f( *p );	// ok
}

int main( )
{
	C<int>* p = nullptr;
	g( p );
}
```
- 둘러싼 네임스페이스에서 프렌드 선언이 가시화되어 있다면 클래스 템플릿을 인스턴스화함으로써 일반 함수의 선언이 가시화 될 수 있다.
- C++ 표준은 **프렌드 선언이 둘러쌓인 영역에서 일반적으로 가시화되지 않고 ADL에 의해 연관된 클래스에 속한다면 이 프렌드 함수를 찾을 수 있다고 명시**했다.
- 위의 예제를 다시 살펴보면 f( )는 인자가 없기 때문에 연관된 클래스나 네임스페이스가 없다. 따라서 유효하지 않다. 하지만 f( \*p )는 호출에 C\<int\>\*라는 클래스(\*p의 데이터형)과 전역 네임스페이스가 연관돼 있다. (\*p의 데이터형이 선언된 네임스페이스) C\<int\>가 사실상 이 함수의 호출 이전에 완전히 인스턴스화됐으므로 두 번째 프렌드 함수 선언은 찾을 수 있다.

## 주입된 클래스 이름
- 클래스의 이름은 해당 클래스 자체의 영역 내에 주입되며 그 영역 내에서는 한정되지 않은 이름으로 접근할 수 있다.
```c++
// NIT_05.cpp
#include <iostream>

int C;

class C
{
private:
	int i[2];
public:
	static int f( )
	{
		return sizeof( C );
	}
};

int f( )
{
	return sizeof( C );
}

int main( )
{
	std::cout << "C::f() = " << C::f( ) << ", "
		<< " ::f() = " << ::f( ) << std::endl;
}
```
- 위의 예제를 보면 멤버 함수 C::f()에서 C라는 클래스의 데이터형의 크기를 반환하는데 반해 ::f()는 변수 C의 크기를 반환한다.
- 클래스 템플릿 역시 주입된 클래스 이름을 가진다. 클래스 템플릿의 주입된 이름은 뒤에 템플릿 인자가 따라 나올 수 있지만 템플릿 인자가 따라 나오지 않는다면 자신의 파라미터를 인자로 가지는 클래스를 나타낸다.
```c++
// NIT_06.cpp
template <template <typename> class TT> class X
{
};

template <typename T> class C
{
	C* a;				// OK : C<T>* a 와 같다.
	C<void> b;			// ok
	//X<C> c;			// 템플릿 인자 목록이 없는 C는 템플릿을 나타내지 않음
	//X<::C> d;			// error <: 는 [로 해석되는 겹자(digraph)이다. 겹자는 #, [ 등이 없는 키보드에서 쉽게 C++코드를 작성할 수 있도록 추가됐다.
	X< ::C> e;
};
```
- 한정되지 않은 이름이 주입된 이름을 참조하는 방식과 **템플릿 인자 목록이 뛰따라오지 않는다면 한정되지 않은 이름을 템플릿의 이름으로 고려하지 않는다**는 것에 주의해야 한다.
- 이를 보완하려면 파일 영역 한정자인 ::을 사용해 템플릿의 이름을 찾을 수 있도록 해야 한다.

## 템플릿 파싱
- 대부분 프로그래밍 언어를 위한 컴파일러의 기본 동작은 토큰화(스캐닝(scanning) 혹은 렉싱(lexing))와 파싱(parsing)이다.
- 토큰화 과정은 소스코드를 문자로 읽어 들여 이를 통해 토큰을 생성한다.
> int* p = 0; 과 같은 문자를 본다면 토큰 분리기( tokenizer )는 키워드 int, 기호/연산자 *, 식별자 p, 기호/연산자 =, 상수형 리터럴 0, 기호/연산자 ;을 나타내는 토큰을 생성한다.

- 파서는 재귀적으로 토큰을 제거해 토큰들 속에서 패턴을 찾거나 상위 클래스에서 이미 알려진 패턴을 찾는다.
> 예를 들어 0이라는 토큰이 유효한 표현식이고 * 다음에는 식별자 p가 오는 것도 유효한 선언이다. 파서는 이런 패턴을 찾는다.

## 템플릿을 쓰지 않을 때의 문맥 민감성
- 파싱은 토큰화보다 어렵다. 하지만 오랫동안 연구된 이론을 사용해서 많은 언어를 그리 어렵지 않게 파싱할 수 있다.
- 하지만 이 이론은 문맥 자유 언어에서 잘 동작하는데 C++은 문맥 민감 언어이다. 그래서 C++은 **기호 테이블을 토큰 분리기와 파서에 연결시켜 이런 문제를 해결**한다.
- 파싱된 것이 선언이면 *선언된 것은 기호 테이블에 삽입*된다. 토큰 분리기가 식별자를 찾는다면 그 식별자를 기호 테이블에서 찾아보고 데이터형을 찾았다면 그 결과 토큰에 대해 주석을 단다.
> 예를 들어 C++ 컴파일러가 x*를 찾았다면 토큰 분리기는 x를 기호 테이블에서 찾는다. <br>
> 기호 테이블을 찾아본 결과 x가 데이터형이면 파서는 선언이 시작됐다고 결론을 지을 것이고 x가 데이터형이 아니면 변수라고 판단하여 곱셈일 경우만 유효하게 파싱될 것이다.

- 문맥 민감성에 대한 또 다른 예를 살펴보자
> X\<1\>(0), 여기서 X가 클래스 템플릿이라면 상수 0을 인자로 X\<1\>이라는 자료형의 객체를 생성하는 구문이다. <br>
> 하지만 X가 템플릿이 아니라면 ( X \< 1 ) \> 0 과 같은 대소 비교문으로 해석될 수 있다.

- 따라서 꺾쇠로 템플릿 인자 목록을 둘러싼 것은 여러모로 좋지 않다.
```c++
// NIP_07.cpp
template <bool B>
class Invert
{
public:
	static const bool result = !B;
};

void g( )
{
	bool test = Invert<(1>0)> ::result; // 괄호가 필요
}
```
- Invert\<(1\>0)\> 에서 괄호가 생략되었다면 1\>0 의 **'\>'가 템플릿 인자 목록을 닫았다고 잘 못 해석**된다.

## 데이터형의 종속 이름
- 템플릿에서 이름에 관련된 문제는 이름이 항상 잘 분류되는 것이 아니라서 발생한다.
- 템플릿은 다른 템플릿의 내부를 볼 수 없는데 다른 템플릿의 내용이 명시적 특수화에 의해 유효하지 않게 바뀔 수 있기 때문이다.
```c++
// NIP_08.cpp
template <typename T>
class Trap
{
public:
	enum { x }; // x는 데이터형이 아님
};

template <typename T>
class Victim
{
public:
	int y;
	void proof( )
	{
		Trap<T>::x* y; // 선언? 곱셈?
	}
};

template <>
class Trap<void>
{
public:
	typedef int x; // 여기서 x가 데이터형
};

void boom( Victim<void>& bomb )
{
	bomb.proof( );
}
```
- 컴파일러가 Trap\<T\>::x* y 를 파싱하면 이것이 선언인지 곱셈인지를 판단해야 한다. 이런 결정은 결국 종속되었고 한정된 이름인 Trap\<T\>::x 가 자료형인지 아닌지에 달려있다.
- 따라서 Trap의 내부를 살펴보고 데이터형인지 아닌지 확인하려고 할 것이다. 하지만 데이터형이 아닌 열거자였던 본래의 선언과는 달리 뒤에 제시된 특수화된 코드는 x가 데이터형이다.
- C++에서는 이 문제를 해결하기 위해 종속되고 한정된 이름의 경우 **키워드 typename 뒤에 오지 않는 한 데이터형을 나타낼 수 없게 하였다.** 템플릿 인자 치환 후 그 이름이 데이터형이 아니라면 인스턴화중 오류가 발생한다.
- 이름 앞에 덧붙인 typname은 다음과 같은 상황을 모두 만족하면 반드시 필요하다.

1\. 템플릿 내에 나타날 때 ( C++11 부터는 템플릿 내부가 아니여도 사용할 수 있다. )

2\. 한정돼 있을 때

3\. 기본 클래스 명세의 목록에서나 생성자 정의를 도입하는 멤버 초기화의 목록에서 사용되지 않을 때

4\. 템플릿 파라미터에 종속될 때
- 여기서 ~~1,~~ 2, 3 조건을 만족하지 않는다면 typename 접두사를 붙여서는 안된다.

```c++
// NIT_09.cpp
#include <string>

template <typename T>
class X
{
public:
	typedef std::string Base;
	typedef int C;
	typedef short D;
};

template <typename T> // 1 ok
struct S : typename X<T>::Base // 2 error 3번 규칙 X
{
	//	   3 error 3번 규칙 X	4 ok 필요하다.
	S( ) : typename X<T>::Base( typename X<T>::Base( 0 ) ) {}
	typename X<T> f( )	// 5 error 2번 규칙 X
	{
		typename X<T>::C* p;	// 6 ok
		X<T>::D * q;			// 곱하기이다.
		
		return X<T>( );
	}
	typename X<int>::C* s; // 7 ok 붙여도 되고 안 붙여도 된다.
};

struct U
{
	typename X<int>::C * pc; // 8 템플릿 내부가 아니라 실패해야 하는데 책과는 다르게 ok... gcc, vs community 2015에서도 컴파일 성공. ( C++11 부터 템플릿 내부가 아니여도 사용가능하다. )
};
```

## 템플릿 종속 이름
- 데이터형 이름과 함께 < 를 쓰는 경우, 컴파일러는 프로그래머가 template라는 키워드를 프로그램에 직접 사용하지 않으면 종속 이름이 템플릿을 참조한다고 간주하지 않는다.
```c++
// NIT_10.cpp
template <typename T>
class Shell
{
public:
	template <int N>
	class In
	{
	public:
		template <int M>
		class Deep
		{
		public:
			template <typename U>
			void g( )
			{
				std::cout << "g()" << std::endl;
			}
		};
	};
};

template <typename T, int N>
class Weird
{
public:
	void case1( typename Shell<T>::template In<N>::template Deep<N>* p )
	{
		p->template g<int>( );
	}

	void case2( typename Shell<T>::template In<N>::template Deep<N>& p )
	{
		p.template g<int>( );
	}
};
```
- 위의 예제는 이름을 한정시킬 수 있는 모든 연산자(::, -\>, .)를 사용하는 상황 중 키워드 template이 필요한 경우를 보여준다.
- 한정 연산자가 앞에 붙어있거나 표현식의 데이터형이 템플릿 파라미터에 종속적이고 연산자 뒤에 따라오는 이름이 템플릿 식별자인 경우 룩업을 통해서 이것이 템플릿인지를 살펴볼 수 없으므로 template를 앞에 삽입해 템플릿이라는 것을 알려야 한다.
> 예를 들어  p-\>template g\<int\>( ) 에서 p의 데이터형은 템플릿 파라미터 T에 종속적이다. template 접두사가 없다면 ((p-\>g)\<int)\>( )로 파싱된다.

## uinsg 선언에서 종속 이름
- using 선언( using-declation )은 네임스페이스와 클래스라는 두 공간에 이름을 불러드리는 것이다.
- using 선언을 통해서 기본 클래스의 이름을 파생 클래스로 불러올 수 있다.
```c++
// NIT_11.cpp
class BX
{
public:
	void f( int ) { std::cout << "BX::f(int)" << std::endl; }
	void f( const char* ) { std::cout << "BX::f( const char* )" << std::endl; }
	void g( ) { std::cout << "BX::g()" << std::endl; }
};

class DX : private BX
{
public:
	using BX::f;
};

int main( )
{
	DX dx;
	dx.f( 1 );
}
```
- 위의 예제는 기본 클래스 BX의 이름 f를 DX로 가져온다. **이런 종류의 using 선언은 접근 불가한 멤버인 멤버도 접근할 수 있게 한다는 점에 주의**해야 한다.
- DX의 공개 인터페이스 내에서 도입된 BX::f 함수만 빼고 나머지 기본 BX는 DX에게 private이다.
- 종속 클래스 내에서 using 선언은 이 이름이 데이터형 이름인지, 템플릿 이름인지 혹은 그 외의 이름인지 모르기 때문에 문제가 발생한다.
```c++
// NIT_11.cpp
template <typename T>
class BXT
{
public:
	typedef T Mystery;
	template <typename U>
	struct Magic;
};

template <typename T>
class DXTT : private BXT<T>
{
public:
	using typename BXT<T>::Mystery;		// typename을 빼면 gcc에서 컴파일 error VS 2015 community에서는 정상적으로 빌드 됨
	Mystery* p;
};
```
- 종속 이름에 대해 using 선언으로 해당 데이터형까지 불러들이려면 키워드 typename을 사용해야 한다. C++ 표준은 종속 이름을 템플릿처럼 표시하는 기능을 제공하지 않는다.
```c++
template <typename T>
class DXTM : private BXT<T>
{
public:
	// gcc 에서는 error vs 2015 community에서는 에러가 아님.
	using BXT<T>::template Magic;	// error 표준이 아님.
	Magic<T>* plink;				// error Magic은 알려진 템플릿이 아님.
};
```

## ADL과 명시적 템플릿 인자
- 아래와 같은 상황에서는 ADL을 통해 함수를 호출할 수 없다.
```c++
namespace N
{
	class X
	{

	};

	template <int N> void select( X* ) { std::cout << "select<int N>" << std::endl; };
}

void g( N::X* xp )
{
	select<3>( xp );
}
```
- select\<3\>( xp )라는 호출이 ADL을 통해 템플릿 select()로 해석되려면 <3>이 템플릿 인자 목록이라고 결정해야만 xp가 함수 호출 인자라고 결정할 수 있다.
- 또한, 컴파일러는 select()가 템플릿이라는 것을 알기 전까지 이것이 템플릿 인자 목록이라고 결정 내릴 수 없다. 따라서 위 표현식은 (select\<3)\>(xp)로 파싱돼 아무런 의미도 갖지 못한다.

## 파생과 클래스 템플릿
- 클래스 템플릿도 상속하거나 상속받을 수 있다. 클래스 템플릿과 템플릿이 아닌 클래스의 상속은 크게 다르지 않다.
- 하지만 클래스 템플릿을 *종속 이름으로 지칭되는 기본 클래스에서 파생시키려고 할 때 미묘한 문제가 발생*한다.

## 종속되지 않은 기본 클래스
- 클래스 템플릿에서 종속되지 않은 기본 클래스는 템플릿 인자를 알지 않아도 완전한 데이터형을 결정할 수 있는 클래스이다.
- 템플릿에서 종속되지 않은 기본 클래스들은 종속적이지 않은 일반 클래스들과 유사하게 동작하지만, 이상하게 동작하는 상황이 있다.
```c++
// NIT_13.cpp
template <typename X>
class Base
{
public:
	int basefield;
	typedef int T;
};

class D1 : public Base<Base<void>> // 이 클래스는 템플릿이 아니다.
{
public:
	void f( ) { basefield = 3; }
};

template <typename T>
class D2 : public Base<double>	// 종속되지 않은 기본 클래스
{
public:
	void f( ) { basefield = 7; }	// 일반적으로 상속받은 멤버로 접근
	T strange;						// T는 Base<double>::T 이지 템플릿 파라미터가 아님
};

void g( D2<int*>& d2, int* p )
{
	d2.strange = p;					// error
}
```
- 한정되지 않은 이름을 템플릿 파생에서 찾아볼 때는 **템플릿 파라미터의 목록들보다 먼저 종속적이지 않은 기본 클래스들을 고려**한다.
- 파생 템플릿의 작성자는 종속적이지 않은 기본 클래스에서 이름들에 대해(간접적으로 파생됐거나 해당 이름이 private라 하더라도) 알고 있어야 한다.

## 종속적인 기본 클래스
- 종속적이지 않은 기본 클래스에서는 **기본 클래스가 템플릿 파라미터에 종속적이지 않아서 기본 클래스 내의 종속적이지 않은 이름을 템플릿 정의가 나타나자마자 찾아볼 수 있었다.**
- 하지만 종속적인 기본 클래스는 그렇지 않다.
```c++
// NIT_14.cpp
template <typename X>
class Base
{
public:
	int basefield;
	typedef int T;
};

template <typename T>
class DD : public Base<T>			// 종속 기본 클래스
{
public:
	void f( ) { basefield = 0; }	// 1
};

template <>							// 명시적 특수화
class Base<bool>
{
public:
	enum { basefield = 42 };		// 2
};

void g( DD<bool>& d )
{
	d.f( );							// 3
}
```
- 1에서 종속적이지 않은 basefield를 룩업한다. 템플릿 Base에서 이 이름을 찾아서 거기서 찾은 int 멤버를 여기에 바인드한다고 하면 명시적 특수화로 Base의 선언을 오버라이딩하게 되어 이미 알고 있던 basefield의 의미를 enum으로 바꾸게 되고 2에서 특수화를 거치면 수정할 수 있는 basefield가 없어서 오류 메시지를 발생한다.
- 이런 문제를 우회하기 위해서 표준 C++은 종속적이지 않은 이름은 종속적인 기본 클래스에서 룩업되지 않는다고 정했다. 그래서 표준 C++ 컴파일러는 1에서 진단 메세지를 내보낸다.
- 이 문제는 basefield를 종속적으로 만드는 것만으로도 해결할 수 있다. 왜냐면 **종속 이름은 인스턴스화 시점에서만 룩업할 수 있기 때문**이다.
- basefield는 다음과 같은 2가지 방법으로 종속적으로 만들 수 있다.
```c++
// NIT_14.cpp
// 첫 번째 방법
template <typename T>
class DD1 : public Base<T>
{
public:
	void f( ) { this->basefield = 0; }
};

// 두 번째 방법
template <typename T>
class DD2 : public Base<T>
{
public:
	void f( ) { Base<T>::basefield = 0; }
};
```
- 두 번째 방법은 가상 함수를 호출할 때 한정되지 않고 종속되지 않은 이름이 쓰인다면 한정화로 인해 가상 함수의 호출이 억제돼 프로그램의 의미가 변할 수 있다. 그런데도 두 번째 방법이 적합한 경우가 존재한다.
```c++
// NIT_15.cpp
template <typename T>
class B
{
public:
	enum E { e1 = 6, e2 = 28, e3 = 496 };
	virtual void zero( E e = e1 );
	virtual void one( E& );
};

template <typename T>
class D : public B<T>
{
public:
	void f( )
	{
		typename D<T>::E e; // this->E는 유효한 문법이 아님
		this->zero( );		// D<T>::zero()는 가상성을 억제함
		one( e );			// 책에 따르면 종속적인 이름인데 컴파일 error가 발생한다. this-> 를 붙여 종속적으로 만들면 발생하지 않는다.
	}
};
```
- ~~one( e )이라는 호출에서 명시한 인자 중 하나가 종속적인 데이터형을 가졌기 때문에 이름 one 역시 종속적이다.~~
- 묵시적으로 사용된 기본 인자가 템플릿 파라미터에 종속적인 데이터형을 가진다면 컴파일러는 이것이 이미 룩업을 통해 결정된 상태가 될 때까지 그것을 검증할 수 없으므로 이 경우에는 종속적이 되지 않는다.
- 반복된 한정화로 코드가 난잡하게 됐다면 종속 기본 클래스의 이름을 파생 클래스로 가져와 계속 사용할 수 있다.
```c++
// NIT_14.cpp
// 세번째 방법
template <typename T>
class DD3 : public Base<T>
{
public:
	using Base<T>::basefield;		// 종속 이름이 영역 내에 있음
	void f( ) { basefield = 0; }	// ok
};
```
- using 선언은 인스턴스화될 때까지 검증되지 않기 때문에 원하는 것을 이룰 수 있다. 다만 이 방식에도 한계점이 있는데 이 클래스의 **기본 클래스가 여러 개라면 프로그램은 원하는 멤버를 가진 클래스를 정확히 알고 선택**해야 한다.