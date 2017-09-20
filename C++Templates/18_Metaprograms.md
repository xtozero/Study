# 메타프로그래밍
## 개요
- 메타프로그래밍(metaprogramming)은 프로그램을 프로그래밍하는 것이다. 즉 실제로 원하는 기능을 구현하는 새로운 코드를 만들어내는 프로그래밍 시스템을 작성하는 것이다.
- 메타프로그래밍은 적은 노력으로 더 많은 기능을 구현하기 위한 목적으로 사용되며 여기서 노력이란 코드 크기, 유지 비용 등을 일컫는다.
- 메타프로그래밍의 특징은 성능이나 인터페이스의 단순성과 같은 이점을 얻기 위해 일부 사용자 정의 계산이 번역 시간에 일어난다는 점이다.

## 메타프로그램의 첫 번째 예
- 메타프로그래밍의 세부 사항을 살펴보기 전에 간단한 예제를 하나 살펴보자
- 다음 프로그램은 컴파일 시작에 특정 값을 주어진 값만큼 제곱하는 과정을 보여준다.
```c++
// META_01.cpp

template <int X, int N>
class Pow
{
public:
	constexpr static int result = X * Pow<X, N - 1>::result;
};

template <int X>
class Pow<X, 0>
{
public:
	constexpr static int result = 1;
};
```
- 재귀적 템플릿 인스턴스화가 템플릿 메타프로그래밍의 핵심이다. 이번 예제에서는 다음 두 법칙에 따라 반복적 템플릿 인스턴스화가 이뤄졌다.

1. X^N = X * X^N-1
2. X^0 = 1

- 첫 번째 템플릿은 일반적인 재귀 법칙을 구현하고 두 번째 템플릿은 재귀를 끝내기 위한 특수화이다.
- Pow<> 템플릿( 특수화 포함 )을 템플릿 메타프로그렘이라 부른다.

## 열거형 값과 정적 상수
- 오래된 C++ 컴파일러에서는 클래스 선언에서 열거형 값만이 진짜 상수를 가질 수 있었다. 하지만 표준화를 거치는 동안 클래스 내에서 정적 상수 초기화의 개념을 도입하였다.
```c++
// META_02.cpp

struct TrueConstants
{
	enum { Three = 3 };
	static const int Four = 4;
    static constexpr int Five = 5;  // c++11 에서 추가된 constexpr 한정자를 사용하였다.
};
```
- Four는 Three와 같이 진짜 상수이다. 다만 여기서 Four는 lvalue라는 단점이 있다. 따라서 다음과 같은 선언이 있다고 하면
```c++
// META_02.cpp

void foo( const int& )
```
- 다음과 같이 메타프로그램의 결과를 건네주려 하면 에러가 발생한다.
```c++
// META_02.cpp

foo( TrueConstants::Four );
...

1>META_02.obj : error LNK2001: unresolved external symbol "public: static int const TrueConstants::Four" (?Four@TrueConstants@@2HB)
```
- 위의 프로그램이 동작하기 위해서는 컴파일러가 TrueConstants::Four의 주소를 건네야하므로 정적 멤버의 정의를 인스턴스화하고 할당해야만 한다. 결국 순수하게 컴파일 시간에만 계산하면 되는 게 아니다.
- 한편 열거형 값과 constexpr 한정자를 사용한 경우 이들을 참조로 전달한다 해도 정적 메모리가 사용되지 않아 정상적으로 프로그램이 동작한다.

## 두 번째 예: 제곱근 구하기
- 두 번째 메타프로그램 예제로 제곱근을 구해보자.
```c++
// META_03.cpp

template <int N, int LO = 1, int HI=N>
class Sqrt
{
public:
	enum { mid = (LO+HI+1) / 2 };
	enum { result = (N<mid*mid) ? Sqrt<N, LO, mid-1>::result : Sqrt<N, mid, HI>::result };
};

template <int N, int M>
class Sqrt<N, M, M>
{
public:
	enum { result = M };
};
```
- 이진 탐색 기법을 사용하여 제곱근을 찾아가는 메타프로그램이다. 템플릿 내에서 result가 {LO, mid - 1}와 {mid, HI}의 범위 중 어디에 속하는지 계산하여 삼항 연산자를 사용해서 해당 범위에서 검색을 진행하도록 구현됐다.
- LO와 HI가 같은 M이라는 값을 가진다면 재귀 과정을 끝내기 위한 특수화를 사용해 마지막 result, M을 반환한다.
- 이 메타프로그램을 사용하는 간단한 프로그램을 살펴보자.
```c++
// META_03.cpp

std::cout << "Sqrt<16>::result = " << Sqrt<16>::result << std::endl;
std::cout << "Sqrt<25>::result = " << Sqrt<25>::result << std::endl;
std::cout << "Sqrt<42>::result = " << Sqrt<42>::result << std::endl;
std::cout << "Sqrt<1>::result = " << Sqrt<1>::result << std::endl;
```
- Sqrt\<16\>::result을 예로 알아보자. 이 표현식은 Sqrt\<16,1,16\>::result로 확장되고 다음과 같이 계산한다.
```
mid = (1+16+1)/2 = 9
result = (16<9*9) ? Sqrt<16,1,8>::result
                  : Sqrt<16,9,16>::result
       = (16<81) ? Sqrt<16,1,8>::result
                  : Sqrt<16,9,16>::result
       Sqrt<16,1,8>::result
```
- Sqrt\<16,1,8\>::result도 마찬가지로 방식으로 계산되고 마지막으로 최대, 최솟값이 같은 Sqrt\<16,4,4\>::result로 재귀가 종료되어 계산이 완료된다.
- 여기서 한 가지 중요한 점이 있는데 컴파일러가 Sqrt\<16,1,16\>::result 라는 표현식을 계산할 때 옳은 쪽뿐만이 아니라 틀린 쪽도 인스턴스화 한다. 뿐만 아니라 결과 클래스형의 멤버 :: 연산자를 사용해 접근하므로 클래스형 내의 모든 멤버도 인스턴스화 된다. 결과 엄청난 수의 인스턴스가 생성된다.
- 템플릿 인스턴스화는 대부분의 컴파일러에서 꽤 비싼 과정이다. 따라서 엄청난 수의 인스턴스가 생기지 않도록 해야 한다. 다행히 특수화를 사용하면 엄청난 수의 인스턴스가 생성되는 것을 막을 수 있다.
```c++
// META_04.cpp

#include <type_traits>

template <int N, int LO = 1, int HI = N>
class Sqrt
{
public:
	enum { mid = ( LO + HI + 1 ) / 2 };

	using SubT = typename std::conditional < N<mid*mid, Sqrt<N, LO, mid - 1>, Sqrt<N, mid, HI>>::type;

	enum { result = SubT::result };
};

template <int N, int M>
class Sqrt<N, M, M>
{
public:
	enum { result = M };
};
```
- 주목할 부분은 c++11에서 부터 추가된 type_traits 헤더에 있는 std::conditional을 사용한 부분이다.
- std::conditional 템플릿은 주어진 bool 상수값에 따라 두 데이터형 중 하나를 선택하는 장치이다. 클래스 템플릿 인스턴스에 대해 별칭을 정의하더라도 해당 인스턴스의 몸체를 인스턴스화하지 않는 점을 이용하였다. 따라서 이전과 같이 엄청난 수의 인스턴스가 생성되지 않는다.

## 유도 변수 사용
- 이전 예제에서 작성된 메타프로그램은 꽤 복잡해 보일 수 있는데 여기서는 좀 더 반복적인 제곱근을 계산하는 메타프로그래밍을 살펴보려고 한다.
```c++
// META_05.cpp

template <int N, int I = 1>
class Sqrt
{
public:
	enum { result = ( I * I < N ) ? Sqrt<N, I+1>::result : I };
};

template <int N>
class Sqrt<N, N>
{
public:
	enum { result = N };
};
```

- 위 코드는 반복적으로 I를 증가시켜나가면서 Sqrt\<N, I\>를 생성한다. I * I \< N이 참인 동안 다음 반복이 진행되고 그렇지 않으면 I가 마지막 결과가 된다.
- 여기서도 재귀를 끝내기 위한 템플릿 특수화가 필요한데 삼항연산자에 의해 양쪽이 모두 인스턴스화되는 효과 때문에 필요하다.
> **템플릿 특수화가 없다면 컴파일러의 한계에 도달할 때까지 계속 인스턴스를 생성할 것이다.**

- 여기서도 std::conditional을 사용하여 엄청난 수의 인스턴스가 생성되는 것을 방지할 수 있다.
```c++
// META_05.cpp

#include <type_traits>

template <int N>
class Value
{
public:
	enum { result = N };
};

template <int N, int I = 1>
class Sqrt
{
public:
	using SubT = typename std::conditional<( I * I < N ), Sqrt<N, I + 1>, Value<I>>::type;

	enum { result = SubT::result };
};
```

## 계산 완벽성
- 예제들을 통해서 템플릿 메타프로그램이 다음과 같은 사항을 가질 수 있음을 보여준다.

1. 상태 변수 : 템플릿 파라미터
2. 루프 생성 : 재귀를 통해서
3. 경로 선택 : 조건 표현식이나 특수화를 통해서
4. 정수 수식 계산

- 재귀 인스턴스화의 수와 허용되는 상태 변수의 수에 제한이 없다면 계산 가능한 모든 것을 메타프로그래밍을 통해 계산할 수 있을 것이다.
- 하지만 템플릿으로 모든 계산을 하는 것은 편리하지 않고 컴파일러의 자원을 매우 많이 소모한다. C++ 표준은 최소한 재귀 인스턴스화 수준을 17까지 두는 것을 추천하지만 템플릿 메타프로그램은 이런 제약을 쉽게 초과할 수 있다.
- 따라서 일반적으로 템플릿 메타프로그램은 조심스럽게 사용해야 한다.

## 재귀적 인스턴스화와 재귀적 템플릿 인자
- 재귀적 인스턴스화를 하는 경우 템플릿 인자는 재귀적이지 않게 하는 편이 좋다. 아래의 재귀 템플릿 예제를 살펴보자.
```c++
// META_06.cpp

template <typename T, typename U>
struct Doublify {};

template <int N>
struct Trouble
{
	typedef Doublify<typename Trouble<N - 1>::LongType, typename Trouble<N - 1>::LongType> LongType;
};

template <>
struct Trouble<0>
{
	typedef double LongType;
};

Trouble<10>::LongType ouch;
```
- Trouble\<10\>::LongType 는 재귀적으로 Trouble\<9\>, Trouble\<8\>, ... Trouble\<0\> 인스턴스화하고 복잡해지는 데이터형에 대해서 Doublify도 인스턴스화한다.
- *표현식 Trouble\<N\>::LongType에 대한 데이터형의 복잡도는 N의 지수승으로 증가*하므로 재귀적 인자를 포함하지 않는 인스턴스화 보다 **컴파일러에 많은 부담을 가한다.**
- 초기 C++ 구현은 템플릿-식별자의 길이에 거의 비례하는 인코딩을 사용하여 위 예제에 대해서 *10000자에 가까운 문자를 사용*했지만 **최근 C++ 컴파일러들은 이름 인코딩 증가도를 줄이는 압축기술을 사용**하고 있다.

## 루프를 풀기 위한 메타프로그래밍
- 메타프로그래밍을 실용적으로 사용한 응용 중 하나는 숫자 계산을 위한 루프를 풀어내는 것이다.
- 벡터의 내적을 생각해보자. 두 벡터 a, b의 내적은 두 벡터 내 대응되는 요소의 곱을 모두 합한 값이다.
> a dot b = a[0] \* b[0] + a[1] \* b[1] + a[2] \* b[2]

- 이와 같은 내적을 계산하는 코드를 작성한다면 다음과 같이 작성할 수 있다.
```c++
// META_07.cpp

template <typename T>
inline T dot_product( int dim, T* a, T* b )
{
	T result = T( );
	for ( int i = 0; i < dim; ++i )
	{
		result += a[i] * b[i];
	}
	return result;
}
```
- 이 코드는 옳은 결과를 반환하지만 높은 성능을 보여야 하는 애플리케이션에서는 너무 길다.
- 성능을 증가시키기 위해서 메타프로그래밍을 통하여 내적을 구하는 부분의 루프를 풀 수 있다.
```c++
// META_07.cpp
template <int DIM, typename T>
class DotProduct
{
public:
	static T result( T* a, T* b )
	{
		return *a * *b + DotProduct<DIM - 1, T>::result( a + 1, b + 1 );
	}
};

template <typename T>
class DotProduct<1, T>
{
public:
	static T result( T* a, T* b )
	{
		return *a * *b;
	}
};

template <int DIM, typename T>
inline T Dot( T* a, T* b )
{
	return DotProduct<DIM, T>::result( a, b );
}
```
- 이런 방식의 프로그래밍은 컴파일 시에 배열의 크기를 알아야 하지만 대부분의 경우 크기를 알기 때문에 문제가 없다.
