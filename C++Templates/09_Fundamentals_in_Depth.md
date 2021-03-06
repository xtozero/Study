# 템플릿 기호 원리의 깊은 이해
## 개요
- 여기서는 템플릿 선언, 템플릿 파라미터에 대한 제한과 템플릿 인자에 대한 제약 등에 대해 자세히 살펴본다.

## 파라미터화된 선언
- c++은 클래스 템플릿과 함수 템플릿이라는 두 종류의 템플릿을 지원한다. 물론 여기에는 멤버 템플릿도 포함된다.
- 이 같은 템플릿 선언은 일반 클래스나 함수와 유사하지만 다음과 같은 형태의 파라미터화 절이 붙는다는 점이 다르다.
```c++
template <... 파라미터 ...>
```
- 멤버 템플릿이 자신의 클래스 내부에서 선언될 때와 외부에서 선언될 때 파라미터화 절은 다음과 같이 작성한다.
```c++
// FID_01.cpp
template <typename T>
class List
{
public:
	template <typename T2>
	List( const List<T2>& list );
};

template <typename T>
template <typename T2>
List<T>::List( const List<T2>& list )
{
	// ...
}
```
- 멤버 템플릿이 자신의 클래스 외부에서 정의될 때 파라미터화 절은 **가장 밖을 둘러싼 클래스 템플릿에서부터 하나씩 나열**된다.
- 공용체 템플릿도 선언할 수 있고 클래스 템플릿의 일종으로 간주한다.
```c++
// FID_01.cpp
template <typename T>
union AllocChuck
{
	T object;
	unsigned char bytes[sizeof( T )];
};
```
- 함수 템플릿은 다른 일반 함수 선언처럼 기본 호출 인자를 가질 수 있다.
```c++
// FID_01.cpp
template <typename T>
void report_top( const std::vector<T>&, int number = 10 )
{
	// ...
}

template <typename T>
void fill( const std::vector<T>&, const T& = T( ) )
{
	// ...
}
```
- 두 번째 선언을 보면 기본 호출 인자가 템플릿 파라미터에 종속될 수 있다는 걸 알 수 있다.
- 함수 템플릿이 인스턴스화 될 때 기본 호출 인자를 명시적으로 제공한다면 기본 인자는 인스턴스화되지 않는다. 이를 통해서 특정 T에서는 인스턴스화될 수 없는 기본 호출 인자를 사용하더라도 오류가 발생하지 않게 할 수 있다.
```c++
// FID_01.cpp
class Value
{
public:
	Value( int ) {}		// 기본 생성자 없음
};

int main( )
{
	Value zero( 0 );
	std::vector<Value> v;

	fill( v, zero ); // T() 가 사용되지 않음.
	// fill( v ); error T() 가 사용됨.
}
```
- 기본적인 두 종류의 템플릿과 더불어 다음 세 가지 클래스 템플릿 멤버의 정의도 모두 파라미터화될 수 있다.

1\. 클래스 템플릿의 멤버 함수 정의

2\. 클래스 템플릿에 내포된 클래스 멤버 정의

3\. 클래스 템플릿의 정적 데이터 멤버 정의

- 이들도 파라미터화될 수 있지만, 이 정의가 항상 템플릿을 의미하는 것은 아니다. 이들의 파라미터는 전적으로 그들이 멤버로 속한 템플릿에 의해 결정된다.
```c++
// FID_01.cpp
template <int N>
class CupBoard
{
	void open( );
	class Shelf;
	static double total_weight;
};

template <int N>
void CupBoard<N>::open( )
{
	// ...
}

template <int N>
class CupBoard<N>::Shelf
{
	// ...
};

template <int N>
double CupBoard<N>::total_weight = 0.0;
```
- 파라미터화 선언을 보통 템플릿이라고 부르지만 위의 예제처럼 꼭 들어맞는 건 아니다.

## 가상 멤버 함수
- 멤버 함수 템플릿은 virtual로 선언될 수 없다.
> 가상 함수 호출 메커니즘은 대체로 가상 함수 하나당 하나의 엔트리를 갖는 고정 크기의 테이블(vftable)을 쓰는 방식으로 구현되는데 멤버 함수 템플릿은 템플릿 인자에 따라 무한히 인스턴스화 될 수 있기 때문이다.

- 이와 대조적으로 클래스 템플릿의 일반 멤버는 클래스가 인스턴스화될 때 그 수가 고정되기 때문에 virtual로 선언될 수 있다.
```c++
// FID_02.cpp
template <typename T>
class Dynamic
{
public:
	virtual ~Dynamic( ) {} // ok Dynamic<T> 당 하나의 소멸자
	template <typename T2>
	virtual void copy( const T2& ) {} // error Dynamic<T>의 인스턴스 내에서 copy() 인스턴스의 수를 결정할 수 없으므로
};
```

## 템플릿의 링크
- 모든 템플릿은 이름을 가지며 그 이름은 해당 영역 내에서 고유해야 한다.
> 함수 템플릿은 오버로딩 될 수 있다.

- 클래스형과 달리 클래스 템플릿은 다른 종류의 실체가 가진 이름을 공유할 수 없다.
```c++
// FID_03.cpp
int C;

class C; // ok 클래스 이름과 클래스가 아닌 이름은 다른 공간에 있음.

int X;

template <typename T>
class X; // error : 변수 X 와 충돌

struct S;

template <typename T>
class S; // error : struct S와 충돌
```
- 템플릿 이름은 링크를 가지지만 C 링크는 가질 수 없다.
```c++
// FID_03.cpp
extern "C++" template <typename T>
void normal( ) {} // 이것이 기본

extern "C" template <typename T>
void invalid( ) {} // error 템플릿은 C 링크를 가질 수 없음
```
- **템플릿은 일반적으로 외부 링크를 가진다.** 다만 static 지정자를 가지는 네임스페이스 영역 함수 템플릿만은 예외다.

## 기본 템플릿
- **템플릿에 대한 일반적인 선언을 기본 템플릿( primary template )**이라고 한다. 그러한 템플릿 선언에서 *템플릿 이름 뒤에는 꺾쇠로 둘러싸인 템플릿 인자가 따라오지 않는다.*
```c++
// FID_04.cpp
template <typename T> class Box;

template <typename T> class Box<T>; // error

template <typename T> void translate( T* );

template <typename T> void translate<T>( T* ); // error
```

## 템플릿 파라미터
- 템플릿 파라미터에는 세 종류가 있다.

1\. 데이터형 파라미터

2\. 데이터형이 아닌 파라미터

3\. 템플릿 템플릿 파라미터

- 템플릿 파라미터는 템플릿 선언의 도입부에 있는 파라미터화 절에서 선언된다. 이런 선언에는 이름을 생략할 수 있다.
```c++
template <typename, int>
class x
```
- 템플릿 내에서 파라미터를 참조할 것이라면 이름을 부여해야 한다. 템플릿 파라미터 이름은 그 이후의 파라미터 선언에도 사용될 수 있다.
```c++
template <typename T, T* Root, template<T*> class Buf>
class Structure
```

## 데이터형 파라미터
- 데이터형 파라미터는 typename이나 class로 도입되며 어떤 키워드를 사용하던 같다.
- 키워드 뒤에는 간단한 식별자가 따라 나오며 그 뒤에는 다음 파라미터 선언의 시작을 알리기 위한 쉼표나 파라미터화 절의 끝을 알리기 위한 닫기 꺾쇠( \> ) 혹은 기본 템플릿 인자의 시작을 알리기 위한 등호( = )가 나와야 한다.
- 템플릿 선언 내에서 데이터형 파라미터는 마치 typedef와 유사한 방식으로 동작하므로 만약 T가 템플릿 파라미터라면 class T라는 형태의 이름은 사용할 수 없다.
```c++
// FID_05.cpp
template <typename Allocator>
class List
{
	class Allocator* allocator;
	friend class Allocator;
	
	//...
};
```

## 데이터형이 아닌 파라미터
- 데이터형이 아닌 템플릿 파라미터는 컴파일이나 링크 시에 결정되는 상숫값을 말한다.
- 함수와 배열형 역시 데이터형이 아닌 파라미터로 명시될 수 있지만, 이들은 묵시적으로 포인터형으로 바뀐다.
```c++
// FID_05.cpp
template <int buf[5]> class Lexer;	// buf는 사실 int*
template <int* buf> class Lexer;	// ok 이것은 재선언
```
- 데이터형이 아닌 파라미터는 변수와 비슷한 방식으로 선언되지만 이들은 static, mutual과 같은 지시자를 가질 수 없다.
- 또한, const와 volatile과 같은 한정자를 가질 수 있지만, 한정자가 파라미터형의 맨 뒤에 있다면 그냥 무시한다.
```c++
// FID_05.cpp
template <int const length> class Buffer;	// const 무시
template <int length> class Buffer // 이전 선언과 동일
```

## 템플릿 템플릿 파라미터
- 템플릿 템플릿 파라미터는 클래스 템플릿을 갖기 위한 일종의 자리표시자이다.
- 이들의 선언은 클래스 템플릿과 유사하지만 struct와 union과 같은 키워드는 사용할 수 없다.
```c++
// FID_05.cpp
template <template <typename X> class C>
void f( C<int>* p );

template <template <typename X> struct C> // error
void f( C<int>* p );

template <template <typename X> union C> // error
void f( C<int>* p );
```
- 템플릿 템플릿 파라미터는 선언 영역 내에서 다른 클래스 템플릿과 같은 방식으로 사용된다.
```c++
// TB_05.cpp
template <typename T, template<typename ELEM> class CONT = std::deque>
class Stack
{
private:
	CONT<T> m_elems; // 클래스 템플릿과 같은 방식으로 사용된다.
	
	//...
```
- 템플릿 템플릿 파라미터는 기본 템플릿 인자를 가질 수 있다. 템플릿 템플릿 파라미터를 사용할 때 해당 파라미터가 지정되지 않았다면 기본 인자가 적용된다.
- **템플릿 템플릿 파라미터의 템플릿 파라미터의 이름은 그 템플릿 템플릿 파라미터의 다른 파라미터 선언에만 사용**된다.
```c++
// FID_05.cpp
template <template <typename T, T*> class Buf> // ok 파라미터화 구문애서는 사용 가능
class Edge
{
	//...
};

template <template <typename T> class List>
class Node
{
	T* storage; // error 템플릿 템플릿 파라미터의 파라미터는 여기서 사용할 수 없음
};
```
- 하지만 대체로 **템플릿 템플릿 파라미터의 템플릿 파라미터의 이름은 사용되지 않는다.** 대체로 이름 없이 남겨진다.
```c++
// FID_05.cpp
template <template <typename, typename = MyAllocator> class Container>
class Adaptataion
{
	Container<int> storage; // 묵시적으로 Container<int, MyAllocator>와 동일
};
```

## 기본 템플릿 인자
- 템플릿 파라미터는 기본 인자를 가질 수 있다. 기본 인자는 자신의 파라미터에 종속되지 않으나 이전 파라미터에 종속될 수 있다.
```c++
template <typename T, template Allocator = std::allocator<T>> class List;
```
- 연속된 기본 템플릿 인자는 하나의 템플릿 선언 내에서 제공될 뿐만 아니라 이전 선언을 기준으로 제공될 수 있다.
```c++
// FID_06.cpp
template <typename T1 = char, typename T2, typename T3, typename T4, typename T5> // error 함수의 기본 인자와 마찬가지이다.
class Test;

template <typename T1, typename T2, typename T3, typename T4 = char, typename T5 = char>
class Quintuple;

template <typename T1, typename T2, typename T3 = char, typename T4, typename T5> // ok T4와 T5는 이미 기본값을 가지고 있다.
class Quintuple;

template <typename T1, typename T2 = void>
class Value;

template <typename T1, typename T2 = void> // error 하지만 기본 인자를 반복해서 선언할 순 없다.
class Value;
```

## 탬플릿 인자
- 템플릿 인자는 템플릿이 인스턴스화될 때 **템플릿 파라미터를 치환** 값을 말한다. 이 값은 다양한 방식을 통해 결정된다.

1\. *명시적 템플릿 인자* : 꺾쇠 사이에 템플릿 인자 값을 두어 명시적으로 제공할 수 있다. 그 결과로 만들어진 이름을 템플릿 식별자라고 부른다.

2\. *삽입된 클래스 이름* : 템플릿 파라미터인 P1, P2...을 가지는 클래스 템플릿 X의 범위 내에서 해당 템플릿의 이름은 템플릿 식별자 X<P1, P2, ..> 와 동일하다.

3\. *기본 템플릿 인자* : 기본 템플릿 인자를 쓸 수 있다면 클래스 템플릿 인스턴스에서 템플릿 인자를 생략할 수 있다. 하지만 모든 템플릿 파라미터가 기본값을 가져도 꺾쇠는 써줘야 한다.

4\. *인자 추론* : 명시적으로 제시되지 않은 함수 템플릿 인자는 호출 시 함수 호출 인자의 데이터형을 통해 추론된다. **모든 템플릿 인자가 추론될 수 있다면 함수 템플릿의 이름 뒤에 꺾쇠를 붙이지 않아도 된다.**

## 함수 템플릿 인자
- 함수 템플릿을 위한 템플릿 인자는 명시되거나 템플릿이 사용된 방식에 따라 추론된다.
```c++
// FID_07.cpp
template <typename T>
inline const T& max( const T& lhs, const T& rhs )
{
	return lhs > rhs ? lhs : rhs;
}

int main( )
{
	max<double>( 1.0, -3.0 );	// 명시적인 템플릿 인자
	max( 1.0, -3.0 );			// 템플릿 인자가 함수의 인자로부터 추론
	max<int>( 1.0, 3.0 );		// 명시적인 <int>표기로 추론되지 않게 만듬. 결국 max<int>호출
}
```
- 어떤 템플릿 인자는 추론될 수 없다. 그런 파라미터는 템플릿 파라미터 목록의 맨 첫 부분에 위치시킨 후 다른 인자는 추론되게 두고 이런 인자만 명시할 수 있다.
> 첫 부분에 위치시키지 않는다면 모든 템플릿 인자를 명시해야 한다.

```c++
// FID_07.cpp
template <typename DstT, typename SrcT>
inline DstT implicit_cast( const SrcT& src ) // SrcT는 인자로부터 추론 가능하지만 DstT는 불가능
{
	return x;
}

double value = implicit_cast<double>(-1);
```
- 함수 템플릿은 오버로딩될 수 있으므로 함수 템플릿을 위해 모든 인자를 제공하는 것만으로 필요한 함수를 식별하기 어려울 수 있다.
```c++
// FID_08.cpp
#include <iostream>

template <typename Func, typename T>
void apply( Func func_ptr, T x )
{
	func_ptr( x );
}

template <typename T> void single( T ) { std::cout << "void single( T )" << std::endl; }

template <typename T> void multi( T ) { std::cout << "void multi( T )" << std::endl; }
template <typename T> void multi( T* ) { std::cout << "void multi( T* )" << std::endl; }

int main( )
{
	apply( &single<int>, 3 ); // ok

	apply( &multi<int>, 7 ); // error multi<int>가 하나가 아님.
}
```
- 위 예제에서 첫 번째 호출에서 single<int>가 모호하지 않기 때문에 정상적으로 호출될 수 있었으나 두 번째 호출에서는 하나 이상의 데이터형이 될 수 있으므로 Func가 추론될 수 없다.
- 또한, 함수 템플릿을 위해서 템플릿 인자를 명시하면 옳지 않은 자료형을 생성하려 시도할 수도 있다.
```c++
// FID_09.cpp
#include <iostream>

typedef char RT1;

struct RT2
{
	char a[2];
};

template <typename T> RT1 test( typename T::X const* ) { return RT1( ); }
template <typename T> RT2 test( T ) { return RT2( ); }

int main( )
{
	test( 1 ); // ok SFINAE
}
```
- 위 예제에서 test<int>라는 표현식에서 int에는 x라는 데이터형을 갖는 멤버가 없으므로 두 함수 템플릿 중 첫 번째에는 맞지 않는다. 하지만 두 번째 템플릿에서는 아무런 문제가 없다.
- 이런 **치환 실패는 오류가 아님**( SFINAE : Substitution Failure Is Not An Error ) 법칙은 함수 템플릿을 오버로딩할 경우 중요한 역할을 한다.
- 다음 예제는 주어진 데이터형 T가 클래스형인지를 컴파일할 때 검사하는 예제이다. ( 출처 : [http://en.cppreference.com/w/cpp/types/is_class](http://en.cppreference.com/w/cpp/types/is_class) )
```c++
// FID_09.cpp
namespace detail
{
	template <typename T> char test( int T::* );
	struct two { char c[2]; };
	template <typename T> two test( ... );
}

template <typename T, T v>
class x_integral_constant
{
public:
	static constexpr T value = v;
};

template <typename T>
class x_is_class : public x_integral_constant<bool, sizeof( detail::test<T>( 0 ) ) == 1 && !std::is_union<T>::value>
{
};

//...
std::cout << "int is class ? : " << ( x_is_class<int>::value ? "true" : "false" ) << std::endl;
std::cout << "RT2 is class ? : " << (x_is_class<RT2>::value ? "true" : "false" ) << std::endl;

union X
{
	int n;
	float f;
};

std::cout << "X is class ? : " << (x_is_class<X>::value ? "true" : "false") << std::endl;
```
- SFINAE 법칙은 유효하지 않은 데이터형을 만드는 시도를 보호할 뿐 잘못된 표현식을 계산하는 시도는 막지 않는다.
```c++
// FID_09.cpp
template <int N> void f( int( &)[24/(4-N)] ) {}
template <int N> void f( int( &)[24/(4+N)] ) {}

&f<4>; // gcc에서는 문제없다. vs 2015 community에서도 오류는 나지만 0으로 나눠서 발생하는 오류는 아니다.
```

## 데이터형 인자
- 템플릿형 인자는 템플릿형 파라미터를 위해 명시된 값이다. 대부분의 데이터형은 템플릿 인자로 사용될 수 있지만, 사용될 수 없는 예외가 두 가지 있다.
> 아래 내용은 C++11 부터는 해당하지 않는다. ([참고 링크](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2657.htm))

1\. 지역 클래스와 열거형은( 즉 함수 정의 내에 선언된 데이터형 ) 템플릿형 인자가 될 수 없다.

2\. 이름 붙여지지 않은 클래스 형( unnamed class type )이나 이름 붙여지지 않은 열거형( unnamed enumeration )에 속하는 데이터는 템플릿형 인자가 될 수 없다.
> 이름 붙여지지 않은 클래스형이나 이름 붙여지지 않은 열거형이라도 typedef로 이름을 부여하면 템플릿형 인자가 될 수 있다.

```c++
// FID_10.cpp
template <typename T> class List
{
	// ...
};

typedef struct
{
	double x, y, z;
} Point;

typedef enum { red, green, blue } *ColorPtr;

int main( )
{
	struct Association
	{
		int* p;
		int* q;
	};

	List<Association*> error1;	// error 템플릿 인자가 지역 데이터형
	List<ColorPtr> error2;		// error 템플릿 인자가 이름 없는 데이터형
	List<Point> ok;				// ok 이름 없는 클래스형을 typedef로 이름 붙임
}
```
- 기타 데이터형은 템플릿 인자로 사용할 수 있으나 템플릿 치환에 따른 템플릿 생성이 유효해야 한다.
```c++
// FID_10.cpp
template <typename T>
void clear( T p )
{
	*p = 0;
}

	int a;
	clear( a );					// error int는 단항 연산자 *를 지원하지 않는다.
```

## 데이터형이 아닌 인자
- 데이터형이 아닌 템플릿 인자는 데이터형이 아닌 파라미터를 치환하는 값이다. 이런 값은 다음에 나열된 사항 중 하나에 속해야 한다.

1\. 데이터형이 아닌 템플릿 파라미터로 올바른 데이터형을 가질 경우

2\. 컴파일 시 결정되는 정수형(혹은 열거형) 상숫값, 대응되는 파라미터가 그 값과 일치하는 데이터형을 가지거나 묵시적으로 해당 데이터형으로 변환될 수 있으면 가능하다.

3\. 외부 변수나 함수의 이름 앞에 내장 & 연산자가 붙는 경우, 함수나 배열 변수일 경우 &는 생략할 수 있다. 이같은 템플릿 인자는 데이터형이 아닌 포인터형 파라미터라고 할 수 있다.

4\. 멤버 접근 포인터 상수, 다시 말해 &C::m이라는 형태의 표현식에서 C가 클래스 형이고 m이 정적(static)이 아닌 멤버일 경우

5\. 이것은 멤버 접근 포인터형에 대한 데이터형이 아닌 파라미터에만 대응한다. 다른 환경에서는 이들이 유효한 묵시적 변환을 제공한다고 해도, 포인터나 참조자인 파라미터에 인자를 대응시킬 때엔 사용자 정의 변환과 파생 클래스에서 기본 클래스로의 변환은 고려되지 않는다. 인자에 const나 volatile을 더 붙이는 묵시적 변환은 괜찮다.

```c++
// FID_11.cpp
template <typename T, T nontype_param>
class C
{
};

C<int, 33>* cl;			// 정수형

int a;
C<int*, &a> c2;			// 외부 변수의 주소

void f( );
void f( int );
C<void( *)(int), f> c3;	// 함수의 이름 : 오버로딩 해석에 의해 f( int )를 선택

class X
{
public:
	int n;
	static bool b;
};

C<bool&, X::b>* c4;		// 정적 클래스 멤버는 수용가능

C<int X::*, &X::n>* c5;	// 멤버 접근 포인터 상수의 예

template<typename T>
void templ_func( );

C<void(*)( ), &templ_func<double>>* c6; // 함수 템플릿 인스턴스도 함수임

int main( )
{
}
```
- 템플릿 인자는 컴파일러나 링커가 프로그램을 빌드할 때 그들의 값을 표현할 수 있어야 한다는 일반적인 제약 조건을 만족시켜야 한다. *프로그램이 실행될 때까지 알려지지 않은 값은 프로그램을 빌드하는 중 인스턴스화되는 템플릿의 개념과 상충한다.*
- 하지만 아래 나열된 상숫값들은 유효한 템플릿 인자로 사용될 수 없다.

1\. 부동 소수점 숫자
```c++
// FID_11.cpp
constexpr float fv = 10.f;
C<float, fv>* c7; // error 부동소수점 숫자는 안됨
```

2\. 문자열 리터럴
```c++
// FID_11.cpp
const char* stringLiteral = "Hello Template";
C<char*, stringLiteral> c8; // error 문자열 리터럴도 안됨

// 상수 문자열로 초기화하려면 아래와 같은 방법으로 해야 한다.
extern const char  hello[] = "Hello World!"; // extern 빼면 const 배열 변수가 내부 링크를 가질 수 있으므로 주의
C<const char*, hello> c9;
```
- 그 외 데이터형이 아닌 인자가 될 수 없는 인자의 종류의 예를 몇 가지 더 들면 다음과 같다.
```c++
// FID_11.cpp
class Base
{
public:
	int i;
} base;

class Derived : public Base
{

} derived_obj;

C<Base*, &derived_obj> err1; // error 부모 클래스로의 변환은 고려되지 않는다.

C<int&, base.i> err2; // error 클래스 변수의 멤버 변수는 변수로 간주되지 않음.

int a[10];
C<int*, &a[0]> err3; // error 배열 내 개별 주소 역시 마찬가지
```

## 템플릿 템플릿 인자
- 템플릿 템플릿 인자는 자신이 치환할 템플릿 템플릿 파라미터와 **정확히 일치하는 파라미터를 가진 클래스 템플릿**이어야 한다. *템플릿 템플릿 인자의 기본 템플릿 인자는 무시된다.*
> 템플릿 템플릿 파라미터가 기본 인자를 가진다면 템플릿의 인스턴스화 과정에서 고려된다.

- 따라서 아래와 같은 예제는 유효하지 않다.
```c++
// FID_12.cpp
#include <list>
// list의 선언
// naspace std {
// template <typename T,
// typename Allocator = aollcator<T>>
// class list;
// }

template <typename T1, typename T2, template<typename> class Container> // Container는 하나의 파라미터를 갖는 템플릿을 기다림
class Relation
{
public:
	// ...

private:
	Container<T1> dom1;
	Container<T2> dom2;
};

int main( )
{
	Relation<int, double, std::list> rel; // 오류 std::list는 하나 이상의 템플릿 파라미터를 가짐
}
```
- 이 예제는 std::list가 하나 이상의 템플릿 파라미터를 가진다는 데 문제가 있다. 두 번째 파라미터는 *기본값을 갖긴 하지만 std::list를 Container 파라미터와 비교할 때에 고려되지 않는다.*
- 템플릿 템플릿 파라미터에서 파라미터에 기본값을 추가해 이 같은 현상을 해결해 볼 수 있다.
```c++
template <typename T1, typename T2, template<typename T, typename = std::allocator<T>> class Container> // Container는 이제 표준 컨테이너 템플릿을 수용할 수 있음.
```
- C++14까지는 class라는 키워드로만 템플릿 템플릿 파라미터를 선언할 수 있다. ([참고](http://en.cppreference.com/w/cpp/language/template_parameters) **하지만 gcc, vs 2015 community 버전에서도 된다.) 하지만 class 키워드로 선언된 클래스 템플릿만이 인자가 될 수 있다는 뜻으로 해석하면 안된다.** 구조체( struct ) 템플릿과 공용체( union ) 템플릿도 모두 템플릿 템플릿 파라미터를 위한 유효한 인자가 될 수 있다. 키워드 class로 선언된 템플릿 파라미터를 위해 어떤 종류의 데이터형도 쓸 수 있는 것과 유사하다.

## 동일
- 템플릿 인자의 두 집합은 인자의 값들이 1:1로 같을 때 동일하다고 본다. 데이터형 인자의 경우 typedef 이름은 중요하지 않고 가리키는 진짜 데이터형이 중요하다.
- 데이터형이 아닌 정수형 인자의 경우 인자의 값을 비교한다. 하지만 값을 어떻게 표현했는지는 중요하지 않다.
```c++
// FID_13.cpp
#include <iostream>
#include <type_traits>

template <typename T, int I>
class Mix {};

typedef int Int;

using Short = short;

int main( )
{
	std::cout << ( std::is_same<Mix<int, 3 * 3>, Mix<Int, 4 + 5>>() ? "true" : "false" ) << std::endl;
	std::cout << ( std::is_same<Mix<short, 2 + 5>, Mix<Short, 7>>::value ? "true" : "false") << std::endl;
}
```
- 함수 템플릿에서 생성된 함수는 이들이 동일한 데이터형과 동일한 이름을 가진다 하더라도 일반 함수와 동일할 수 없다. 이를 통해 클래스 멤버에 대한 중요한 두 가지 결과를 이끌어 낼 수 있다.

1\. 멤버 함수 템플릿에서 생성된 함수는 가상 함수를 오버라이딩하지 않는다.

2\. 생성자 템플릿에서 만들어진 생성자는 기본 복사 생성자가 될 수 없다.
> 이와 유사한 이유로 할당 템플릿에서 생성된 할당은 복사 항당 연산자가 될 수 없다. 그렇지만 복사 할당 연산자를 묵시적으로 호출하는 일은 더 드물어서 여기서 문제가 될 일은 많지 않다.

## 프렌드
- 프렌드는 한 클래스와 밀접한 관계를 맺는 클래스나 함수를 알리는 것이다. 프렌드는 다음과 같은 두 가지 특성이 있다.

1\. 프렌드 선언은 실체에 대한 선언만을 의미할 수 있다.

2\. 프렌드 함수 선언은 정의가 될 수 있다.

- 프렌드 클래스 선언은 정의가 될 수 없다. 템플릿에서의 프렌드 클래스 선언은 기존 문법과 달리 클래스 템플릿의 특정 인스턴스를 프렌드로 지칭할 수 있다.
```c++
// FID_14.cpp
template <typename T>
class Node
{
	// ...
};

template <typename T>
class Tree
{
	friend class Node<T>; // Node가 가시화돼 있지 않으면 오류이다.
};
```
- 템플릿 클래스의 인스턴스 중 하나가 클래스나 클래스 템플릿의 프렌드로 만들어지려면 해당 클래스 템플릿이 가시화돼야 한다.
> 일반 클래스는 이와 같은 조건이 붙지 않는다.

```c++
// FID_14.cpp
template <typename T>
class Tree
{
	friend class Factory; // Factory에 대한 첫 번째 선언이라 해도 괜찮다.
	friend class Node<T>; // Node가 가시화돼 있지 않으면 오류이다.
};
```

## 프렌드 함수
- 프렌드 함수의 이름 뒤에 꺾쇠를 붙임으로써 함수 템플릿의 인스턴스를 프렌드로 만들 수 있다. 꺾쇠는 인자가 추론된다면 빈 채로 둘 수 있다.
```c++
// FID_14.cpp
template <typename T1, typename T2>
void combine( T1, T2 ) {}

class Mixer
{
public:
	friend void combine<>( int&, int& ); // ok
	friend void combine<int, int>( int, int ); // ok
	friend void combine<char>( char, int ); // ok
	friend void combine<char>( char&, int& ); // error char와 char& 형이 맞지 않는다.
	friend void combine<char>( long, long ) {} // error 템플릿 인스턴스를 정의할 수 없다( 특수화를 정의할 수 있을 뿐이다. )
};
```
- 이름 뒤에 꺾쇠( \<\> )가 없다면 두 가지 상황이 가능하다.

1\. 이름이 한정되지 않았다면 ( ::가 없다면 ) 절대로 템플릿 인스턴스를 참조할 수 없다. 프렌드 선언의 시점에서 템플릿이 아닌 함수 중 일치하는 것이 없다면 프렌드 선언은 해당 함수에 대한 첫 번째 선언이 된다. 선언은 정의가 될 수도 있다.

2\. 이름이 한정됐다면 ( ::가 있다면 ) 그 이름은 이전에 선언된 함수나 함수 템플릿을 가리켜야만 한다. 함수와 함수 템플릿이 동시에 일치한다면 함수 쪽을 선호한다. 하지만 이런 프렌드 선언은 정의가 될 수 없다.

```c++
// FID_14.cpp
void multiply( void* ) {} // 일반 함수

template <typename T>
void multiply( T ) {} // 함수 템플릿

class Comrades
{
	friend void multiply( int ) {} // 새 함수 ::multiply(int)를 정의
	friend void ::multiply( void* ); // 일반 함수를 참조
	friend void ::multiply( int ); // 템플릿의 인스턴스를 참조
	friend void ::multiply<double*>( double* ); // 한정된 이름 뒤에도 꺾쇠가 나올 수 있다. 다만 템플릿은 가시화돼 있어야 한다.
	friend void ::error( ) {} // error 프렌드가 한정되어 있을 경우 정의가 될 수 없다.
};
```
- 위 예제에서 프렌드 함수는 일반 클래스에서 선언됐다. 클래스 템플릿에서 프렌드를 선언할 때에도 같은 법칙을 적용받지만 **프렌드로 할 함수를 식별할 때 템플릿 파라미터를 사용할 수 있다.**
```c++
// FID_14.cpp
template <typename T>
class Node 
{
	Node<T>* allocate();
};

template <typename T>
class List
{
	friend Node<T>* Node<T>::allocate( );
};
```
- 하지만 템플릿에서 선언만 된 그 어떤 것도 인스턴스화 될 때까지 실제로 존재하는 실체가 아니므로 클래스 템플릿에서 프렌드 함수를 정의하면 다음과 같은 현상이 일어난다.
```c++
// FID_14.cpp
template <typename T>
class Creator
{
	friend void appear( ) // 이 함수는 Creator가 인스턴스화될 때까지 존재하지 않는다.
	{

	}
};

int main( )
{
	Creator<void> miracle; // ::appear는 이 시점에서 생성된다.
	Creator<double> oops; // error ::appear가 두 번쨰로 생성되며 ODR을 어기게 된다.
}
```
- 따라서 **클래스 템플릿의 파라미터가 그 템플릿에서 정의된 어떤 프렌드 함수의 데이터형에 나타나는지를 확인**해야 한다.
```c++
// FID_14.cpp
template <typename T>
class Creator
{
	friend void feed( Creator<T>* ) {} // 모든 T는 다른 함수 ::feed()를 생성한다.
};
```
- 이렇게 하면 다른 자료형에 대해서 모든 인스턴스가 다른 함수를 생성한다. *이런 함수가 템플릿 인스턴스화 과정에서 생성되긴 했지만 함수 자체는 템플릿의 인스턴스가 아니라 **일반 함수**이다.*
> 이런 프렌드 함수는 몸체가 클래스 정의 내에 정의돼 있으므로 묵시적으로 인라인화됐다. 따라서 두 번역 단위 내에서 같은 함수가 또다시 정의된다 해도 오류가 아니다.

## 프렌드 템플릿
- 어떤 *템플릿의 모든 인스턴스를 프렌드로 선언한 것*을 **프렌드 템플릿**이라 한다.
```c++
// FID_14.cpp
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
```
- 일반 프렌드 함수처럼 프렌드 템플릿도 함수 이름에 꺾쇠가 뒤따라오지 않고 한정되지 않은 이름일 때만 정의될 수 있다. 또한, **기본 템플릿에 연관된 부분 특수화나 명시적 특수화는 자동으로 프렌드가 된다.**