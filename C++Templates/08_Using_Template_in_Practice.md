# 템플릿 실제 사용
## 포함 모델
- 대부분의 템플릿이 아닌 코드는 선언은 헤더파일( *.hpp, *.h, *.hh 등등 )에 놓고 정의는 C 파일( *.cpp, *.c, *.cc 등등 )에 놓는다.
- 이렇게 코드를 분리하여도 프로그램은 잘 동작한다. 하지만 템플릿에서는 분리된 코드는 에러를 일으킨다.
```c++
// UTIP_01.hpp
#ifndef  UTIP_01_HPP
#define UTIP_01_HPP

template <typename T>
void print_typeof( const T& );

#endif


// UTIP_01.cpp
#include "UTIP_01.hpp"

#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& )
{
	std::cout << typeid(x).name( ) << std::endl;
}

// UTIP_MAIN_01.cpp
#include "UTIP_01.hpp"

int main( )
{
	double ice = 3.0;
	print_typeof( ice ); // 링크 에러가 발생한다.
}
```
- 템플릿이 인스턴스화되려면 컴파일러는 어떤 정의가 어떤 템플릿 인자로 인스턴스화돼야 하는지 알아야한다.
- 하지만 코드가 분리되어 있는 경우 컴파일러가 정의를 알지 못하므로 어떤 인자에 대해서 템플릿 정의를 인스턴스화해야 하는지 모른다.
- 이 문제는 아래와 같은 방법으로 컴파일러가 정의를 알 수 있도록 해주면 해결할 수 있다.

1\. 헤더 파일에 소스 코드를 포함시키는 방법.
```c++
// UTIP_01.hpp
#ifndef  UTIP_01_HPP
#define UTIP_01_HPP

template <typename T>
void print_typeof( const T& );

#include "UTIP_01.cpp"

#endif

// UTIP_01.cpp
// UTIP_01.hpp include 부분 삭제
#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}
```

2\. 선언과 정의를 하나의 헤더 파일에 작성하는 방법.
- 이런 방식으로 템플릿 코드를 작성하는 것을 포함 모델이라 부른다.
- 포함 모델을 사용하면 문제를 해결할 수 있지만 **헤더파일( UTIP_01.hpp )을 포함하는데 드는 비용이 증가**된다.
> 이 예제의 경우 UTIP_01.cppd의 \<iostream\>, \<typeinfo\>가 추가로 불러들여진다.

- 또한 포함 모델의 경우 **인라인이 아닌 함수 템플릿은 인스턴스화될 때 함수의 새로운 복사본이 생성**(=POI)되는데 이런 복사본이 자동적으로 만들어지기 때문에 각기 다른 파일에 동일한 복사본을 생성할 수 있으며 ODR을 위배하여 에러가 발생할 수 있다.

## 명시적 인스턴스화
- c++ 표준은 직접 템플릿을 인스턴스화할 수 있게 명시적인 인스턴스화 지시자를 제공한다.
- 포함 모델 챕터의 링커 오류를 일으켰던 예제를 명시적 인스턴스화를 통해서 해결할 수 있다.
```c++
// UTIP_02_INST.cpp
#include "UTIP_02.cpp"

template void print_typeof<double>( const double& );
```
- 명시적 인스턴스화는 **template 키워드 다음에 인스턴스화하고 싶은 실체에 대해 파라미터를 완전히 치환한 선언이 뒤따르는 형태**로 구성된다.
- 명시적 인스턴스화는 멤버 함수나 정적 데이터 멤버에도 동일하게 적용될 수 있다.
```c++
// UTIP_03.cpp
// int에 대한 Stack<>의 명시적 인스턴스화
template <typename T>
class MyClass 
{
public:
	MyClass( ) noexcept {};
};

template MyClass<int>::MyClass( ) noexcept;

// 함수 템플릿에 대한 명시적 인스턴스화
template <typename T>
const T& max( const T& lhs, const T& rhs ) { return lhs > rhs ? lhs : rhs; }

template const int& max( const int&, const int& );
```
- 또한 간단하게 인스턴스화할 수 있는 모든 멤버를 명시적으로 인스턴스화할 수 있다. 다만 이미 인스턴스화된 멤버와 이전에 특수화된 멤버는 제외된다.
```c++
// UTIP_03.cpp
// int에 대한 Stack<>의 명시적 인스턴스화
template class Stack<int>;

// String에 대한 Stack<> 일부 멤버 함수의 명시적 인스턴스화
template Stack<std::string>::Stack( ) noexcept;
template void Stack<std::string>::push( const std::string& );
template std::string Stack<std::string>::top( ) const;

// error 중복된 명시적 인스턴스화
// template Stack<int>::Stack( );

// 이미 특수화된 템플릿 인수에 대해서는 어떤 영향도 주지 않는다.
// Explicit instantiation has no effect if an explicit specialization appeared before for the same set of template arguments.
// http://en.cppreference.com/w/cpp/language/class_template
template class Stack<float>;
```
- 적어도 프로그램 내에서 각기 다른 실체에 대해서는 하나의 명시적 인스턴스화가 있어야 한다. ([ODR 참조](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/03_One%20Definition%20Rule.md))
- 명시적 인스턴스화는 **함수 템플릿, 가변 템플릿, 멤버 함수, 클래스 템플릿의 정적 데이터 멤버, 멤버 함수 템플릿**의 경우에는 템플릿 정의가 같은 번역단위에 존재하면 명시적 인스턴스화 구문전에 완전한 정의가 존재하지 않아도 된다.
- 반면 **클래스 템플릿, 클래스 템플릿의 멤버 클래스, 멤버 클래스 템플릿**의 경우에는 명시적 인스턴스화 구문 전에 완전한 정의가 존재해야 한다.
- 수동 인스턴스는 어떤 실체가 인스턴스화되는지 프로그래머가 추적해서 일일이 명시적으로 인스턴스화 해주어야 하기 때문에 좋지 않다.
- 다만 아래와 같은 몇가지 장점이 있다.

1\. 프로그램의 요구에 맞게 인스턴스화 할 수 있다. 특히 헤더의 크기가 지나치게 커지지 않는다.

2\. 템플릿 정의를 가진 소스코드를 숨길 수도 있다. 하지만 이 경우 추가로 인스턴스화를 시도할 수 없다.

3\. 템플릿 인스턴스의 정확한 위치를 제어할 수 있다.

## 포함 모델과 명시적 인스턴스화 결합
- 포함 모델이나 명시적 인스턴스화중 어느 것을 쓸지 결정하지 못한 상태에서 템플릿의 선언과 정의를 두 파일에 따로 둘 수 있다.
- 포함 모델을 사용하고 싶다면 간단히 템플릿 정의 헤더를 포함시키면 된다.
```c++
// UTIP_04.cpp
#ifndef  UTIP_04_CPP
#define UTIP_04_CPP

#include "UTIP_04.hpp"

#include <iostream>
#include <typeinfo>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}

#endif

// UTIP_04_MAIN.cpp
#include "UTIP_04.hpp"
// 정의 파일을 포함 하거나
#include "UTIP_04.cpp"

int main( )
{
	double ice = 3.0;
	print_typeof( ice );
}
```
- 명시적으로 인스턴스화하고 싶다면 명시적 인스턴스 지시자를 가지는 파일을 제공할 수도 있다.
```c++
// UTIP_04_INST.cpp
// 명시적 인스턴스화 지시자를 가지는 파일을 제공

#include "UTIP_04.cpp"

template void print_typeof<double>( const double& );
```

## 분리 모델
- 분리 모델을 구현한 컴파일러가 드물고 관련 키워드 export는 c++11 부터 사용하지 않게 되었다. ([참고링크](http://en.cppreference.com/w/cpp/keyword/export))

## 템플릿과 인라인
- **함수 템플릿과 인라인 함수 모두 여러 번역 단위에 정의될 수 있다.** 정의를 포함한 헤더 파일을 여러 cpp 파일에 포함시키면 해당 번역 단위마다 정의된다. ([ODR 참조](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/03_One%20Definition%20Rule.md))
```c++
// UTIP_05.hpp
#include <iostream>

template <typename T>
void print_typeof( const T& x )
{
	std::cout << typeid(x).name( ) << std::endl;
}

// UTIP_05_TR1.h
#ifndef  _UTIP_05_TR1_H_
#define _UTIP_05_TR1_H_

void print_typeof_int( );

#endif


// UTIP_05_TR1.cpp
#include "UTIP_05_TR1.h"

#include "UTIP_05.hpp"

void print_typeof_int( )
{
	int value = 0;
	print_typeof( value );
}

// UTIP_05.cpp
#include "UTIP_05_TR1.h"

#include "UTIP_05.hpp"


int main( )
{
	int value = 0;
	print_typeof( value );
	print_typeof_int( );
}
```
- 이 때문에 함수 템플릿이 기본적으로 인라인이라고 생각할 수 있지만 **템플릿 함수는 인라인이 아니다.**
- **인라인으로 취급되는 함수를 작성하기 위해서는 inline 지정자를 사용**해야 한다.

## 전컴파일된 헤더
- 헤더 파일이 커지면 컴파일에 오랜 시간이 걸릴 수 있다. 템플릿은 이런 경향을 부추길 수 있으므로 컴파일 시간을 단축하기 위해서 전컴파일된 헤더(precompiled header)라고 불리는 기법이 존재한다.
- 전컴파일된 헤더는 표준 밖에서 정의됐으므로 컴파일러에 따라서 다르다. 따라서 여기서는 일반적인 동작에 대해서 알아본다.
- 컴파일러가 파일 내 코드를 번역할 때 컴파일러는 파일은 처음부터 끝까지 읽으며 토큰을 처리하고 룩업을 위해 기호 테이블을 만드는 등 내부 상태를 적응시키면서 목적파일을 생성한다.
- **전컴파일된 헤더 기법은 많은 파일이 같은 코드로 시작한다는 점**에 착안하였다.

1\. 같은 코드에 대해 컴파일한 후 그 시점에서 컴파일러의 완전한 상태를 저장한다.

2\. 같은 코드를 사용하는 프로그램의 모든 파일에 대해 컴파일하기 전에 저장된 전컴파일된 헤더를 불러와 다른 부분부터 컴파일을 시작한다.

- 전컴파일 헤더를 효율적으로 쓰기 위해서는 되도록 **시작하는 부분에 같은 코드가 많이 들어가게 해야** 한다.
> 빌드 시간의 상당 부분은 #include 지시자가 차지하므로 이들의 순서를 맞추는 것이 좋다.

> 어떤 프로그래머는 불필요한 헤더를 #include로 불러오더라도 전컴파일 헤더를 사용해 컴파일 시간을 줄이는 편을 선택하기도 한다. ( ex 모든 표준 헤더를 포함한 std.hpp라는 헤더 파일을 생성해 모든 표준 헤더를 불러들이게 할 수도 있다. )

## 템플릿 디버그하기
- 템플릿을 디버깅할 때 직면할 수 있는 문제는 크게 두 종류가 있다.

1\. 작성한 템플릿 코드가 문서화한 조건을 만족하는 어떠한 템플릿 인자에 대해서도 정상적으로 동작함을 어떻게 확신할 수 있을지

2\. 템플릿 사용자가 문서화된 대로 템플릿을 사용하였는데 동작하지 않을 때 어떤 요구사항을 어겼는지를 찾아낼 수 있을지이다.

- 템플릿 파라미터에는 두 종류의 제약 조건이 있을 수 있다.

1\. 문법적 제약조건 ( syntactic constraints ) : 컴파일 오류를 발생시키는 제약 조건
> 특정 생성자가 존재할 것, 특정 함수 호출이 모호하지 않아야 할 것 등

2\. 의미론적 제약조건 ( semantic constraints ) : 문법적 제약 조건외의 조건들 예를 들면 템플릿 파라미터가 < 연산자를 정의해놓길( 이것은 문법적 제약조건이다. ) 요구하는 것은 실제로 파라미터가 어떤 종류의 정렬을 정의할 수 있어야 한다. ex ) 사전식 순서로 문자을 정렬하는 것 등

- 이런 템플릿 라이브러리의 제약 조건을 개념 ( concept )이라고 한다.
> C++ 표준 라이브러리는 무작위 접근 반복자와 기본 생성 가능이라는 개념을 사용한다.

- 이런 개념들이 템플릿 구현이나 사용중에 어떻게 위반됐는지를 결정하는 것을 템플릿 코드 디버깅이라 부를 수 있다.

## 긴 오류 메세지 해석
- 일반적인 컴파일 오류는 꽤 간결하고 어디가 문제인지 바로 알 수 있다.
- 하지만 템플릿에서는 이 일이 그렇게 쉽지 않다.
```c++
// UTIP_06.cpp
#include <algorithm>
#include <functional>
#include <list>
#include <string>

int main( )
{
	std::list<std::string> coll;
	
	auto pos = std::find_if( coll.begin( ), coll.end( ), std::bind2nd(std::greater<int>(), "A") );
}
```
- 위의 코드를 g++에서 돌린 결과 나오는 오류 메세지는 다음과 같다.
```
In file included from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\stl_algobase.h:71:0,
                 from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\algorithm:61,
                 from UTIP_06.cpp:1:
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\predefined_ops.h: In instantiation of 'bool __gnu_cxx::__ops::_Iter_pred
<_Predicate>::operator()(_Iterator) [with _Iterator = std::_List_iterator<std::__cxx11::basic_string<char> >; _Predicate
 = std::binder2nd<std::greater<int> >]':
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\stl_algo.h:104:42:   required from '_InputIterator std::__find_if(_Input
Iterator, _InputIterator, _Predicate, std::input_iterator_tag) [with _InputIterator = std::_List_iterator<std::__cxx11::
basic_string<char> >; _Predicate = __gnu_cxx::__ops::_Iter_pred<std::binder2nd<std::greater<int> > >]'
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\stl_algo.h:161:23:   required from '_Iterator std::__find_if(_Iterator,
_Iterator, _Predicate) [with _Iterator = std::_List_iterator<std::__cxx11::basic_string<char> >; _Predicate = __gnu_cxx:
:__ops::_Iter_pred<std::binder2nd<std::greater<int> > >]'
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\stl_algo.h:3815:28:   required from '_IIter std::find_if(_IIter, _IIter,
 _Predicate) [with _IIter = std::_List_iterator<std::__cxx11::basic_string<char> >; _Predicate = std::binder2nd<std::gre
ater<int> >]'
UTIP_06.cpp:10:94:   required from here
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\predefined_ops.h:234:30: error: no match for call to '(std::binder2nd<st
d::greater<int> >) (std::__cxx11::basic_string<char>&)'
  { return bool(_M_pred(*__it)); }
                              ^
In file included from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\stl_function.h:1128:0,
                 from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\string:48,
                 from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\random:40,
                 from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\bits\stl_algo.h:66,
                 from c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\algorithm:62,
                 from UTIP_06.cpp:1:
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\backward\binders.h:157:7: note: candidate: typename _Operation::result_type s
td::binder2nd<_Operation>::operator()(const typename _Operation::first_argument_type&) const [with _Operation = std::gre
ater<int>; typename _Operation::result_type = bool; typename _Operation::first_argument_type = int]
       operator()(const typename _Operation::first_argument_type& __x) const
       ^
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\backward\binders.h:157:7: note:   no known conversion for argument 1 from 'st
d::__cxx11::basic_string<char>' to 'const first_argument_type& {aka const int&}'
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\backward\binders.h:163:7: note: candidate: typename _Operation::result_type s
td::binder2nd<_Operation>::operator()(typename _Operation::first_argument_type&) const [with _Operation = std::greater<i
nt>; typename _Operation::result_type = bool; typename _Operation::first_argument_type = int]
       operator()(typename _Operation::first_argument_type& __x) const
       ^
c:\mingw\lib\gcc\mingw32\5.3.0\include\c++\backward\binders.h:163:7: note:   no known conversion for argument 1 from 'st
d::__cxx11::basic_string<char>' to 'std::binary_function<int, int, bool>::first_argument_type& {aka int&}'
```
- 오류 메세지를 잘 살펴보면 std::binder2nd를 잘 못 작성했다는 것을 알 수 있다.
> error: no match for call to '(std::binder2nd<std::greater<int> >) (std::__cxx11::basic_string<char>&)' 이 부분을 보면 된다.

- 그러나 이렇게 긴 메세지는 해석하기 어렵다. 추후 concept이 표준에 도입되면 이러한 에러 메세지를 명확하게 변경할 수 있다.

## 얕은 인스턴스화
- 긴 오류 메세지 해석에서 보았던 에러와 같이 긴 오류 메세지로 인한 디버깅의 어려움을 해소하기 위해서 템플릿 인자가 제약 조건들을 만족하는지 조기에 확인해볼 수 있다.
```c++
// UTIP_07.cpp
#include <iostream>

template <typename T>
void clear( T const& p )
{
	*p = 0;
}

template <typename T>
void core( T const& p )
{
	clear( p );
}

template <typename T>
void middle( typename T::Index p )
{
	core( p );
}

template <typename T>
void shell( T const& env )
{
	typename T::Index i;
	middle<T>( i );
}

class Client
{
public:
	typedef int Index;
};

int main( )
{
	Client main_client;
	shell( main_client );
}
```
- 이 예제는 가장 깊은 계층인 core()가  int형으로 인스턴스화돼어 *연산으로 역참조할 수 없기 때문에 오류가 발생했다.
- 좋은 진단 정보라면 이 문제를 발생시킨 모든 계층에 대한 추적 정보를 담고 있겠지만 '긴 오류 메세지 해석' 부분에서 보았듯이 너무 많은 정보는 오히려 거추장스럽다.
- 얕은 인스턴스화는 **깊은 수준의 템플릿에 대한 요청을 만족시키지 못하는 템플릿 인자로 인스턴화될 때 얕은 단계에서 오류를 발생시키게 하기 위해 일부러 의미 없는 코드를 삽입**하는 방식이다.
- 앞선 예제에서는 shell에 다음과 같은 코드를 삽입하여 T::Index형의 값을 역 참조할 수 있다.
```c++
// UTIP_07.cpp
template <typename T>
inline void ignore( const T& )
{
}

template <typename T>
void shell( const T& env )
{
	class ShallowChecks
	{
		void deref( T::Index ptr )
		{
			ignore( *ptr );
		}
	};
	typename T::Index i;
	middle<T>( i );
}
```
- T의 T::Index가 역참조할 수 없는 데이터형이라면 오류는 이제 지역 클래스인 ShallowChecks에서 발생한다.
- 지역 클래스는 실제로 사용되지 않기 때문에 추가된 코드는 shell() 함수의 실행 시간에 영향을 주지 않는다.
- 많은 컴파일러는 ShallowChecks 클래스가 실제로 사용되지 않는다고 경고할텐데 ignore와 같은 템플릿을 사용하여 이런 경고를 숨길 수 있다 다만 코드의 복잡도가 증가한다.
- c++11 에서는 **static_assert** 구문을 사용하여 제약조건을 검사할 수 있다.
```c++
// UTIP_07.cpp
template <typename T>
void shell( const T& env )
{
	static_assert( std::is_pointer<typename T::Index>(), "is not pointer" );

	typename T::Index i = T::Index();
	middle<T>( i );
}
```

## 긴 기호
- '긴 오류 메세지 해석' 부분에서 템플릿의 또 다른 문제인 인스턴화된 템플릿 코드가 매우 긴 기호로 바뀌는 현상을 확인할 수 있다.
- 예를 들어 std::string은 다음과 같이 확장된다.
```c++
std::__cxx11::basic_string<char>
```
- c++ 표준 라이브러리를 사용하는 일부 프로그램은 10000자가 넘는 기호를 생성하기도 한다. 이런 긴 기호는 컴파일러, 링커, 혹은 디버거에서 오류나 경고를 생성하게 할 수 있다.
- 요즘 컴파일러는 이런 문제를 줄이기 위해서 압축 기술을 사용하는데 오류 메세지에서 압축된 이름을 사용하면 그 이름이 무엇을 뜻하는지 분명하게 드러나지 않는다.

## 추적자
- 템플릿이 빌드에 성공한 다음에도 올바르게 동작하는지 확인해야 한다.
- 추적자( tracer )는 검사할 템플릿의 인자로 사용될 수 있는 사용자 정의 클래스로 개발 초기에 템플릿 정의에서 문제를 검출함으로써 디버깅 문제를 완화한다.
- 많은 경우 추적자는 템플릿의 요구사항만을 만족하게 작성되나 **호출된 연산에 대한 추적을 생성하는데 중점**을 둔다. 이를 통해서 알고리즘의 효율성과 같은 것을 실험적으로 증명할 수 있고 연산의 과정도 증명할 수 있다.
```
// UTIP_08.hpp
#ifndef _UTIP_08_HPP_
#define _UTIP_08_HPP_

#include <iostream>

class SortTracer
{
private:
	int value;					// 저장할 정수값
	int generation;				// 추적자 생성
	static long n_created;		// 생성자 호출 횟수
	static long n_destoryed;	// 소멸자 호출 횟수
	static long n_assigned;		// 할당 횟수
	static long n_compared;		// 비교 횟수
	static long n_max_live;		// 현재 존재하는 객체의 최대 수

	// 현재 존재하는 객체의 최대 수 다시 계산
	static void update_max_live( )
	{
		if ( n_created - n_destoryed > n_max_live )
		{
			n_max_live = n_created - n_destoryed;
		}
	}

public:
	static long SortTracer::creations( )
	{
		return n_created;
	}

	static long SortTracer::destructions( )
	{
		return n_destoryed;
	}

	static long SortTracer::assignments( )
	{
		return n_assigned;
	}

	static long SortTracer::comparisions( )
	{
		return n_compared;
	}

	static long SortTracer::max_live( )
	{
		return n_max_live;
	}

	// 생성자
	SortTracer( int v = 0 ) : value( v ), generation( 1 )
	{
		++n_created;
		update_max_live( );
		std::cerr << "SortTracer #" << n_created << ", created generation " << generation << " (total: " << n_created - n_destoryed << ")\n";
	}

	// 복사 생성자
	SortTracer( const SortTracer& b ) : value( b.value ), generation( b.generation )
	{
		++n_created;
		update_max_live( );
		std::cerr << "SortTracer #" << n_created << ", copied as generation " << generation << " (total: " << n_created - n_destoryed << ")\n";
	}

	// 소멸자
	~SortTracer( )
	{
		++n_destoryed;
		update_max_live( );
		std::cerr << "SortTracer gneration" << generation << " destroyed (total: " << n_created - n_destoryed << ")\n";
	}

	// 할당
	SortTracer& operator=( const SortTracer& b )
	{
		++n_assigned;
		std::cerr << "SortTracer assignment#" << n_created << "(generation " << generation << " = " << b.generation << ")\n";
		value = b.value;
		return *this;
	}

	int val( ) const
	{
		return value;
	}

	// 비교
	friend bool operator< ( const SortTracer& a, const SortTracer& b )
	{
		++n_compared;
		std::cerr << "SortTracer comparision #" << n_compared << " (generation " << a.generation << " < " << b.generation << ")\n";
		return a.value < b.value;
	}
};

#endif

// UTIP_08.cpp
#include "UTIP_08.hpp"

long SortTracer::n_created = 0;
long SortTracer::n_destoryed = 0;
long SortTracer::n_assigned = 0;
long SortTracer::n_compared = 0;
long SortTracer::n_max_live = 0;
```
- 이 추적자를 통해서 주어진 템플릿에서 수행된 할당과 비교 연산뿐만이 아니라 실제 생성과 소멸의 형태도 추적할 수 있다.
```c++
// UTIP_08_MAIN.cpp
#include <iostream>
#include <algorithm>
#include "UTIP_08.hpp"

int main( )
{
	// 예제 입력 준비
	SortTracer input[] = { 7, 3, 5, 6, 4, 2, 0, 1, 9, 8 };

	// 초기값 출력
	for ( int i = 0; i < 10; ++i )
	{
		std::cerr << input[i].val( ) << ' ';
	}
	std::cerr << std::endl;

	// 초기 조건을 기억
	long created_at_start = SortTracer::creations( );
	long max_live_at_start = SortTracer::max_live( );
	long assigned_at_start = SortTracer::assignments( );
	long compared_at_start = SortTracer::comparisions( );

	// 알고리즘 수행
	std::cerr << "---[ Start std::sort() ]---------------------------------\n";
	std::sort<>( &input[0], &input[9] + 1 );
	std::cerr << "---[ End std::sort() ]-----------------------------------\n";

	// 결과 검증
	for ( int i = 0; i < 10; ++i )
	{
		std::cerr << input[i].val( ) << ' ';
	}
	std::cerr << "\n\n";

	// 마지막 보고
	std::cerr << "std::sort of 10 SortTracers"
		<< " was performed by:\n"
		<< SortTracer::creations( ) - created_at_start
		<< " temporary tracers\n"
		<< "up to "
		<< SortTracer::max_live( )
		<< " tracers at th same tiem ("
		<< max_live_at_start << " before)\n"
		<< SortTracer::assignments( ) - assigned_at_start
		<< " assignments\n"
		<< SortTracer::comparisions( ) - compared_at_start
		<< " comparisions\n\n";
}
```
- 이 프로그램을 실행시키면 많은 양의 출력이 생성되지만 중요한 내용 대부분은 마지막 보고에 담겨있다.
```
std::sort of 10 SortTracers was performed by:
9 temporary tracers                             // 9 개의 임시 추적자가 생성되었다.
up to 11 tracers at th same tiem (10 before)    // 동시에 생성된 추적자는 하나뿐이다.
33 assignments                                  // 33 번의 할당이 이루어졌다.
42 comparisions                                 // 42번의 비교가 이루어졌다.
```
- 이 추적자는 표준 sort() 알고리즘이 추적자가 가진 기능보다 많은 것을 요구하지 않는다.
> 연산자 == 는 정의하지 않았다.

## 원형
- 추적자는 추적할 템플릿의 요구사항을 최소한만 만족시키는 인터페이스를 제공한다.
- 이와 같은 추적자가 실시간 출력을 생성하지 않는다면 이 추적자는 원형(archetype)이라고 불린다.
- 원형을 사용하면 템플릿 구현이 의도한 문법적 제약 조건 이외의 것을 요구하지는 않는지 검증할 수 있다.