# Tuple
Tuple은 다양한 데이터형의 객체를 모아둘 수 있는 클래스 템플릿을 말한다. 여기서는 C++11 이전, 이후의 Tuple 구현 방식을 살펴보고자 한다. 먼저 C++11 이전 Tuple은 표준 std::pair 템플릿과 유사한 구현체인 Duo에서 시작해서 Trio, Quartet 등 임의의 멤버를 여러 개 가질 수 있도록 확장할 것이다.

## Duo
듀오( Duo )는 두 객체를 하나의 데이터형으로 합친 것으로 표준 라이브러리인 std::pair 클래스 템플릿과 유사하지만 약간 다른 기능이 있다. 가장 간단한 Duo 템플릿은 다음과 같다.
```c++
template <typename T1, T2>
struct Duo
{
    T1 v1;  // 첫 번째 필드
    T2 v2;  // 두 번째 필드
};
```
위와 같은 템플릿은 유효하지 않은 값을 반환할 수 있는 함수에서 유용하게 사용할 수 있다.
```c++
Duo<bool, x> result = foo();
if ( result.v1 )
{
    // 유효한 결과 같이 v2에 있다.
}
```
Duo는 두 개의 필드를 가진 구조체를 쉽게 정의할 수 있게 한다. 이제 이 기본적인 기능에 몇 가지 방법을 통해 확장하여 좀 더 편리하게 만들어 보자. 먼저 생성자를 추가할 수 있다.
```c++
// Duo.h
template <typename T1, typename T2>
class Duo
{
public:
	T1 v1 = T1();	// 첫 번째 필드
	T2 v2 = T2();	// 두 번째 필드

    Duo( ) {}
	Duo( const T1& a, const T2& b ) : v1( a ), v2( b ) {}
};
```
명시적 데이터형 파라미터가 필요하지 않게 다음 함수를 추가해 필드형을 추론하게 만들 수 있다.
```c++
// Duo.h
template <typename T1, typename T2>
inline Duo<T1, T2> make_duo( const T1& a, const T2& b )
{
	return Duo<T1, T2>( a, b );
}
```
이제 Duo의 생성과 초기화가 좀 더 편리해졌다.
```c++
// Duo.h
Duo<bool, int> result;
result.v1 = true;
result.v2 = 42;
return result;

// or 

return make_duo( true, 42 );
```
필드형에 대한 접근을 제공하기 위해 다음과 같이 개선하면 Duo를 사용한 어댑터 템플릿을 만들 수 있다.
```c++
template <typename T1, typename T2>
class Duo
{
public:
	using Type1 = T1;	// 첫 번째 필드의 데이터형
	using Type2 = T2;	// 두 번째 필드의 데이터형
	static constexpr int N = 2;	// 필드의 수
	
	T1 v1 = T1();	// 첫 번째 필드
	T2 v2 = T2();	// 두 번째 필드

	Duo( ) {}
	Duo( const T1& a, const T2& b ) : v1( a ), v2( b ) {}
};
```
이 단계에 이르면 Duo는 std::pair와 다음과 같은 차이점을 갖게 된다.
1. 다른 이름을 사용했다.
2. 필드의 수를 가지는 멤버 변수 N을 제공한다.
3. 생성 중 묵시적인 데이터형 변환을 허용하는 멤버 템플릿 초기화가 존재하지 않습니다.
4. 비교 연산자를 제공하지 않는다.

좀 더 강력하고 깔끔하게 구현하려면 다음과 같은 코드를 사용해도 좋다.
```c++
// Duo_Final.h
template <typename T1, typename T2>
class Duo
{
public:
	using Type1 = T1;
	using Type2 = T2;
	static constexpr int N = 2;

private:
	T1 value1 = T1();
	T2 value2 = T2();

public:
	Duo( ) {}
	Duo( const T1& a, const T2& b ) : value1( a ), value2( b ) {}

	// 생성 중 묵시적 데이터형 변환을 위해
	template <typename U1, typename U2>
	Duo( const Duo<U1, U2>& d ) : value( d.v1( ) ), value2( d.v2( ) ) {}

	// 할당 중 묵시적 데이터형 변환을 위해
	template <typename U1, typename U2>
	Duo<T1, T2>& operator=( const Duo<U1, U2>& d )
	{
		value1 = d.value1;
		value2 = d.value2;
		return *this;
	}

	T1& v1( )
	{
		return value1;
	}
	const T1& v1( ) const
	{
		return value1;
	}

	T2& v2( )
	{
		return value2;
	}
	const T2& v2( ) const
	{
		return value2;
	}
};

// 비교 연산자 (혼합된 데이터형 허용)
template <typename T1, typename T2, typename U1, typename U2>
inline bool operator==( const Duo<T1, T2>& lhs, const Duo<U1, U2>& rhs )
{
	return lhs.v1( ) == rhs.v1( ) && lhs.v2( ) == rhs.v2( );
}

template <typename T1, typename T2, typename U1, typename U2>
inline bool operator!=( const Duo<T1, T2>& lhs, const Duo<U1, U2>& rhs )
{
	return !( lhs == rhs );
}

// 생성과 초기화를 편리하게 하는 함수
template <typename T1, typename T2>
inline Duo<T1, T2> make_duo( const T1& a, const T2& b )
{
	return Duo<T1, T2>( a, b );
}
```
위 코드는 다음과 같은 점을 수정하였다.
1. 데이터 멤버를 private으로 선언하고 접근 함수를 추가했다.
2. 비교 연산자인 ==, != 를 추가했다. 혼합된 데이터형을 비교할 수 있게 비교할 양쪽에 서로 다른 템플릿 파라미터 집합을 사용할 수 있도록 했다.

## 재귀적 Duo
많은 수의 값을 한 곳에 저장하기 위해 Trio나 다른 템플릿도 쉼게 추가할 수 있다.

하지만 Duo 자체를 좀 더 구조화시켜 Duo 객체를 내포시켜보도록 한다.
다음 객체 정의를 고려해보자
```c++
// 02_T.cpp
Duo<int, Duo<char, Duo<bool, double>>> q4;
```
q4는 재귀적인 Duo라고 부를 수 있다. 

q4가 네 데이터형을 같은 필드의 수를 세는 방법은 직관적이다. 필드의 수를 세는 공식적인 방법을 위해 Duo 템플릿을 부분적으로 특수화할 수 있다.
```c++
// Duo_Final.h
template <typename A, typename B, typename C>
class Duo<A, Duo<B, C>>
{
public:
	using T1 = A;
	using T2 = Duo<B, C>;
	static constexpr int N = T2::N + 1;

private:
	T1 value1;
	T2 value2;
};
```
또한 단 하나의 필드를 가지는 이종 컨테이너에도 적용할 수 있도록 Duo의 부분 특수화를 제공한다.
```c++
// Duo_Final.h
template <typename A>
class Duo<A, void>
{
public:
	using T1 = A;
	using T2 = void;
	static constexpr int N = 1;

private:
	T1 value1 = T1();

public:
	Duo( ) {}
	Duo( const T1& a ) : value1( a ) {}

	T1& v1( )
	{
		return value1;
	}
	const T2& v1( ) const
	{
		return value1;
	}

	void v2( ) {}
	void v2( ) const {}
};
```
## 필드의 데이터형
재귀적인 듀오는 새로 작성할 수도 있는 Trio나 Quartet 클래스보다 그리 편리하지 않다. 세 번째 값에 접근하려면 다음과 같은 코드를 사용해야 한다.
```c++
// 02_T.cpp
q.v2().v2().v1();
```
다행히도 재귀적 듀오에서 필드의 데이터형과 같은 값을 효율적으로 찾는 재귀적 템플릿을 쉽게 작성할 수 있다.

재귀적 듀오의 N 번째 필드의 데이터형을 찾기 위해 데이터형 함수 DuoT를 작성해 보자
```c++
template <int N, typename T>
class DuoT
{
public:
	using ResultT = void; // 일반적으로 결과 데이터형은 void
};

// 평범한 듀오의 첫 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoT<1, Duo<A, B>>
{
public:
	using ResultT = A;
};

// 평범한 듀오의 두 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoT<2, Duo<A, B>>
{
public:
	using ResultT = B;
};

// 재귀적 듀오의 N 번째 필드를 위한 특수화
template <int N, typename A, typename B, typename C>
class DuoT<N, Duo<A, Duo<B, C>>>
{
public:
	using ResultT = typename DuoT<N - 1, Duo<B, C>>::ResultT;
};

// 재귀적 듀오의 첫 번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoT<1, Duo<A, Duo<B, C>>>
{
public:
	using ResultT = A;
};

// 재귀적 듀오의 두 번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoT<2, Duo<A, Duo<B, C>>>
{
public:
	using ResultT = B;
};
```
## 필드의 값
재귀적 듀오에서 대응하는 필드의 값을 추출하는 것은 데이터형을 추출하는 것보다 좀 더 복잡하다.

val\<N\>(duo) 와 같은 형태의 인터페이스를 쓰고자 한다. 이 인터페이스를 구현하기 위해서는 도우미 클래스 템플릿이 필요하다.

왜냐면 클래스 템플릿 만이 부분적으로 특수화될 수 있으며 부분 특수화를 써야지만 원하는 값을 좀 더 효율적으로 얻어낼 수 있다. 다음 코드를 통해 val() 함수가 어떻게 이런 작업을 하는지 살펴본다.
```c++
template <int N, typename T>
class DuoValue
{
public:
	static void get( T& ) {}	// 기본적으로는 반환값이 없다.
	static void get( const T& ) {}
};

// 평범한 듀오의 첫 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoValue<1, Duo<A, B>>
{
public:
	static A& get( Duo<A, B>& d )
	{
		return d.v1( );
	}

	static A get( const Duo<A, B>& d )
	{
		return d.v1( );
	}
};

// 평범한 듀오의 두 번째 필드를 위한 특수화
template <typename A, typename B>
class DuoValue<2, Duo<A, B>>
{
public:
	static B& get( Duo<A, B>& d )
	{
		return d.v2( );
	}

	static B get( const Duo<A, B>& d )
	{
		return d.v2( );
	}
};

// 재귀적 듀오의 N 번째 필드를 위한 특수화
template <int N, typename A, typename B, typename C>
class DuoValue<N, Duo<A, Duo<B, C>>>
{
public:
	static typename std::reference_wrapper<typename DuoT<N, Duo<A, Duo<B, C>>>::ResultT>::type& get( Duo<A, Duo<B, C>>& d )
	{
		return DuoValue<N - 1, Duo<B, C>>::get( d.v2( ) );
	}

	static typename std::reference_wrapper<typename DuoT<N, Duo<A, Duo<B, C>>>::ResultT>::type get( const Duo<A, Duo<B, C>>& d )
	{
		return DuoValue<N - 1, Duo<B, C>>::get( d.v2( ) );
	}
};

// 재귀적 듀오의 1번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoValue<1, Duo<A, Duo<B, C>>>
{
public:
	static A& get( Duo<A, Duo<B, C>>& d )
	{
		return d.v1( );
	}

	static A get( const Duo<A, Duo<B, C>>& d )
	{
		return d.v1( );
	}
};

// 재귀적 듀오의 2번째 필드를 위한 특수화
template <typename A, typename B, typename C>
class DuoValue<2, Duo<A, Duo<B, C>>>
{
public:
	static B& get( Duo<A, Duo<B, C>>& d )
	{
		return d.v2( ).v1( );
	}

	static B get( const Duo<A, Duo<B, C>>& d )
	{
		return d.v2( ).v1( );
	}
};

template <int N, typename A, typename B>
inline typename std::reference_wrapper<typename DuoT<N, Duo<A, B>>::ResultT>::type& val( Duo<A, B>& d )
{
	return DuoValue<N, Duo<A, B>>::get( d );
}

template <int N, typename A, typename B>
inline const typename std::reference_wrapper<typename DuoT<N, Duo<A, B>>::ResultT>::type& val( const Duo<A, B>& d )
{
	return DuoValue<N, Duo<A, B>>::get( d );
}
```
이제 다음과 같이 듀오를 사용할 수 있다.
```c++
// 02_T.cpp

// 단순한 duo를 생성하고 사용
Duo<bool, int> d;
std::cout << d.v1( ) << std::endl;
std::cout << val<1>( d ) << std::endl;

// triple을 생성하고 사용
Duo<bool, Duo<int, float>> t;

val<1>( t ) = true;
val<2>( t ) = 42;
val<3>( t ) = 0.2;

std::cout << val<1>(t) << std::endl;
std::cout << val<2>(t) << std::endl;
std::cout << val<3>(t) << std::endl;
```
재귀 호출은 컴파일할 때 템플릿 인스턴스화 과정을 통해 풀려나며 함수들은 간단한 인라인 접근자이므로 꽤 효율적으로 호출할 수 있다. 좋은 컴파일러라면 위 코드를 간단한 구조체 필드 접근과 같은 코드로 줄일 수 있을 것이다.
하지만 여전히 Duo 객체를 선언하고 생성하는 것은 여전히 번거로운데 이제 이를 해결하려고 한다.
## Tuple 생성
재귀적 듀오는 중접된 구조를 가지기 때문에 템플릿 메타프로그래밍을 적용하기 쉽다.
많은 파라미터를 갖는 재귀적 Tuple 템플릿을 정의하고 적절한 크기의 재귀적 듀오형을 이끌어 내게 할 수 있다.
다양한 크기의 Tuple을 허용하기 위해 사용하지 않는 데이터형 파라미터인 NullT를 정의하고 NullT의 기본값을 null로 지정한다. 여기서 NullT는 자리표시자로 void는 파라미터형이 될 수 없으므로 void 대신 사용된다.
```c++
// Tuple.h
class NullT {};
```
Tuple은 Duo에서 파생되는 템플릿으로 하나 이상의 데이터형 파라미터가 NullT이다.
```c++
template<typename P1,
		typename P2 = NullT,
		typename P3 = NullT,
		typename P4 = NullT,
		typename P5 = NullT>
class Tuple : public Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>>
{
public:
	using BaseT = Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>>;

	Tuple( ) {}
	Tuple( const typename std::reference_wrapper<P1>& a1,
			const typename std::reference_wrapper<P2>& a2,
			const typename std::reference_wrapper<P3>& a3 = NullT( ),
			const typename std::reference_wrapper<P4>& a4 = NullT( ),
			const typename std::reference_wrapper<P5>& a5 = NullT( ) ) : BaseT( a1, Tuple<P2, P3, P4, P5, NullT>( a2, a3, a4, a5 ) ) {}
};


// 재귀적 상속을 끝내기 위한 특수화
template<typename P1, typename P2>
	class Tuple<P1, P2, NullT, NullT, NullT> : public Duo<P1, P2>
{
public:
	using BaseT = Duo<P1, typename Tuple<P2, NullT, NullT, NullT, NullT>>;

	Tuple( ) {}
	Tuple( const typename std::reference_wrapper<P1>& a1,
			const typename std::reference_wrapper<P2>& a2,
			const typename std::reference_wrapper<NullT>& a3 = NullT( ),
			const typename std::reference_wrapper<NullT>& a4 = NullT( ),
			const typename std::reference_wrapper<NullT>& a5 = NullT( ) ) : BaseT(a1, a2) {}
};
```
마지막으로 템플릿 파라미터를 자동으로 추론할 수 있는 make\_duo와 같은 함수가 있으면 좋을 것이다.
불행히도 함수 템플릿은 기본 템플릿 인자를 갖지 못하며 템플릿 파라미터 추론 과정에서 사용할 기본 함수 호출 인자도 갖지 못하므로 Tuple 크기에 맞춰 각기 다른 함수 템플릿 선언이 필요하다.
> c++ 11 에서는 함수 템플릿이 기본 템플릿 인자를 가질 수 있다. 또한 variadic template을 통해 가변 인자를 다룰 수 있다.

```c++
// Tuple.h
// 한 인자를 위한 편의 함수
template <typename T1>
inline Tuple<T1> make_tuple( const T1& a1 )
{
	return Tuple<T1>( a1 );
}

// 두 인자를 위한 편의 함수
template <typename T1, typename T2>
inline Tuple<T1, T2> make_tuple( const T1& a1, const T2& a2 )
{
	return Tuple<T1, T2>( a1, a2 );
}

// 세 인자를 위한 편의 함수
template <typename T1, typename T2, typename T3>
inline Tuple<T1, T2, T3> make_tuple( const T1& a1, const T2& a2, const T3& a3 )
{
	return Tuple<T1, T2, T3>( a1, a2, a3 );
}

// 네 인자를 위한 편의 함수
template <typename T1, typename T2, typename T3, typename T4>
inline Tuple<T1, T2, T3, T4> make_tuple( const T1& a1, const T2& a2, const T3& a3, const T4& a4 )
{
	return Tuple<T1, T2, T3, T4>( a1, a2, a3, a4 );
}

// 다섯 인자를 위한 편의 함수
template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline Tuple<T1, T2, T3, T4, T5> make_tuple( const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5 )
{
	return Tuple<T1, T2, T3, T4, T5>( a1, a2, a3, a4, a5 );
}
```
다음 코드는 Tuple을 어떻게 사용하는지 보여준다.
```c++
// 03_T.cpp
Tuple<int> t1;
val<1>( t1 ) += 42;
std::cout << t1.v1( ) << std::endl;

Tuple<bool, int> t2;
std::cout << val<1>( t2 ) << ", ";
std::cout << t2.v1( ) << std::endl;

Tuple<bool, int, double> t3;

val<1>( t3 ) = true;
val<2>( t3 ) = 42;
val<3>( t3 ) = 0.2;

std::cout << val<1>(t3) << ", ";
std::cout << val<2>(t3) << ", ";
std::cout << val<3>(t3) << std::endl;

t3 = make_tuple( false, 23, 13.13 );

std::cout << val<1>( t3 ) << ", ";
std::cout << val<2>( t3 ) << ", ";
std::cout << val<3>( t3 ) << std::endl;

Tuple<bool, int, float, double> t4( true, 42, 13, 1.95582 );
std::cout << val<4>( t4 ) << std::endl;
std::cout << t4.v2().v2().v2() << std::endl;
```


