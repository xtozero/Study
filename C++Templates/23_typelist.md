# typelist
typelist는 이름이 나타내는 대로 데이터형을 담고 있는 리스트이다. 메타 프로그램은 이런 데이터형의 리스트를 조작하여 실행 가능한 프로그램의 일부로 만든다.

typelist는 리스트와 관련된 연산을 제공하는데 요소의 순회, 추가, 삭제 등을 제공한다.

하지만 typelist는 실행 시간 자료구조와는 다르게 수정할 수 없다. std::list에 요소를 추가하는 것은 리스트 그 자체를 바꾼다. 하지만 typelist에 요소를 추가하는 것은 원본 typelist를 수정하는 것이 아니라 새로운 typelist를 생성하는 것이다.

typelist는 일반적으로 데이터형 리스트의 내용, 즉 포함하고 있는 데이터형과 그 순서를 템플릿 인수 내에서 인코딩한 클래스 템플릿 특수화를 통해서 구현된다.

typelist를 구현하는 직접적인 방법은 요소를 파라미터 팩으로 인코딩하는 것이다.
```c++
// Typelist.h
template <typename... Elements>
class Typelist
{
};
```
typelist의 요소는 템플릿 인자로 직접 작성된다. 예를 들면 빈 typelist는 Typelist\<\>, int만을 담고 있다면 Typelist\<int\> 와 같은 식이다.

이런 typelist를 다루려면 typelist를 부분으로 나눠야 한다. 일반적으로 리스트의 첫 번째 요소를 나머지 부분에서 분리한다. 예를 들어 Front 메타 함수는 첫 번째 요소를 typelist에서 추출한다.
```c++
// Typelist.h
template <typename List>
class FrontT;

template <typename Head, typename... Tail>
class FrontT<Typelist<Head, Tail...>>
{
public:
	using Type = Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;
```
유사하게 PopFront 메타 함수는 typelist를 Head와 Tail로 나누고 Tail로부터 새로운 Typelist를 특수화하여 typelist에서 첫 번째 요소를 제거한다.
```c++
// Typelist.h
template <typename List>
class PopFrontT;

template <typename Head, typename... Tail>
class PopFrontT<Typelist<Head, Tail...>>
{
public:
	using Type = Typelist<Tail...>;
};

template <typename List>
using PopFront = typename PopFrontT<List>::Type;
```
또한 존재하는 모든 기존 요소를 템플릿 매개 변수 팩으로 캡처 한 다음 새로운 Typelist를 만드는 것으로 typelist의 앞에 요소를 추가할 수 있다.
```c++
// Typelist.h
template <typename List, typename NewElement>
class PushFrontT;

template <typename... Elements, typename NewElement>
class PushFrontT<Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist<NewElement, Elements...>;
};

template <typename List, typename NewElements>
using PushFront = typename PushFrontT<List, NewElements>::Type;
```
## typelist 알고리즘
기본적인 연산인 Front, PopFront, PushFront를 조합하여 좀 더 흥미로운 조작을 할 수 있다. PushFront와 PopFront를 조합하여 첫 번째 요소를 교체할 수 있다.
```c++
// 01_TL.cpp
using NewType = PushFront<PopFront<SignedIntegralTypes>, bool>;
```
더 나아가 typelist에 작동하는 템플릿 메타 함수를 통해서 검색과 같은 알고리즘을 구현할 수 있다.

## Indexing
typelist에 대한 가장 기본적인 연산은 특정 요소를 리스트에서 추출하는 것이다.
```c++
// 01_TL.cpp
using TL = NthElement<Typelist<short, int, long>, 2>;
```
이 때 TL은 long 의 별칭이 된다.

NthElement 연산은 필요로 하는 요소를 찾을 때까지 Typelist를 순회하는 재귀 메타 프로그램을 통해 구현된다.
```c++
// Typelist.h
template <typename List, unsigned int N>
class NthElementT : public NthElementT<PopFront<List>, N - 1>
{
};

template <typename List>
class NthElementT<List, 0> : public FrontT<List>
{
};

template <typename List, unsigned int N>
using NthElement = typename NthElementT<List, N>::Type;
```

## 최적 탐색
typelist를 검색하는 여러 알고리즘이 존재하는데 예를 들자면 typelist에서 가장 큰 데이터형을 탐색할 수도 있다.

이것도 마찬가지로 재귀를 통해 구현된다.
```c++
// Typelist.h
template <typename List>
class LargestTypeT;

template <typename List>
class LargestTypeT
{
private:
	using First = Front<List>;
	using Rest = typename LargestTypeT<PopFront<List>>::Type;

public:
	using Type = typename std::conditional<sizeof( First ) >= sizeof( Rest ), First, Rest>::type;
};

template <>
class LargestTypeT<Typelist<>>
{
public:
	using Type = char;
};

template <typename List>
using LargestType = typename LargestTypeT<List>::Type;
```
재귀는 typelist가 비었을 때 종료된다. 기저 클래스에서 빈 typelist를 명시적으로 언급( Typelist\<\> )하는 것을 주목하자. 이것은 다른 형태의 사용을 배제하기 때문에 다소 아쉬운데 IsEmpty 메타 함수를 통해서 이를 개선할 수 있다.
```c++
// Typelist.h
template <typename List>
class IsEmpty
{
public:
	static constexpr bool value = false;
};

template <>
class IsEmpty<Typelist<>>
{
public:
	static constexpr bool value = true;
};
```
IsEmpty를 사용하면 LargestType을 Front, PopFront, IsEmpty를 구현한 어떤 typelist에도 잘 동작하도록 구현할 수 있다.
```c++
// Typelist.h
template <typename List, bool Empty = IsEmpty<List>::value>
class LargestTypeT;

template <typename List>
class LargestTypeT<List, false>
{
private:
	using Contender = Front<List>;
	using Best = typename LargestTypeT<PopFront<List>>::Type;
public:
	using Type = typename std::conditional<sizeof( Contender ) >= sizeof( Best ), Contender, Best>::type;
};

template <typename List>
class LargestTypeT<List, true>
{
public:
	using Type = char;
};

template <typename List>
using LargestType = typename LargestTypeT<List>::Type;
```
두 번째 템플릿 파라미터 Empty는 리스트가 비었는지 확인하고 비어있지 않으면 재귀로 탐색을 계속하고 비어있다면 재귀를 끝내도록 한다.

## typelist에 추가하기
PushFront는 새로운 요소를 리스트 앞에 추가할 수 있게 한다.

typelist를 사용하다 보면 std::list나 std:::vector처럼 요소를 앞이 아니라 뒤에 추가하고자 할 때도 있다.

여기서 구현한 Typelist 템플릿은 이 연산을 PushFront의 구현을 조금 바꾸는 것으로 구현할 수 있다.
```c++
// Typelist.h
template <typename List, typename NewElement>
class PushBackT;

template <typename... Elements, typename NewElement>
class PushBackT<Typelist<Elements...>, NewElement>
{
public:
	using Type = Typelist<Elements..., NewElement>;
};

template <typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;
```
하지만 LargestType과 같이 기본적인 Front, PushFront, PopFront, IsEmpty 연산을 사용해서 일반적인 알고리즘으로 구현할 수도 있다.
```c++
// Typelist.h
template <typename List, typename NewElement, bool = IsEmpty<List>::value>
class PushBackRecT;

template <typename List, typename NewElement>
class PushBackRecT<List, NewElement, false>
{
private:
	using Head = Front<List>;
	using Tail = PopFront<List>;
	using NewTail = typename PushBackRecT<Tail, NewElement>::Type;

public:
	using Type = PushFront<NewTail, Head>;
};

template <typename List, typename NewElement>
class PushBackRecT<List, NewElement, true>
{
public:
	using Type = PushFront<List, NewElement>;
};

template <typename List, typename NewElement>
class PushBackT : public PushBackRecT<List, NewElement> {};

template <typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;
```
재귀로 이해하기 어려울 수 있는데 간단한 예로 재귀를 풀어보자
```c++
PushBack<Typelist<char, short>, int>;
```
먼저 처음 재귀 단계에서 Head는 char가 Tail은 Typelist\<short\>가 되고 NewTail은 다음과 같다.
```c++
PushBackRecT<Typelist<short>, int>
```
Head는 short Tail은 빈 typelist, Typelist\<\>가 된다. 여기서 NewTail은 다음과 같다.
```c++
PushBackRecT<Typelist<>, int>
```
typelist가 비었으므로 기저 조건에 도달하게 되어 재귀가 풀리게 된다.

int를 빈 typelist의 앞에 추가하여 Typelist\<int\>가 되고 이전 재귀 단계의 HEAD를 차례대로 앞에 추가하게 된다.
```c++
PushFront<short, Typelist<int>>
// 이전 재귀 단계
PushFront<char, Typelist<short, int>>
```
최종적으로 Typelist\<char, short, int\>를 얻을 수 있다.

지금 개발한 알고리즘은 평가되는데 선형 횟수( linear number of template instantiaitions ) 만큼의 인스턴스화가 필요하다. typelist의 길이가 N이면 N + 1번의 PushBackRecT, PushFrontT 인스턴스화와 N 번의 FrontT, PopFrontT 인스턴스화가 진행된다.

템플릿 인스턴스 횟수를 세는 것으로 특정 메타프로그램의 컴파일 시간을 대략 추정할 수 있다.

컴파일 시간은 큰 메타프로그램에서 문제가 될 수 있다. 따라서 인스턴스화 횟수를 줄이려고 노력하는 것은 합당하다.

PushBackT의 부분 특수화로 구현한 첫 번째 PushBack의 경우 상수 횟수의 인스턴스화만 이뤄지기 때문에 두 번째 방법보다 훨씬 효율적이며 알고리즘 특수화( algorithm specialization )로 인해서 Typelist\<\>형 일 경우 자동으로 선택됩니다.

## typelist 뒤집기
typelist는 요소 간 어떤 순서를 가지고 있는데 때때로 어떤 알고리즘에서는 그 순서를 뒤집으면 편리하다.
```c++
// Typelist.h
template <typename List, bool = IsEmpty<List>::value>
class ReverseT;

template <typename List>
using Reverse = typename ReverseT<List>::Type;

template <typename List>
class ReverseT<List, false> : public PushBack<Reverse<PopFront<List>>, Front<List>> { };

template <typename List>
class ReverseT<List, true>
{
public:
	using Type = List;
};
```
기저의 경우 빈 typelist를 반환한다. 재귀인 경우는 첫 번째 요소와 나머지 리스트로 나누어 나머지 리스트를 뒤집고 첫 번째 요소를 뒤에 붙인다.

Reverse 알고리즘은 typelist에서 마지막 요소를 제거하는 PopBackT를 구현하는 데도 사용할 수 있다.
```c++
// Typelist.h
template <typename List>
class PopBackT
{
public:
	using Type = Reverse<PopFront<Reverse<List>>>;
};

template <typename List>
using PopBack = typename PopBackT<List>::Type;
```
이 알고리즘은 typelist를 뒤집고 첫 번째 요소를 제거한 다음 다시 뒤집는 것을 통해서 마지막 요소를 제거한다.

## typelist 변환
이전까지의 typelist 알고리즘은 typelist에서 요소를 추출하거나, 검색하고, 새로운 리스트를 만들고 뒤집는 것을 가능하게 했다.

하지만 아직 typelist의 모든 요소를 어떤 방법으로 변환하는 연산은 다루지 않았다.

typelist의 모든 데이터형에 AddConst 메타 함수를 사용해서 const 한정자를 추가하는 예제를 살펴보자
```c++
// Typelist.h
template <typename T>
struct AddConstT
{
	using Type = const T;
};

template <typename T>
using AddConst = typename AddConstT<T>::Type;
```
최종적으로 Transform 알고리즘을 구현하여 typelist와 메타 함수를 받아 각 요소에 메타 함수를 적용한 새로운 typelist를 만들도록 할 것이다. 예를 들면 Transform\<SignedIntegralTypes, AddConstT\> 는 Typelist\<const signed int, const short, const int, const long, const long long\> 을 만들게 된다.

메타 함수는 템플릿 템플릿 파라미터로 제공되며 Transform 알고리즘 자체는 우리가 예상하듯이 재귀 알고리즘으로 구현된다.
```c++
// Typelist.h
template <typename List, template <typename T> class MetaFun, bool = IsEmpty<List>::value>
class TransformT;

template <typename List, template <typename T> class MetaFun>
class TransformT<List, MetaFun, false> : public PushFrontT<typename TransformT<PopFront<List>, MetaFun>::Type, 
										typename MetaFun<Front<List>>::Type> { };

template <typename List, template <typename T> class MetaFun>
class TransformT<List, MetaFun, true>
{
public:
	using Type = List;
};

template <typename List, template <typename T> class MetaFun>
using Transform = typename TransformT<List, MetaFun>::Type;
```
재귀의 경우 문법적으로 어려워 보이지만 직관적이다. 첫 번째 요소를 변환한 결과를 재귀를 통해서 나온 나머지 요소의 결과 앞에 추가하여 새로운 typelist를 생성한다.

## typelist 축적
Transform은 각 요소를 변환하는데 유용한 알고리즘이며 종종 축적(모든 요소를 하나의 결과 값으로 합치는 것)과 함께 사용된다.

Accumulate 알고리즘은 typelist T와 초기 데이터형 I 그리고 메타 함수 F를 받아 F(F(F(...F(I, T1), T2), ..., TN-1), TN) 의 결과를 반환한다.

typelist, F의 선택, 초기 데이터형 I에 따라서 Accumulate 가 다른 결과를 반환하도록 할 수 있다. 예를 들어 F 가 두 데이터형중 가장 큰 데이터형을 반환하게 된다면 Accumulate는 LargestType알고리즘과 같이 동작한다. 한편 F가 typelist와 데이터형을 받아 typelist의 뒤에 추가한다면 Reverse와 같이 동작한다.

Accumulate은 표준적인 재귀 메타 프로그램으로 구현된다.
```c++
// Typelist.h
template <typename List, template <typename X, typename Y> class F, typename I, bool = IsEmpty<List>::value>
class AccumulateT;

template <typename List, template <typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, false> : public AccumulateT<PopFront<List>, F, typename F<I, Front<List>>::Type>
{};

template <typename List, template <typename X, typename Y> class F, typename I>
class AccumulateT<List, F, I, true>
{
public:
	using Type = I;
};

template <typename List, template <typename X, typename Y> class F, typename I>
using Accumulate = typename AccumulateT<List, F, I>::Type;
```
기저의 경우 초기 데이터형 I를 반환한다. 재귀의 경우 메타 함수 F를 이전 결과 I와 typelist의 첫 번째 요소에 적용하고 결과를 새로운 초기 데이터형으로 하여 나머지 리스트에 전달한다.

Accumulate를 사용해서 Reverse 알고리즘을 다음과 같이 사용할 수 있다.
```c++
using AC_RT = Accumulate<SignedIntegralTypes, PushFrontT, Typelist<>>;
```
Accumulate를 사용한 LargestType의 구현도 살펴보자
```c++
// Typelist.h
template <typename T, typename U>
class LargerTypeT 
{
public:
	using Type = typename std::conditional<sizeof( T ) >= sizeof( U ), T, U>::type;
};

template <typename TypeList>
class LargestTypeAccT : public AccumulateT<PopFront<TypeList>, LargerTypeT, Front<TypeList>> {};

template <typename TypeList>
using LargesetTypeAcc = typename LargestTypeAccT<TypeList>::Type;
```
LargestType의 이런 구현은 비어있지 않은 typelist를 요구하는 것에 주목하자.

char나 void 같은 판별 유형을 반환하거나 알고리즘 자체를 SFINAE 친화적으로 구현하여 비어있는 typelist를 명시적으로 처리할 수 있다.
```c++
template <typename TypeList>
class LargestTypeAccT<TypeList, false> : public AccumulateT<PopFront<TypeList>, LargerTypeT, Front<TypeList>> {};

template <typename TypeList>
class LargestTypeAccT<TypeList, true> {};

template <typename TypeList>
using LargesetTypeAcc = typename LargestTypeAccT<TypeList>::Type;
```
Accumulate는 다양한 연산을 표현할 수 있게 해주는 매우 강력한 알고리즘이다. 따라서 typelist를 조작하기 위한 기본적인 알고리즘으로 고려할 만하다.

## 삽입 정렬
마지막 typelist 알고리즘으로 삽입 정렬을 구현해 보고자 한다. 다른 알고리즘과 마찬가지로 재귀 단계에서 첫 번째 요소(Head)와 나머지 요소(Tail)로 나누고 나머지 요소를 정렬한 다음 첫 번째 요소를 알맞은 자리에 위치시킨다.
```c++
template <typename List, template <typename T, typename U> class Compare, bool = IsEmpty<List>::value>
class InsertionSortT;

template <typename List, template <typename T, typename U> class Compare>
class InsertionSortT<List, Compare, false> : public InsertionSortedT<typename InsertionSortT<PopFront<List>, Compare>::Type, Front<List>, Compare>
{};

template <typename List, template <typename T, typename U> class Compare>
class InsertionSortT<List, Compare, true>
{
public:
	using Type = List;
};

template <typename List, template <typename T, typename U> class Compare>
using InsertionSort = typename InsertionSortT<List, Compare>::Type;
```
삽입 정렬의 핵심은 InsertionSortedT 메타 함수이다. InsertionSortedT 메타 함수는 이미 정렬된 리스트의 알맞은 위치에 새로운 요소를 삽입한다.
```c++
template <typename List, typename Element, template <typename T, typename U> class Compare, bool = IsEmpty<List>::value>
class InsertionSortedT;

template <typename List, typename Element, template <typename T, typename U> class Compare>
class InsertionSortedT<List, Element, Compare, false>
{
private:
	using NewHead = typename std::conditional<Compare<Element, Front<List>>::value, Element, Front<List>>::type;
	using NewTail = typename std::conditional<Compare<Element, Front<List>>::value, List, typename InsertionSortedT<PopFront<List>, Element, Compare>::Type>::type;
public:
	using Type = PushFront<NewTail, NewHead>;
};

template <typename List, typename Element, template <typename T, typename U> class Compare>
class InsertionSortedT<List, Element, Compare, true> : public PushFrontT<List, Element> {};
```
기저의 경우 요소가 하나인 리스트는 항상 정렬되어 있으므로 명백하다. 재귀의 경우 정렬된 리스트 보다 삽입할 요소가 비교 결과 앞에 나와야 한다면 PushFront로 앞에 추가하고 그렇지 않다면 정렬된 리스트에서 첫 번째 요소를 제외하고 나머지 요소들에서 알맞은 위치를 찾아 삽입되도록 한다.

이 구현은 사용하지 않는 데이터형을 인스턴스화하지 않도록 컴파일 시간 최적화를 적용하였다.

다음과 같은 구현도 기술적으로는 같다.
```c++
template <typename List, typename Element,
template <typename T, typename U> class Compare>
class InsertSortedT<List, Element, Compare, false>
: public std::conditional<Compare<Element, Front<List>>::value,
PushFront<List, Element>,
PushFront<InsertSorted<PopFront<List>,
Element, Compare>,
Front<List>>>
{};
```
하지만 conditional 의 템플릿 인자가 둘 다 인스턴스화 되기 때문에 불필요한 인스턴스화가 이뤄진다.

우리가 구현한 최적화된 버전에서는 클래스 템플릿에 대한 별칭 선언이 해당 인스턴스의 몸체를 인스턴스화 하지 않는 것을 이용하여 불필요한 인스턴스화를 제거하였다.

## 데이터형이 아닌 typelist
typelist는 풍부한 알고리즘과 연산을 제공하여 데이터형들의 순서를 묘사하고 다룰 수 있도록 하였다.

때때로 컴파일 시간 값의 나열(sequence of compile-time values)을 사용할 수 있는 것은 유용한데 다중 차원의 배열이나 다른 typelist의 인덱스로 사용할 수 있다.

컴파일 시간 값의 typelist를 제공하는 데는 몇 가지 방법이 있는데 간단한 접근방법은 typelist와 함께 특정 유형의 값을 나타내는 CTValue 클래스 템플릿을 정의하는 것이다.
```c++
// ctvalue.h
template <typename T, T Value>
struct CTValue
{
	static constexpr T value = Value;
};
```
CTValue를 템플릿을 사용하면 다음과 같이 소수를 담은 typelist를 표현할 수 있다.
```c++
// 02_TL.cpp
using Primes = Typelist<CTValue<int, 2>, CTValue<int, 3>, CTValue<int, 5>, CTValue<int, 7>, CTValue<int, 11>>;
```
이런 표현과 함께 우리는 소수들의 곱을 계산하는 등, typelist의 값에 대해 수치 계산을 수행할 수 있다.

MultiplyT 템플릿은 같은 데이터형의 두 컴파일 시간 값을 곱해 새로운 컴파일 시간 값을 제공한다.
```c++
// ctvalue.h
template <typename T, typename U>
struct MultiplyT;

template <typename T, T Value1, T Value2>
struct MultiplyT<CTValue<T, Value1>, CTValue<T, Value2>>
{
public:
	using Type = CTValue<T, Value1 * Value2>;
};

template <typename T, typename U>
using Multiply = typename MultiplyT<T, U>::Type;
```
그럼 MultiplyT를 사용해서 다음과 같은 표현으로 모든 소수의 곱을 구할 수 있다.
```c++
// 02_TL.cpp
Accumulate<Primes, MultiplyT, CTValue<int, 1>>::value;
```
Typelist와 CTValue의 사용은 다소 장황한데 같은 데이터형의 값의 리스트를 받는 CTTypelist 템플릿 별칭을 통해서 이를 개선할 수 있다.
```c++
// ctvalue.h
template <typename T, T... Values>
using CTTypelist = Typelist<CTValue<T, Values>...>;
```
이제 우리는 CTTypelist를 사용해서 Primes를 아래와 같이 작성할 수 있다.
```c++
using Primes = CTTypelist<int, 2, 3, 5, 7, 11>;
```
이런 접근법은 단지 별칭일 뿐이기에 에러 메시지에서는 CTValueType들의 Typelist로 다뤄지고 장황해진다. 이 문제를 해결하기 위해서 직접 값을 저장하는 완전히 새로운 typelist 클래스 Valuelist를 작성할 수 있다.
```c++
// valuelist.h
template <typename T, T... Values>
struct Valuelist
{
};

template <typename T, T... Values>
struct IsEmpty<Valuelist<T, Values...>>
{
	static constexpr bool value = sizeof...( Values ) == 0;
};

template <typename T, T Head, T... Tail>
struct FrontT<Valuelist<T, Head, Tail...>>
{
	using Type = CTValue<T, Head>;
	static constexpr T Value = Head;
};

template <typename T, T Head, T... Tail>
struct PopFrontT<Valuelist<T, Head, Tail...>>
{
	using Type = Valuelist<T, Tail...>;
};

template <typename T, T... Values, T New>
struct PushFrontT<Valuelist<T, Values...>, CTValue<T, New>>
{
	using Type = Valuelist<T, New, Values...>;
};

template <typename T, T... Values, T New>
struct PushBackT<ValueList<T, Valuelist...>, CTValue<T, New>>
{
	using Type = Valuelist<T, Valuelist..., New>;
};
```
IsEmpty, FrontT, PopFrontT, PushFrontT를 제공하여 Valuelist를 여기서 제작한 알고리즘과 함께 사용할 수 있도록 하였다. 예를 들면 ValueList는 InsertionSort 알고리즘과 같이 사용될 수 있다.
```c++
using Integers = Valuelist<int, 6, 2, 4, 9, 5, 2, 1, 7>;

using SortedIntegers = InsertionSort<Integers, GreaterThanT>;

static_assert( std::is_same<SortedIntegers, Valuelist<int, 9, 7, 6, 5, 4, 2, 2, 1>>::value, "inserttion sort failed" );
```

## 추론 가능한 데이터형이 아닌 파라미터
C++17에서 CTValue는 추론 가능한 데이터형이 아닌 파라미터로 개선될 수 있다.
> 데이터형이 아닌 파라미터에 대한 auto 선언이 C++17 부터 가능하기 때문이다.
```c++
// ctvalue17.h
template <auto Value>
struct CTValue
{
    static constexpr auto value = Value;
}
```
이렇게 하면 CTValue를 사용할 때마다 데이터형을 지정하지 않아도되 사용하기 쉽다.
```c++
using Primes = Typelist<CTValue<2>, CTValue<3>, CTValue<5>, CTValue<7>, CTValue<11>>;
```
C++17 ValueList에도 이와 같은 작업을 할 수 있지만 반드시 필요하지는 않다. 추론 가능한 데이터형이 아닌 파라미터 팩은 각 인자의 데이터형이 다를 수 있다.
```c++
// ctvalue17.h
template <auto... Values>
class Valuelist {};
```

## 팩 확장을 통한 알고리즘 최적화
팩 확장은 컴파일러가 typelist에 수행하는 반복 작업을 없애는 유용한 기능이다. Transform 알고리즘을 팩 확장을 사용하여 자연스럽게 유도할 수 있다.
```c++
// typelist.h
template <typename... Elements, template<typename T> class MetaFun>
class TransformT<Typelist<Elements...>, MetaFun, false>
{
public:
	using Type = Typelist<typename MetaFun<Elements>::Type...>;
};
```
이 구현은 typelist 의 요소를 파라미터 팩 Elements로 캡처한 다음 typename MetaFun\<Elements\>::Type 패턴과 함께 각 요소에 메타 함수를 적용하기 위해 팩 확장을 사용한다.

이 구현은 재귀를 사용하지 않고 언어 기능을 직관적으로 사용하기 때문에 매우 간단하다. 또한 Transform 템플릿의 한 인스턴스만 인스턴스화되기 때문에 더 적은 템플릿 인스턴스가 요구된다.
> 물론 선형 횟수 만큼의 MetaFun 인스턴스가 필요하지만 이런 인스턴스는 알고리즘은 근간이다.

다른 알고리즘도 팩 확장을 사용하여 간접적인 이익을 얻는다. 예를 들면 Reverse 알고리즘은 선형 횟수의 PushBack 인스턴스가 필요하다. 팩 확장을 사용하면 여전히 선형적이지만 효율적이다. 
> 일반적인 재귀 구현은 그 자체(ReverseT)가 인스턴스화 되기 때문에 Reverse 알고리즘을 이차원적으로 만들게 된다.

팩 확장은 새로운 typelist를 생성하기 위해서 제공된 인덱스에서 요소를 선택하는 데도 유용하게 사용될 수 있다.

Select 메타 함수는 typelist와 인덱스를 담은 ValueList를 받아 ValueList에 의해 정해진 요소만을 담은 새로운 typelist를 생성한다.
```c++
// valuelist.h
template <typename Types, typename Indices>
class SelectT;

template <typename Types, unsigned... Indicies>
class SelectT<Types, Valuelist<unsigned, Indicies...>>
{
public:
	using Type = Typelist<NthElement<Types, Indicies>...>;
};

template <typename Types, typename Indicies>
using Select = typename SelectT<Types, Indices>::Type;
```
인덱스는 파라미터 팩 Indices로 캡처되고 주어진 typelist에서 NthElement 타입의 시퀀스를 생성한다. Select 를 사용하면 typelist를 뒤집는 것도 가능하다.
```c++
// TL_02.cpp
using SignedIntegralTypes = Typelist<signed char, short, int, long, long long>;

using ReversedSignedIntegerTypes = Select<SignedIntegralTypes, Valuelist<unsigned, 4, 3, 2, 1, 0>>;
std::cout << typeid(ReversedSignedIntegerTypes).name() << std::endl;
```
다른 리스트에 대한 자료형이 아닌 인덱스를 담고 있는 리스트를 인덱스 리스트( index list ), 인덱스 시퀀스( index sequence )라고 하고 재귀를 간략하게 하거나 제거할 수 있게 해준다.
> C++11 표준에서 index_sequnce로 사용할 수 있다.

## Cons 스타일 typelist
가변 템플릿이 도입되기 전에 typelist는 일반적으로 LISP의 cons cell을 모델로 하여 재귀적 데이터 구조로 공식화되었다.

각 cons cell은 값과 다른 cons cell이나 빈 리스트 nill인 중첩 리스트를 담고 있다. 이 개념은 C++로 직접 표현할 수 있다.
```c++
// cons.h
class Nil {};

template <typename HeadT, typename TailT = Nil>
class Cons
{
public:
	using Head = HeadT;
	using Tail = TailT;
};
```
빈 typelist는 Nil로 쓰인다. 단일 요소를 가진 리스트는 Cons\<int, Nil\> 혹은 Cons\<int\> 가 되며 긴 리스트는 중첩이 요구된다.
```c++
// 03_TL.cpp
using TwoShort = Cons<short, Cons<unsigned short>>;
```
임의의 긴 리스트는 중첩을 통해서 생성될 수 있지만 긴 목록을 손으로 작성하는 것은 다소 다루기 힘들어질 수 있다.

Cons 스타일의 typelist에서 첫 번째 요소를 추출하는 것은 리스트의 Head를 직접 참조하면 된다.
```c++
// cons.h
template <typename List>
class FrontT
{
public:
	using Type = typename List::Head;
};

template <typename List>
using Front = typename FrontT<List>::Type;
```
리스트의 앞에 새로운 요소를 추가하는 것은 또 다른 Cons로 기존 리스트를 감싸면 된다.
```c++
template <typename List, typename Element>
class PushFrontT
{
public:
	using Type = Cons<Element, List>;
};

template <typename List, typename Element>
using PushFront = typename PushFrontT<List, Element>::Type;
```
첫 번째 요소를 제거하는 것은 중첩 typelist에서 Tail을 추출하면 된다.
```c++
template <typename List>
class PopFrontT
{
public:
	using Type = typename List::Tail;
};

template <typename List>
using PopFront = typename PopFrontT<List>::Type;
```
Nil을 위한 IsEmpty 특수화로 typelist의 주요 연산 모음이 완료된다.
```c++
template <typename List>
struct IsEmpty
{
	static constexpr bool value = false;
};

template <>
struct IsEmpty<Nil>
{
	static constexpr bool value = true;
};
```
이 typelist 연산과 함께 InsertionSort 알고리즘을 cons 스타일 리스트와 함께 사용할 수 있다.
```c++
using ConsList = Cons<int, Cons<char, Cons<short, Cons<double>>>>;
using SortedType = InsertionSort<ConsList, SmallerThanT>;
using Expected = Cons<char, Cons<short, Cons<int, Cons<double>>>>;

std::cout << ( std::is_same<SortedType, Expected>::value ? "is same" : "is not same" ) << std::endl;
```
InsertionSort와 같이 cons 스타일 typelist는 가변 typelist와 동등한 표현을 할 수 있다. 그러나 몇 가지 단점이 있어 가변 버전을 사용하도록 유도한다.
1. 중첩된 긴 cons 스타일 typelist는 쓰기도 어렵고 읽기도 어렵다.
2. 가변 버전으로 작성된 몇몇 알고리즘은 더 효율적이다.
3. 가변 버전의 typelist가 이종의(heterogeneous) 컨테이너와 함께 사용할 때 더 적합하다.