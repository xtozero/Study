# 템플릿 인자 추론
## 개요
- 모든 템플릿이 자신의 템플릿 인자를 명시적으로 알려야 한다면 코드가 길어지고 보기 흉해진다.
- C++ 컴파일러는 템플릿 인자 추론이라고 불리는 과정을 통해 의도된 템플릿 인자를 알아서 결정할 수 있다.

## 추론 과정
- 추론 과정은 함수 인자의 데이터형과 함수 템플릿의 파라미터형을 비교해 하나 이상의 추론된 파라미터로 올바르게 치환하는 과정이다. 각 인자 - 파라미터 쌍은 독립적으로 분석되고 끝에 가서 결과가 일치하지 않으면 추론 과정은 실패한다.
```c++
// TAD_01.cpp
template <typename T>
const T& max( const T& a, const T& b )
{
	return a < b ? b : a;
}

int main( )
{
	int g = max( 1, 1.0 );
}
```
- 여기서 첫 번째 호출 인자는 int형으므로 일단 max()의 템플릿 파라미터 T는 int로 추론된다. 그러나 두 번째 호출 인자는 double이므로 T가 double이어야 한다. **두 결과가 일치하지 않기 때문에 여기서 추론 과정이 실패**한다.
> 여기서는 추론 과정이 실패했다고 말한다. 이후 max라는 다른 이름의 템플릿에서 추론 과정이 성공할 수 있으므로 프로그램이 유효하지 않다고 말하지 않는다.

- 모든 추론된 템플릿 파라미터가 일관되게 결정되더라도 인자를 치환한 이후 유효하지 않은 함수가 생성된다면 추론 과정은 실패한다.
```c++
// TAD_01.cpp
template <typename T>
typename T::ElementT at( const T& a, int i )
{
	return a[i];
}

int main()
{
	//...

	int *p = &g;
	int x = at( p, 7 );
}
```
- 여기서 템플릿 파라미터 T는 int\*로 결정되지만 int\*::Element라는 반환형은 C++에서 정상적이지 않은 형태이므로 결국 추론과정은 실패한다.
- 추론 과정의 마지막으로 인자-파라미터 일치 과정이 어떻게 되는지 살펴봐야 하는데 [04_Function Template](04_Function_Template.md) 에서 한번 보았으므로 간단하게 정리하고 넘어간다.

1\. 파라미터가 reference 형식인 경우 : reference를 무시하고 pattern-matching한다.

2\. 파라미터가 forwarding reference 형식인 경우 : r-value인 경우 reference를 무시하고 pattern-matching, l-value인 경우 l-value reference로 추론된다.

3\. 파라미터가 reference가 아닌 경우 : cv-qualifier, mutable, reference를 무시한다.

## 추론된 문맥
- 인자 추론에 관한 기본적인 예제를 몇 가지 더 살펴보자.
```c++
// TAD_02.cpp
template <typename T>
void f1( T* );

template <typename E, int N>
void f2( E( &)[N] );

template <typename T1, typename T2, typename T3>
void f3( T1( T2::* )( T3* ) );

class S
{
public:
	void f( double* );
};

int main()
{
	int*** a = nullptr;
	f1( a );		// T를 int**로 추론
	
	bool b[42];
	f2( b );		// E는 bool로 N은 42로 추론
	f3( &S::f );	// T1 = void , T2 = S, T3 = double
}
```
- 복잡한 데이터형의 일치 과정은 높은 수준에서 시작해 구성 요소를 살펴보며 일치되는지를 알아보는 방식으로 진행된다. 대부분의 데이터형 선언 생성이 이런 방식을 통해 일치되며 이런 방식을 추론된 문맥(deduced context)이라 한다. 하지만 일부는 추론된 문맥이 될 수 없다.

1\. 한정된 데이터형 이름, 예를 들어 Q<T>::x는 템플릿 파라미터 T를 추론할 때 사용될 수 없다.
```c++
// TAD_02.cpp
template <typename T>
class Q
{
public:
	using Type = T;
};

template <typename T>
void f4( typename Q<T>::Type arg ) {}

Q<int>::Type c;
f4( c );					// error
```

2\. decltype 한정자
```c++
// TAD_02.cpp
template <typename T>
void f5( decltype( *std::declval<T>( ) ) arg ) {}

int d;
f5( d );					// error
```

3\. 자료형이 아닌 템플릿 인자 혹은 배열 경계의 템플릿 파라미터를 참조하는 부분 표현식 ( A non-type template argument or an array bound in which a subexpression references a template
parameter )
```c++
// TAD_02.cpp
template <std::size_t N>
void f6( std::array<int, 2 * N> arg ) {}

std::array<int, 10> e;
f6( a );					// error
```

4\. 기본 인자를 가진 함수 파라미터의 파라미터 타입으로 사용되는 템플릿 파라미터
```c++
// TAD_02.cpp
template<typename T, typename F>
void f7( const std::vector<T>& v, const F& comp = std::less<T>( ) );

std::vector<std::string> v( 3 );
f7( v );					// error : F가 추론될 수 없음.
```

5\. 인자가 하나 이상의 함수와 매치되는 함수, 오버 로딩 집합이거나 하나 이상의 함수 템플릿을 포함하고 있는 오버 로딩 집합일 경우
```c++
// TAD_02.cpp
template<typename T> 
void f8( const T& value ) { std::cout << value; }

f8( "123" );				// ok : T = char[4]
f8( std::endl );			// error : function template
```

6\. 파라미터가 std::initializer\_list 나 std::initializer\_list& 가 아닐 때 인자가 중괄호 초기화 리스트( braced-init-list )일 경우
```c++
// TAD_02.cpp
template<class T> void f9( std::vector<T> ) {}
template<class T> void f10( std::vector<T>, T x ) {}

f9( { 1, 2, 3 } );			// error
f10( { 1, 2, 3 }, 10 );		// ok
```

7\. 파라미터가 파라미터 팩(Parameter Pack)이고 파라미터의 끝이 나타나지 않는 경우
```c++
// TAD_02.cpp
template<class... Ts, class T> void f11( T n, Ts... args ) {}
template<class... Ts, class T> void f12( Ts... args, T n ) {}

f11( 1, 2, 3, 4 ); 			// ok
f12( 1, 2, 3, 4 ); 			// error
```

8\. 파라미터가 포인터나 레퍼런스가 아닌 배열형일 경우의 첫 번째 경계( major bound )
```c++
// TAD_02.cpp
template<int i> void f13( int arg[10][i] ) {}
template<int i> void f14( int arg[i][20] ) {}
template<int i> void f15( int( &arg )[i][20] ) {}

int m[10][20];
f13( m );     				// ok: i = 20
f13<20>( m );				// ok
f14( m );    				// error
f14<10>( m );				// ok
f15( m );     				// ok: i = 10
f15<10>( m ); 				// ok
```

## 특별 추론 상황
- 추론을 위해서 사용되는 (A, P)가 함수 호출을 위한 인자와 함수 템플릿의 파라미터에 존재하지 않는 경우가 두 가지 있다.

1\. 함수 템플릿의 주소를 사용할 때
```c++
// TAD_03.cpp
template <typename T>
void f1( T, T ) {}

void( *pf )( char, char ) = &f1;
```

- P는 void( T, T ) 이고 A는 void( char, char ) 이다. T를 char로 치환하면 추론이 성공하고 f1<char> 특수화의 주소로 초기화된다.

2\. 연산자 템플릿 변환
```c++
// TAD_03.cpp
class S
{
public:
	template <typename T> operator T&( ) {}
};

void f2( int (&)[20] ) {}

void g( S s )
{
	f2( s );
}
```

- P는 T이고 A는 int (&)[20]이다 . T를 int[20]으로 치환하면 추론이 성공한다.

## 허용되는 인자 변환
- 일반적으로 템플릿 추론은 함수 템플릿 파라미터를 치환할 때 P라는 파라미터화된 데이터형을 A라는 데이터형과 똑같게 만들지만, 다음과 같은 차이는 허용된다.

1\. 파라미터가 참조 선언자와 함께 선언된 경우 치환된 P형은 A형보다 const나 volatile로 좀 더 한정될 수 있다.
```c++
// TAD_04.cpp
template <typename T>
void f1( const T& arg ) { std::cout << typeid( arg ).name( ) << std::endl; }

template <typename T>
void f2( volatile T& arg ) { std::cout << typeid( arg ).name( ) << std::endl; }

int val = 0;
f1( val );
f2( val );
```

2\. A형이 포인터나 멤버 접근 포인터형일 경우 한정된 변환으로 치환된 P형으로 변환될 수 있다.
```c++
// TAD_04.cpp
template <typename T>
void f3( const T* arg ) {}

f3( &val );
```

3\. 추론이 변환 연산자 템플릿을 위해 일어나지 않는 한 치환된 P형은 A형의 기본 클래스형이거나 A가 포인터로 가리키고 있는 클래스형의 기본 클래스 형에 대한 포인터일 수 있다.
```c++
// TAD_04.cpp
template <typename T>
class Base {};

template <typename T>
class Derive : public Base<T> {};

template <typename T>
void f3( Base<T>* ) {}

void g( Derive<long> dl )
{
	f3( &dl );
}
```

- **정확히 일치되지 않는 경우에만 완화된 일치 조건이 고려**된다. 완화된 일치 조건을 사용해도 A형을 대체된 P의 변환을 통해서 맞출 수 있는 하나의 치환이 존재해야지만 성공한다.

## 클래스 템플릿 파라미터
- 템플릿 인자 추론은 함수와 멤버 함수 템플릿에만 적용된다.( c++17 부터 클래스 템플릿에도 적용된다. )
- 템플릿 클래스의 인자는 생성자 호출 인자에서 추론되지 않는다. ( until c++14 )
```c++
// TAD_05.cpp
template <typename T>
class S
{
public:
	S( T b ) : a( b )
	{

	}
private:
	T a;
};

S x( 12 );		// error : 추론되지 않는다.
```

## 기본 호출 인자
- 함수 템플릿도 일반 함수처럼 기본 함수 호출 인자를 명시할 수 있다.
```c++
// TAD_06.cpp
template <typename T>
void int( T* loc, T const& val = T( ) )
{
	*loc = val;
}
```

- 기본 함수 호출 인자는 템플릿 파라미터에 종속될 수 있는데 이렇게 종속된 인자는 명시적인 인자가 제공되지 않을 때만 인스턴스화된다.
```c++
// TAD_06.cpp
class S
{
public:
	S( int, int ) {}
};

S s( 0, 0 );

int main( )
{
	init( &s, S( 7, 42 ) );
}
```

- 위 코드에서 S는 기본 생성자가 없으므로 기본 호출 인자가 유효하지 않지만, 명시적인 인자를 제공하면 유효한 코드이다.
- 기본 호출 인자가 종속적이지 않아도 템플릿 인자를 추론하는데 기본 호출 인자를 사용할 수 없다. 따라서 아래의 코드는 유효하지 않다.
```c++
template <typename T>
void f( T x = 42 ) {}

f<int>( );		// ok : T=int
f( );			// error
```

## 바튼-넥만 트릭
- 존 J. 바튼과 리 R. 넥만이 제시한 제한된 템플릿 확장( restricted template expansion )은 그 당시 함수 템플릿이 오버로딩될 수 없고 컴파일러 대부분에서 네임스페이스를 지원하지 않았다는 사실을 기반으로 만들어졌다.
- 바튼-넥만 트릭을 알아보기 위해서 operator==을 정의하려고 하는 Array라는 클래스 템플릿이 있다고 가정하면 operator==은 자신의 인자에 관해서 대칭적이어야 하므로 다음과 같이 네임스페이스 영역 함수로 선언하는 편이 좋다.
```c++
// TAD_07.cpp
template <typename T>
class Array
{

};

template <typename T>
bool operator==( const Array<T>& lhs, const Array<T>& rhs )
{

}
```

- 하지만 **함수 템플릿을 오버로딩 할 수 없다면 해당 영역에서는 이것 외의 operator== 연산자를 선언할 수 없어서 다른 클래스 템플릿을 위해 operaotor== 이 필요할 경우 문제**가 된다.
- 바튼-넥만 트릭은 이를 클래스 내에서 일반 프렌드 함수로 정의된 연산자를 둠으로써 해결했다.
```c++
// TAD_07.cpp
template <typename T>
class Array
{
public:
	friend bool operator==( const Array<T>& lhs, const Array<T>& rhs )
	{
		return ArrayAreEqual( lhs, rhs );
	}
};
```

- 바튼-넥만 트릭 버전의 Array 클래스가 인스턴스화되면 **인스턴스화의 결과로 프렌드 연산자 함수가 선언되지만, 이 함수 자체는 함수 템플릿의 인스턴스가 아니라 일반 함수**이다.
- 이 기법으로 템플릿 operator==의 사용이 모든 데이터형 T에 적용되지 않게 할 수 있기 때문에 이 기법을 제한된 템플릿 확장이라 불렀다.
- operator==( const Array\<T\>& lhs, const Array\<T\>& rhs ) 는 클래스 내에 정의돼 있으므로 묵시적으로 인라인으로 취급된다. 그래서 인라인일 필요가 없으며 다른 템플릿의 이름과 충돌할 일도 없을 것 같은 함수 템플릿 ArrayAreEqual을 도입하였다.

- 바튼-넥만 트릭은 이제 **더는 원래 목적으로 사용될 필요는 없다.** 다만 이 트릭으로 **클래스 템플릿 인스턴스화를 통해 일반 함수를 생성할 수 있다는 점은 중요**하다.
- 함수 템플릿에서 생성된 함수는 아니므로 템플릿 인자 추론을 거칠 필요는 없지만, 일반적인 오버로딩 해석 법칙은 거쳐야 한다. 이론적으로 프렌드 함수를 특정 호출 장소에 일치시키기 위해 부가적으로 묵시적 변환을 거칠 수도 있다는 뜻이다.
- 하지만 표준 C++에서는 **주입된 프렌드 함수가 주위 환경에서 무조건 가시화되지 않고 ADL을 통해서만 가시화**된다. 즉 함수 호출의 인자는 프렌드 함수를 포함하고 있는 클래스에 연관된 클래스를 갖고 있어야만 한다.
```c++
// TAD_07.cpp
class S {};

template <typename T>
class Wrapper
{
private:
	T object;
public:
	Wrapper( T obj ) : object( obj ) {}
	friend void f( const Wrapper<T>& arg ) {}
};

int main()
{
	S s;
	Wrapper<S> w( s );

	f( w );
	f( s );
}
```
- 위 코드에 f()는 w와 관련된 클래스에 선언된 프렌드이므로 f( w )는 유효하다. 하지만 f( s ) 호출에서는 s의 클래스 S가 wrapper\<S\>와 관련이 없으므로 가시화되지 않는다.
- 그래서 S형에서 Wrapper\<S\>로의 유효한 묵시적 변환이 있어도 **후보 함수 f가 처음에 발견되지 않아 이 변환은 절대 고려되지 않는다.**