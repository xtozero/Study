# C++ 11 이후의 Tuple
Tuple에 대한 또 다른 관점은 typelist의 실체화이다. 예를 들면 typelist Typelist\<int, double, std::string\> 은 컴파일 시간에 int, double, std::string 을 포함한 타입을 표현하고 Tuple\<int, double, std::string\> int, double, std::string을 위한 저장 공간을 표현한다.

## 기본 Tuple 디자인
### 저장소
Tuple은 템플릿 인자 리스트의 각 타입을 위한 저장소를 포함하고 있다. 해당 저장소는 함수 템플릿 get을 통해서 접근할 수 있다. 예를 들면 get\<0\>(t)은 t의 첫 번째 타입의 값을 되돌려 준다.

Tuple의 재귀적인 공식은 N \> 0개 요소를 단일 요소와 N - 1개의 요소로 저장할 수 있다는 것에 근거한다. 따라서 세 개의 요소를 가진 Tuple Tuple\<int, double, std::string\>는 int와 Tuple\<double, std::string\>로 저장될 수 있고 두 개의 요소를 가진 Tuple은 double과 Tuple\<std::string\>로 저장될 수 있다.

사실 이런 재귀적 분해 방식은 일반적인 typelist 알고리즘에서도 사용되었으며 재귀적 Tuple 저장의 구현도 유사하게 이뤄진다.
```c++
// Tuple.h
template <typename... Types>
class Tuple;

template <typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
private:
	Head head;
	Tuple<Tail...> tail;
public:
	Tuple() {}
	Tuple( const Head& head, const Tuple<Tail...>& tail ) : head( head ), tail( tail ) {}

	Head& getHead( ) { return head; }
	const Head& getHead( ) const { return head; }
	Tuple<Tail...>& getTail( ) { return tail; }
	const Tuple<Tail...>& getTail( ) const { return tail; }
};

template <>
class Tuple<>
{
};
```
재귀 단계에서 Tuple의 인스턴스는 첫번째 요소를 저장하는 Head와 나머지 요소를 저장하는 Tail 멤버 데이터를 포함하고 있다.

기저 단계는 단순히 빈 Tuple인데 관련된 저장공간이 없다.

get 함수 템플릿은 재귀 구조를 돌아다니며 요청한 요소를 추출한다.
```c++
// Tuple.h
template <unsigned N>
struct TupleGet 
{
	template <typename Head, typename... Tail>
	static const auto& apply( const Tuple<Head, Tail...>& t )
	{
		return TupleGet<N - 1>::apply( t.getTail( ) );
	}
};

template <>
struct TupleGet<0>
{
	template <typename Head, typename... Tail>
	static const Head& apply( const Tuple<Head, Tail...>& t )
	{
		return t.getHead( );
	}
};

template <unsigned N, typename... Types>
const auto& get( const Tuple<Types...>& t )
{
	return TupleGet<N>::apply( t );
}
```
함수 템플릿 get은 TupleGet의 정적 멤버 함수를 호출하는 단순한 래퍼 함수이다.

### 생성자
Tuple을 좀 더 유용하게 만들기 위해 독립적인 값의 집합과 다른 Tuple로 부터 Tuple을 생성할 수 있도록 해야 한다. 독립적인 값의 집합에서 Tuple을 생성하는 생성자는 이미 정의되어 있는데 사용자가 move 생성자를 통해서 Tuple을 생성하고자 할 수 있다. 따라서 Perfect forwarding을 사용해야 한다.
```c++
template <typename VHead, typename... VTail>
Tuple( VHead&& vhead, VTail&&... vtail ) : head( std::forward<VHead>( vhead ) ), tail( std::forward<VTail>( vtail )... ) {}
```
또한 다른 Tuple에서 Tuple을 생성할 수 있도록 해야 한다.
```c++
template <typename VHead, typename... VTail>
Tuple( const Tuple<VHead, VTail...>& other ) : head( other.getHead( ) ), tail( other.getTail( ) ) { }
```
하지만 이 생성자로는 Tuple 변환을 허용하는 데 충분치 않다. 다음과 같은 호환 가능한 타입을 사용한 초기화가 실패하게 된다.
```c++
// 01_T.cpp
Tuple<long int, long double, std::string> t2( t );
```
이는 독립적인 값의 집합을 인자로 받는 생성자가 Tuple을 받는 생성자보다 더 일치하기 때문에 발생하며 std::enable_if\<\>를 사용하여 해결해야 한다.
```c++
// Tuple.h
template <typename VHead, typename... VTail, typename = typename std::enable_if<sizeof...(VTail) == sizeof...(Tail)>::type>
Tuple( VHead&& vhead, VTail&&... vtail ) : head( std::forward<VHead>( vhead ) ), tail( std::forward<VTail>( vtail )... ) {}

template <typename VHead, typename... VTail, typename = typename std::enable_if<sizeof...( VTail ) == sizeof...( Tail )>::type>
Tuple( const Tuple<VHead, VTail...>& other ) : head( other.getHead( ) ), tail( other.getTail( ) ) { }
```
마지막으로 Tuple을 쉽게 생성하기 위한 도움 함수를 작성하자. makeTuple() 함수 템플릿은 요소의 집합을 통해서 반환해야 할 Tuple의 타입을 결정하여 튜플을 쉽게 만들 수 있게 한다.
```c++
// Tuple.h
template <typename... Types>
auto makeTuple( Types&&... elems )
{
	return Tuple<std::decay_t<Types>...>( std::forward<Types>( elems )... );
}
```
상수 문자열과 배열형을 포인터형으로 변환하고 const와 &를 제거하기 위해서 std::decay<>를 사용하였다. 이제 makeTuple을 이용하여 다음과 같이 Tuple을 생성할 수 있다.
```c++
// 01_T.cpp
auto t3 = makeTuple( 17, 3.14, "Hello, World!" );
auto t4 = makeTuple( 1, 2, 3, 4, 5, 6, 7, 8 );
```
## 기본 Tuple 연산
### 비교
Tuple은 다른 값을 포함하는 구조의 타입이므로 두 개의 Tuple을 비교하려면 그들의 요소를 비교해야 한다.
```c++
// Tuple.h
bool operator==( const Tuple<>&, const Tuple<>& )
{
	return true;
}

template <typename Head1, typename... Tail1,
		typename Head2, typename... Tail2,
		typename = std::enable_if_t<sizeof...( Tail1 ) == sizeof...( Tail2 )>>
	bool operator==( const Tuple<Head1, Tail1...>& lhs, const Tuple<Head2, Tail2...>& rhs )
{
	return lhs.getHead( ) == rhs.getHead( ) && lhs.getTail( ) == rhs.getTail( );
}
```
typelist와 tuple의 많은 알고리즘과 마찬가지로 요소 비교는 첫 번째 요소를 방문하여 기저 조건에 도달할 때까지 재귀적으로 나머지 요소를 방문한다.
### 출력
tuple의 내용을 손쉽게 확인하기 위해서 operator\<\<을 정의하여 tuple을 출력해보자.
```c++
// Tuple.h
void printTuple( std::ostream& strm, const Tuple<>&, bool isFirst = true )
{
	strm << ( isFirst ? '(' : ')' );
}

template <typename Head, typename... Tail>
void printTuple( std::ostream& strm, const Tuple<Head, Tail...>& t, bool isFirst = true )
{
	strm << ( isFirst ? "(" : ", " );
	strm << t.getHead( );
	printTuple( strm, t.getTail( ), false );
}

template <typename... Types>
std::ostream& operator<<( std::ostream& strm, const Tuple<Types...>& t )
{
	printTuple( strm, t );
	return strm;
}
```
이제 손쉽게 Tuple을 출력할 수 있게 되었다.
```c++
std::cout << makeTuple( 1, 2.5, std::string( "Hello" ) ) << std::endl; //(1, 2.5, Hello)
```
## Tuple 알고리즘
Tuple 알고리즘은 컴파일 타임 및 런타임 계산이 모두 요구되기 때문에 특히 흥미롭다.

Tuple에 알고리즘을 적용하면 typelist와 같이 컴파일 타임 계산이 필요한 완전히 다른 타입의 tuple이 계산될 수 있다. 예를 들어 Tuple\<int, double, string\>을 뒤집으면 Tuple\<string, double, int\>가 된다. 하지만 튜플 알고리즘은 실제로 런타임에 코드를 실행해야 하므로 생성된 코드의 효율성을 염두에 두어야 한다.
### Tuple을 Typelists와 같이 다루기
Tuple은 런타임 구성 요소를 무시하면 Typelist와 정확히 같은 구조로 되어 있다. 약간의 부분 특수화를 통해 Tuple을 typelist로 바꿀 수 있다.
```c++
// TupleTypelist.h
template <>
struct IsEmpty<Tuple<>>
{
	static constexpr bool value = true;
};

template <typename Head, typename... Tail>
class FrontT<Tuple<Head, Tail...>>
{
public:
	using Type = Head;
};

template <typename Head, typename... Tail>
class PopFrontT<Tuple<Head, Tail...>>
{
public:
	using Type = Tuple<Tail...>;
};

template <typename... Types, typename Element>
class PushFrontT<Tuple<Types...>, Element>
{
public:
	using Type = Tuple<Element, Types...>;
};

template <typename... Types, typename Element>
class PushBackT<Tuple<Types...>, Element>
{
public:
	using Type = Tuple<Types..., Element>;
};
```
이제 typelist에 동작하는 알고리즘이 Tuple에도 동등하게 동작한다.
```c++
// 02_t.cpp
Tuple<int, double, std::string> t1( 17, 3.14, "Hello World!" );
using T2 = PopFront<PushBack<decltype( t1 ), bool>>;
T2 t2( get<1>( t1 ), get<2>( t1 ), true );
std::cout << t2; // (3.14, Hello World!, 1)
```
앞으로 살펴보겠지만 Tuple 타입에 적용된 typelist 알고리즘은 Tuple 알고리즘의 결과 타입 결정에 유용하게 사용할 수 있다.
### Tuple에 요소 추가, 제거하기
Tuple의 처음 또는 끝에 요소를 추가하는 기능은 Tuple의 고급 알고리즘을 구현하는 데 중요하다. typelist처럼 Tuple의 앞에 요소를 추가하는 것은 맨 끝에 추가하는 것보다 쉽다. 따라서 PushFront부터 시작하도록 하자.
```c++
// TupleAlgorithm.h
template <typename... Types, typename V>
PushFront<Tuple<Types...>, V> pushFront( const Tuple<Types...>& tuple, const V& value )
{
	return PushFront<Tuple<Types...>, V>( value, tuple );
}
```
기존 Tuple의 앞부분에 새로운 요소를 추가하려면 새로운 요소의 값과 기존 튜플을 통해 새로운 튜플 타입을 생성해야 한다. 결과 튜플 타입은 Tuple\<V, Types...\>이 된다.

PushFront는 적절한 런타임 값을 위한 타입을 컴파일 타임에 계산한다.

새로운 요소를 맨 끝에 추가하는 것은 좀 더 복잡하다.
```c++
// TupleAlgorithm.h
template <typename V>
Tuple<V> pushBack( const Tuple<>&, const V& value )
{
	return Tuple<V>( value );
}

template <typename Head, typename... Tail, typename V>
Tuple<Head, Tail..., V> pushBack( const Tuple<Head, Tail...>& tuple, const V& value )
{
	return Tuple<Head, Tail..., V>( tuple.getHead( ), pushBack( tuple.getTail( ), value ) );
}
```
기저의 경우 예상한 대로 추가할 요소를 가진 Tuple을 반환한다. 재귀의 경우 목록의 처음에 있는 요소와 새로운 요소를 리스트의 끝에 추가한 결과로 새로운 Tuple을 생성한다. 또한, 결과 타입을 표현하기 위해 선택한 Tuple\<Head, Tail..., V\>는 컴파일 타입 PushBack\<Tuple\<Head, Tail...\>, V\>와 같다.

popFront는 구현하기 쉽다.
```c++
// TupleAlgorithm.h
template <typename... Types>
PopFront<Tuple<Types...>> popFront( const Tuple<Types...>& tuple )
{
	return tuple.getTail( );
}
```
이제 다음과 같은 코드를 작성할 수 있다.
```c++
// 03_T.cpp
auto t3 = popFront( pushBack( Tuple<int, double, std::string>( 17, 3.14, "Hello, World!" ), true ) );
std::cout << t3 << std::endl; // (3.14, Hello, World!, 1)
```
### Tuple 뒤집기
Tuple의 요소는 또 다른 Tuple 재귀 알고리즘을 통해 뒤집을 수 있다.
```c++
// TupleAlgorithm.h
Tuple<> reverse( const Tuple<>& t )
{
	return t;
}

template <typename Head, typename... Tail>
Reverse<Tuple<Head, Tail...>> reverse( const Tuple<Head, Tail...>& t )
{
	return pushBack( reverse( t.getTail( ) ), t.getHead( ) );
}
```
기저의 경우 빈 Tuple이므로 명백하다. 재귀의 경우 Tail에 대해서 재귀적으로 reverse를 수행하고 현재 Head를 맨 뒤에 추가하면 된다.

이제 typelist와 같이 popBack()을 손쉽게 구현할 수 있다.
```c++
// TupleAlgorithm.h
template <typename... Types>
PopBack<Tuple<Types...>> popBack( const Tuple<Types...>& t )
{
	return reverse( popFront( reverse( t ) ) );
}
```
### 인덱스 리스트
이전에 구현한 reverse은 불필요한 런 타임 계산을 요구한다. 이 문제를 살펴보기 위해서 복사 횟수를 세는 간단한 클래스를 도입해보자.
```c++
// copycounter.h
template <int N>
struct CopyCounter
{
	static int numCopies;
	CopyCounter( ) {}
	CopyCounter( const CopyCounter& ) { ++numCopies; }
};

template <int N>
int CopyCounter<N>::numCopies = 0;
```
그리고 CopyCounter의 Tuple을 생성하고 뒤집어 보자.
```c++
// 03_T.cpp
Tuple<CopyCounter<0>, CopyCounter<1>, CopyCounter<2>, CopyCounter<3>, CopyCounter<4>> copies;
auto t6 = reverse( copies );
std::cout << "0: " << CopyCounter<0>::numCopies << " copies\n";
std::cout << "1: " << CopyCounter<1>::numCopies << " copies\n";
std::cout << "2: " << CopyCounter<2>::numCopies << " copies\n";
std::cout << "3: " << CopyCounter<3>::numCopies << " copies\n";
std::cout << "4: " << CopyCounter<4>::numCopies << " copies\n";

/* 출력 결과
0: 5 copies
1: 8 copies
2: 9 copies
3: 8 copies
4: 5 copies
*/
```
매우 많은 복사가 일어나는 것을 확인할 수 있다. 이상적인 reverse 구현에서는 각 요소는 단 한 번만 복사돼야 한다. 원복 Tuple에서 결과 Tuple로 적합한 위치를 찾아서 바로 복사한다면 이 목표를 달성할 수 있을 것이다.

불필요한 복사를 어떻게 제거할 수 있을지 생각해보면 다음과 같이 makeTuple과 get을 사용하는 방법을 떠올릴 수 있다.
```c++
auto t7 = makeTuple( get<4>( copies ), get<3>( copies ), get<2>( copies ), get<1>( copies ), get<0>( copies ) );
std::cout << "0: " << CopyCounter<0>::numCopies << " copies\n";
std::cout << "1: " << CopyCounter<1>::numCopies << " copies\n";
std::cout << "2: " << CopyCounter<2>::numCopies << " copies\n";
std::cout << "3: " << CopyCounter<3>::numCopies << " copies\n";
std::cout << "4: " << CopyCounter<4>::numCopies << " copies\n";

/* 출력 결과
0: 1 copies
1: 1 copies
2: 1 copies
3: 1 copies
4: 1 copies
*/
```
인덱스 리스트(혹은 인덱스 시퀀스)는 Tuple의 인덱스를 포착하는 것으로 이런 개념을 일반화하였다. 이 경우 4, 3, 2, 1, 0은 파라메타 팩화되어 팩 확장을 통해서 get을 호출할 수 있도록 한다.

이것은 런 타임 효율성이 중요한 곳에서 복잡한 템플릿 메타 프로그램이 될 수 있는 인덱스 계산을 분리할 수 있게 해준다.

표준 타입 std::integer_sequence는 이런 인덱스 리스트를 나타낸다.
### 인덱스 리스트로 뒤집기
인덱스 리스트로 Tuple을 뒤집기 위해서 먼저 인덱스 리스트가 필요하다. 인덱스 리스트는 다른 typelist나 이종 데이터 구조의 인덱스로 사용되는 값을 담고 있는 typelist이다.

여기서는 이전에 구현한 ValueList 타입을 사용하여 인덱스 리스트를 구성한다. 5개의 요소를 담고 있는 Tuple을 뒤집는 상황에 해당하는 인덱스 리스트는 다음과 같다.
```c++
Valuelist<unsigned, 4, 3, 2, 1, 0>;
```
이런 인덱스 리스트를 어떻게 만들 수 있을까? 한 가지 접근법은 0에서 N - 1까지의 인덱스 리스트를 생성하는 것에서 시작하는 것이다.
```c++
// indexList.h
template <unsigned N, typename Result = Valuelist<unsigned>>
struct MakeIndexListT : MakeIndexListT<N - 1, PushFront<Result, CTValue<unsigned, N - 1>>>
{
};

template <typename Result>
struct MakeIndexListT<0, Result>
{
	using Type = Result;
};

template <unsigned N>
using MakeIndexList = typename MakeIndexListT<N>::Type;
```
이제 이 인덱스 리스트를 뒤집어서 원하는 인덱스 리스트를 구성할 수 있다.
```c++
using MyIndexList = Reverse<MakeIndexList<5>>;
```
실제로 Tuple을 뒤집으려면 인덱스 리스트의 인덱스가 타입이 아닌 파라미터 팩으로 캡처될 필요가 있다. 인덱스 집합 reverse() 알고리즘의 구현을 2부분으로 나눠서 이를 해결할 것이다.
```c++
// TupleAlgorithm.h
template <typename... Elements, unsigned... Indices>
auto reverseImpl( const Tuple<Elements...>& t, Valuelist<unsigned, Indices...> )
{
	return makeTuple( get<Indices>( t )... );
}

template <typename... Elements>
auto reverse( const Tuple<Elements...>& t )
{
	return reverseImpl( t, Reverse<MakeIndexList<sizeof...( Elements )>>( ) );
}
```
reverse() 함수는 단지 적절한 인덱스 집합을 생성하여 reverseImpl 알고리즘에 제공한다.

인덱스는 템플릿 메타 프로그램으로 조작되므로 런 타임에 동작하는 코드가 존재하지 않는다. 런 타임 코드는 reverseImple의 makeTuple을 사용하여 Tuple을 생성하는 부분뿐이므로 Tuple의 각 요소가 단 한 번만 복사된다.
### Shuffle 과 Select
이전에 구현한 reverseImpl() 함수 템플릿은 뒤집는 연산이 포함되어 있지 않다. 특정한 인덱스 집합에 따라 기존의 Tuple에서 선택하여 새로운 Tuple을 생성한다. 많은 알고리즘의 핵심이 바로 이런 Select() 연산이다.
```c++
// TupleAlgorithm.h
template <typename... Elements, unsigned... Indices>
auto select( const Tuple<Element...>& t, Valuelist<unsigned, Indices...> )
{
	return makeTuple( get<Indices...>( t )... );
}
```
select()를 기반으로 만들어지는 간단한 알고리즘 중 하나가 splat 연산이다.

splat 연산은 하나의 tuple의 단일 요소를 원하는 개수대로 증가시켜 새로운 tuple을 만든다.
```c++
// TupleAlgorithm.h
template <unsigned I, unsigned N, typename IndexList = Valuelist<unsigned>>
class ReplicatedIndexListT;

template <unsigned I, unsigned N, unsigned... Indices>
class ReplicatedIndexListT<I, N, Valuelist<unsigned, Indices...>> 
	: public ReplicatedIndexListT<I, N - 1, Valuelist<unsigned, Indices..., I>> 
{};

template <unsigned I, unsigned... Indices>
class ReplicatedIndexListT<I, 0, Valuelist<unsigned, Indices...>>
{
public:
	using Type = Valuelist<unsigned, Indices...>;
};

template <unsigned I, unsigned N>
using ReplicatedIndexList = typename ReplicatedIndexListT<I, N>::Type;

template <unsigned I, unsigned N, typename... Elements>
auto splat( const Tuple<Elements...>& t )
{
	return select( t, ReplicatedIndexList<I, N>( ) );
}
```
splat 연산의 결과는 다음과 같다.
```c++
// T_03.cppp
Tuple<int, double, std::string> t8( 42, 7.7, "hello" );
auto a = splat<1, 4>( t8 );
std::cout << a << std::endl;
/* 출력결과
(7.7, 7.7, 7.7, 7.7)
*/
```
복잡한 Tuple 알고리즘도 인덱스 리스트의 메타 프로그램을 통해 구현될 수 있다.

예를 들어 23_typelist 에서 자료형의 크기로 정렬하는 알고리즘을 구현하였는데 정렬 알고리즘을 Tuple에 대해서도 구현할 수 있다.
```c++
// TupleAlgorithm.h
template <typename List, template <typename T, typename U> class F>
class MetafunOfNthElementT
{
public:
	template <typename T, typename U> class Apply;

	template <unsigned N, unsigned M>
	class Apply<CTValue<unsigned, M>, CTValue<unsigned, N>> : public F<NthElement<List, M>, NthElement<List, N>>{ };
};

template <template <typename T, typename U> class Compare, typename... Elements>
auto sort( const Tuple<Elements...>& t )
{
	return select( t, InsertionSort<MakeIndexList<sizeof...( Elements )>, MetafunOfNthElementT<Tuple<Elements...>, Compare>::template Apply>( ) );
}
```
InsertionSort 사용법을 주의 깊게 살펴보면 정렬될 실제 typelist는 MakeIndexList\<\>로 생성된 인덱스의 리스트이다.

따라서 삽입 정렬의 결과는 Tuple에 대한 인덱스 집합이고 그다음 select() 연산에 사용된다. 하지만 InsertionSort가 인덱스에 대해서 동작하기 때문에 두 인덱스를 비교할 것으로 예상하는데 이것은 다음과 같이 std::vector의 인덱스를 정렬하는 예제를 살펴보면 이해하기 쉽다.
```c++
#include <vector>
#include <algorithm>
#include <string>
int main()
{ 
	std::vector<std::string> strings = { "banana", "apple", "cherry" };
	std::vector<unsigned> indices = { 0, 1, 2 };
	std::sort( indices.begin( ), indices.end( ),
		[&strings]( unsigned i, unsigned j ) {
		return strings[i] < strings[j];
	} );
}
```
여기서 indices는 문자열 vector의 인덱스로 sort()는 실제 인덱스를 정렬한다. 따라서 비교를 위해 제공된 람다는 부호 없는 두 개의 값을 받는다.

하지만 람다의 본문은 부호 없는 값을 문자열 vector의 인덱스로 사용한다. 그래서 순서는 실제 문자열 벡터의 내용을 따르게 된다. 정렬이 끝나면 인덱스는 문자열 vector에 인덱스를 제공하고 문자열의 값에 따라 정렬되게 된다.

tuple의 sort()에서도 같은 접근법을 채용하였다. 어댑터 템플릿 MetafunOfNthElementT는 두 개의 인덱스를 받는 템플릿 메타함수를 제공하고 NthElement를 사용하여 Typelist 인자에서 대응하는 요소를 추출한다.

멤버 템플릿 Apply는 추출된 요소를 메타 함수에 제공하여 비교가 이뤄지게 된다. sort의 모든 연산은 컴파일 타임에 이뤄지며 결과로 생성된 tuple은 런타임에 외부 복사본이 없는 상태로 직접 형성된다.

마지막으로 sort 연산의 결과는 다음과 같다.
```c++
// T_03.cppp
template<typename T, typename U>
class SmallerThanT
{
public:
	static constexpr bool value = sizeof( T ) < sizeof( U );
};

auto t9 = makeTuple( 17LL, std::complex<double>( 42, 77 ), 'c', 42, 7.7 );
std::cout << t1 << std::endl;
auto t10 = sort<SmallerThanT>( t1 );
std::cout << "sorted by size: " << t2 << std::endl;
/* 출력 결과
(16, 17, 3.14, Hello World!)
sorted by size: (17, 3.14, Hello, Template!)
*/
```
## Tuple 확장
튜플은 관련된 값의 집합을 하나의 값으로 다루는 데 유용하다. 어떤 자료형이 있는지 얼마나 많은 값이 관련되어 있는지는 고려하지 않아도 된다.

때때로 이런 Tuple의 값을 풀어야 할 필요가 있다. Tuple의 요소를 함수의 분리된 인자로 전달하는 것을 예로 들 수 있겠다.

간단한 예로 Tuple을 아래와 같이 variadic print() 함수로 전달하고자 할 수 있다.
```c++
Tuple<std::string, char const*, int, char> t("Pi", "is roughly", 3, '\n');
print(t…); //ERROR: Tuple은 parameter pack이 아니므로 확장할 수 없다.
```
보다시피 Tuple은 parameter pack이 아니므로 확장할 수 없다. 하지만 index list를 사용하여 같은 동작을 할 수 있다.

apply() 템플릿 함수는 함수와 Tuple을 인자로 받은 다음 Tuple의 요소를 풀어 함수를 호출해준다.
```c++
template <typename F, typename... Elements, unsigned... Indices>
auto applyImpl( F f, const Tuple<Elements...>& t, Valuelist<unsigned, Indices...> )
-> decltype( f( get<Indices>( t )... ) )
{
	return f( get<Indices>( t )... );
}

template <typename F, typename... Elements, unsigned N = sizeof...( Elements )>
auto apply( F f, const Tuple<Elements...>& t ) -> decltype(applyImpl(f, t, MakeIndexList<N>()))
{
	return applyImpl( f, t, MakeIndexList<N>( ) );
}
```
applyImpl() 함수는 인덱스 리스트를 받아 Tuple의 요소를 확장하여 함수 객체 인자 f에 인자 리스트를 전달한다.

apply()는 초기 인덱스 리스트를 생성할 책임만을 갖는다.

이제 apply를 사용해서 print()의 인수에 튜플을 확장할 수 있다.
```c++
// 04_T.cpp
Tuple<std::string, char const*, int, char> t( "Pi", "is roughly", 3, '\n' );
apply( print<std::string, char const*, int, char>, t ); // variadic template 으로 작성된 print를 인자 없이 넘기기 때문에 알맞은 함수 추론이 안 된다. 따라서 명시적으로 템플릿 인자를 적어서 호출해야 한다.
```
## Tuple 최적화
Tuple의 컴파일 타임이나 런타임 최적화를 고려하는 것은 가치가 있다. 여기서는 몇 가지 Tuple 최적화를 살펴보고자 한다.

### Tuple과 EBCO
지금까지 살펴본 Tuple 구현은 낭비되는 저장공간이 존재한다. 한 가지 문제는 비어 있지 않은 모든 Tuple이 빈 Tuple로 끝나기 때문에 Tail 맴버가 결국 빈 Tuple이 된다는 것이다. 따라서 항상 최소 1바이트의 저장 공간을 가져야 한다.

Tuple의 저장 공간 효율성을 개선하기 위해서 Tail을 멤버 변수로 하기보다 상속을 받아 EBCO( empty base class optimization )를 적용할 수 있다.
```c++
// TupleOptimize.h
template <typename... Types>
class Tuple;

template <typename Haed, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...>
{
private:
	Head head;

public:
	Head& getHead( ) { return head; }
	const Head& getHead( ) const { return head; }
	Tuple<Tail...>& getTail( ) { return *this; }
	const Tuple<Tail...>& getTail( ) const { return *this; }
};
```
불행하게도 이 구현은 초기화되는 멤버의 순서가 역전되는 부수효과를 가지고 있다. 이전 구현에서 head 멤버는 tail 멤버 보다 앞에 선언되었기에 먼저 초기화되었다. 새로운 구현에서는 tail이 기본 클래스에 있기 때문에 head보다 먼저 초기화된다.

이 문제는 head 멤버를 tail보다 먼저 상속되는 기본 클래스에 넣음으로써 해결할 수 있다.
```c++
// TupleOptimize2.h
template <typename... Types>
class Tuple;

template <typename T>
class TupleElt
{
	T value;

public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : value( std::forward<U>( other ) ) {}

	T& get( ) { return value; }
	const T& get( ) const { return value; }
};

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<Head>, private Tuple<Tail...>
{
public:
	Head& getHead( ) 
	{ 
		return static_cast<TupleElt<Head*>>(this)->get(); 
	}
	const Head& getHead( ) const
	{ 
		return static_cast<TupleElt<const Head*>>( this )->get( );
	}
	Tuple<Tail...>& getTail( ) { return *this; }
	const Tuple<Tail...>& getTail( ) const { return *this; }
};

template <>
class Tuple<>
{
};
```
이 방법은 초기화 순서 문제를 해결하지만 새로운 문제를 안고 있다. Tuple<int, int>와 같이 2개의 요소가 같은 자료형을 가진 Tuple에서 요소를 추출할 수 없다.

이는 기본 클래스로의 변환이 ( Tuple에서 TupleElt로의 변환 ) 모호해지기 때문이다.

모호성을 명확하게 하려면 각 TupleElt 기본 클래스가 주어진 Tuple 내에서 유일하게 만들어야 한다.

한 가지 접근법은 높이를 인코딩하는 것이다. Tuple의 마지막 요소는 높이 0과 함께 저장되고 그다음 요소는 높이 1과 함께 저장될 것이다.
```c++
// TupleOptimize3.cpp
template <typename... Types>
class Tuple;

template <unsigned Height, typename T>
class TupleElt
{
	T value;

public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : value( std::forward<U>( other ) ) {}

	T& get( ) { return value; }
	const T& get( ) const { return value; }
};

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<sizeof...(Tail), Head>, private Tuple<Tail...>
{
public:
	using HeadElt = TupleElt<sizeof...( Tail ), Head>;
	Head& getHead( )
	{
		return static_cast<HeadElt*>( this )->get( );
	}
	const Head& getHead( ) const
	{
		return static_cast<const HeadElt*>( this )->get( );
	}
	Tuple<Tail...>& getTail( ) { return *this; }
	const Tuple<Tail...>& getTail( ) const { return *this; }
};

template <>
class Tuple<>
{
};
```
다음 프로그램을 통해 실제 tuple의 크기를 살펴보자
```c++
// 05_Tuple.cpp
#include "TupleOptimize3.h"
#include <iostream>

struct A
{
	A( )
	{
		std::cout << "A()" << std::endl;
	}
};

struct B
{
	B( )
	{
		std::cout << "B()" << std::endl;
	}
};

int main( )
{
	Tuple<A, char, A, char, B> t1;
	std::cout << sizeof( t1 ) << " bytes" << std::endl; // vs 2015 에서 6, g++ 에서 5
}
```
빈 Tuple이 최적화되어 1바이트가 사라진다. 하지만 A와 B가 빈 클래스이므로 EBCO를 적용할 기회가 남아있다. 이를 위해서 TupleElt를 약간 확장할 수 있다.
> 다만 g++에서만 확인할 수 있었다. vs 2015에서는 재미있게도 built-in 자료형이 아니면 EBCO가 적용되지 않았다.

```c++
// TupleOptimizeFinal.h
#include <utility>
#include <type_traits>

template <typename... Types>
class Tuple;

template <unsigned Height, typename T, bool = std::is_class<T>::value && !std::is_final<T>::value>
class TupleElt;

template <unsigned Height, typename T>
class TupleElt<Height, T, false>
{
	T value;

public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : value( std::forward<U>( other ) ) {}

	T& get( ) { return value; }
	const T& get( ) const { return value; }
};

template <unsigned Height, typename T>
class TupleElt<Height, T, true> : private T
{
public:
	TupleElt( ) = default;

	template <typename U>
	TupleElt( U&& other ) : T( std::forward<U>( other ) ) {}

	T& get( ) { return *this; }
	const T& get( ) const { return *this; }
};
```
TupleElt는 final이 아닌 클래스를 상속받아 EBCO가 적용될 수 있도록 한다. 이 변경 점으로 이전 프로그램은 다음과 같이 출력 된다.
```c++
A()
A()
B()
2 bytes // g++에서의 결과 vs 2015에서는 여전히 1byte 붙어 3
```
### 상수 시간 get()
get() 연산은 매우 일반적인 Tuple연산이다. 하지만 재귀구현된 get()은 선형 횟수의 템플릿 인스턴스화가 필요하여 컴파일 시간에 영향을 줄 수 있다. 다행히 EBCO 최적화를 get을 좀 더 효율적으로 구현할 수 있다.

템플릿 인자 추론이 파라미터를 인자에 일치시킬 때 기본 클래스를 위한 템플릿 인자를 추론한다는 것이 핵심이다. 따라서 추출하고자 하는 요소의 높이 H를 계산할 수 있다면 전체 인덱스를 순회하지 않고 요소를 추출하기 위해서 Tuple 특수화에서 TupleElt<H, T>로 변환할 수 있다.
```c++
// TupleOptimizeFinal.h
template <unsigned H, typename T>
T& getHeight( TupleElt<H, T>& te )
{
	return te.get( );
}

template <unsigned I, typename... Elements>
auto get( Tuple<Elements...>& t )
{
	return getHeight<sizeof...(Elements)-I - 1>( t );
}
```
get\<I>(t)는 원하는 요소의 인덱스 I를 받는다. Tuple의 실제 저장공간은 높이 H에 존재하기 때문에 I를 통해 H를 계산하고 getHeight() 호출에 대한 템플릿 인자 추론이 실제 탐색을 수행한다.

높이 H는 호출에서 명시적으로 제공되므로 고정되어 있다. 따라서 T가 추론되는 과정에서 하나의 TupleElt 기본 클래스가 일치 할 것이다.

주목할 것은 getHeight() 함수가 Tuple의 private 기본 클래스에 접근하기 위해서 friend 선언되야 한다는 점이다.
```c++
// TupleOptimizeFinal.h
template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private TupleElt<sizeof...( Tail ), Head>, private Tuple<Tail...>
{
public:
	// ...
	template<unsigned I, typename... Elements> friend auto get( Tuple<Elements...>& t );
};
```
이 구현은 일정한 수의 템플릿 인스턴스화만 필요하며 컴파일러 추론 엔진이 인덱스를 맞춰보는 작업의 부담을 덜어준다.
## Tuple 첨자 연산
원칙적으로 [] 연산자를 정의하여 요소에 액세스할 수도 있다. 하지만 Tuple의 요소는 각각 다른 자료형을 가지고 있을 수 있으므로 Tuple의 [] 연산자는 템플릿이여야 한다.

CTValue 클래스 템플릿은 자료형과 함께 숫자 인덱스를 인코딩하는 것을 가능하게 한다. CTValue를 사용하여 Tuple의 멤버의 첨자 연산을 정의할 수 있다.
```c++
// Tuple.h
template <typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
	// ...
public:
	// ...
	template <typename T, T Index>
	auto& operator[]( CTValue<T, Index> )
	{
		return get<Index>( *this );
	}
};
```
이제 Tuple 클래스를 다음과 같이 사용할 수 있다.
```c++
// 06_T.cpp
auto t = makeTuple( 0, '1', 2.2f, std::string( "hello" ) );

auto a = t[CTValue<unsigned, 2>{}];
auto b = t[CTValue<unsigned, 3>{}];
```
편리한 사용을 위해서 일반 리터럴에서 직접 컴파일 타임 숫자 리터럴을 계산하기 위한 리터럴 연산자를 constexpr를 사용하여 구현할 수 있다.
```c++
// TupleLiterals.h
#include "../23_Typelist/ctvalue.h"
#include <cassert>
#include <cstddef>

constexpr int toInt( char c )
{
	if ( c >= 'A' && c <= 'F' )
	{
		return static_cast<int>( c ) - static_cast<int>( 'A' ) + 10;
	}
	if ( c >= 'a' && c <= 'f' )
	{
		return static_cast<int>( c ) - static_cast<int>( 'a' ) + 10;
	}

	assert( c >= '0' && c <= '9' );
	return static_cast<int>( c ) - static_cast<int>( '0' );
}

template <std::size_t N>
constexpr int parseInt( const char( &arr )[N] )
{
	int base = 10;
	int offset = 0;
	if ( N > 2 && arr[0] == '0' )
	{
		switch ( arr[1] )
		{
		case 'x':
		case 'X':
			base = 16;
			offset = 2;
			break;
		case 'b':
		case 'B':
			base = 2;
			offset = 2;
			break;
		default:
			base = 8;
			offset = 1;
			break;
		}
	}

	int value = 0;
	int multiplier = 1;
	for ( std::size_t i = 0; i < N - offset; ++i )
	{
		if ( arr[N - 1 - i] != '\'' )
		{
			value += toInt( arr[N - 1 - i] ) * multiplier;
			multiplier *= base;
		}
	}

	return value;
}

template <char... cs>
constexpr auto operator"" _c( )
{
	return CTValue<int, parseInt<sizeof...( cs )>( { cs... } ) > {};
}
```
리터럴의 각 문자를 자신의 템플릿 파라미터로 추론하는 리터럴 연산자를 사용하였다.
> 리터럴 연산자가 템플릿을 경우 반드시 파라미터 리스트는 비어 있어야 하고 템플릿 파라미터는 반드시 char형의 자료형이 아닌 템플릿 단 하나여야 한다. [참고 사이트](http://en.cppreference.com/w/cpp/language/user_literal)

constexpr 함수인 parseInt()는 컴파일 타임에 문자 나열을 계산하여 CTValue를 생성한다. 예를 들면 42_c는 CTValue\<int\, 42>가 된다. 16진수 2진수 리터럴도 지원한다.

1. 0x815_c =\> CTValue\<int, 2069\>
2. 0b1111\'1111_c =\> CTvalue\<int, 255\>

리터럴 연산자를 사용하여 Tuple을 다음과 같이 사용할 수 있다.
``` c++
// 06_T.cpp
auto t = makeTuple(0, ’1’, 2.2f, std::string{"hello"});
auto c = t[2_c];
auto d = t[3_c];
```