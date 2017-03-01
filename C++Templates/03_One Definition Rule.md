# 단정의 법칙
## 개요
- 단정의(單定義) 법칙 : 모든 파일에서 인라인이 아닌 함수는 단 한 번만 정의하고 클래스와 인라인 함수는 번역 단위 내에서 최대 한 번만 정의하도록 하여 모든 정의가 같게 하는 법칙

## Translation Units
- 번역 단위( Translation Units ) : 전처리기가 할 일을 마친 후 컴파일러에게 전달한 코드 덩어리
- 전처리기는 컴파일 지시자 (#if, #ifdef etc...)에 의해 선택되지 않은 코드를 삭제, #include로 추가된 파일들을 삽입하고 매크로를 확장한다.
```c++
// ODR_01.h
#ifdef DO_DEBUG
    #define debug(x) cout << x << endl
#else
    #define debug(x)
#endif

void debug_init() {}

// ODR_01.cpp
#include "ODR_01.h"

int main()
{
    debug_init();
    debug( "main()" );
}

// 위의 파일과 같은 하나의 파일 버전
void debug_init() {}

int main()
{
    debug_init();
}
```
- [외부 연결](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/01_BasicTemplateTerminology.md#Linkage)을 갖는 선언( 전역 함수 혹은 extern으로 선언된 변수 )이나 내보내기 된 템플릿의 인자 종속 룩업을 통해서 번역 단위 경계를 넘는 연결을 생성할 수 있다.

## [Declarations 와 Definitions](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/01_BasicTemplateTerminology.md#declarations-와-definitions)
- 선언은 프로그램에 이름을 도입하거나 재도입하는 C++ 생성 과정이다.
- 선언은 실체를 어떻게 도입할 것인가에 따라 정의가 될 수 있다.
- 선언과 정의의 분류
    
    1\. **네임스페이스와 네임스페이스 별칭** : 네임스페이스와 네임스페이스의 별칭에 대한 선언은 항상 정의다. 다만 네임스페이스의 멤버 목록은 이후에 확장될 수 있다.
    ```c++
    // ODR_02.cpp
    namespace A
    {
        namespace B
        {
            void Foo() {}
        }
    }

    int main()
    {
        namespace AB = A::B; // 네임스페이스 별칭
        // namespace AB = A;

        AB::Foo();
        A::B::Foo();
    }
    ```
    
    2\. **클래스, 클래스 템플릿, 함수, 함수 템플릿, 멤버 함수, 멤버 함수 템플릿** : 선언이 중괄호{}로 묶인 내용을 가진 이름으로 이뤄졌으면 정의다.  
    > 공용체, 연산자, 멤버 연산자, 정적 멤버 함수, 생성자와 소멸자 그리고 이들의 템플릿 버전에 대한 명시적 특수화에도 적용된다.
    ```c++
    // ODR_03.cpp
    class Declaration; // 선언
    class Declaration; // ok
    struct Definition {}; // 정의
    struct Definition {}; // error ODR에 의해서 한 번만 정의되야 함.
    ```

    3\. **열거형** : 중괄호{}로 묶인 열거자(enumerators) 목록이 뒤따라오면 정의다.
    ```c++
    // ODR_04.cpp
    enum Declaration : int;
	enum Declaration : int; // ok 
	enum Declaration; //  error C3432: 'Declaration': 범위가 지정되지 않은 열거형의 정방향 선언에는 내부 형식이 있어야 합니다.
	enum Definitions {};
	enum Definitions {}; // error
    ```

    4\. **지역 변수와 정적이지 않은(nonstatic) 데이터 멤버** : 항상 정의로 취급된다.
    ```c++
    // ODR_05.cpp
    int Definitions;
	int Definitions; // error
    ```

    5\. **전역 변수** : extern이 붙지 않거나 extern이 붙은 전역 변수가 초기화를 가지고 있다면 정의다.
    ```c++
    // ODR_06.cpp
    extern int global;
    extern int global; // ok
    extern int global = 2;
    extern int global = 2; // error
    ```

    6\. **정적 데이터 멤버** : 자신이 속해 있는 클래스나 클래스 템플릿의 **외부에서 선언되면 정의**다.
    ```c++
    // ODR_07.cpp
    class StaticMember
    {
    public:
        static int member; // 선언
        //static constexpr int member = 1; // 내부에서 정의하려면 이렇게 할 수도 있다.
    };

    int StaticMember::member = 1; // 정의
    ```

    7\. **typedef, using 선언(using decalarations)과 using 지시자(using directives)** : 정의가 아니다.
    ```c++
    // ODR_08.cpp
    class Base
    {
    public:
        void f( char ) { cout << "Base::f" << endl; }
        void g( char ) { cout << "Base::g" << endl; }
    };

    class Derived : public Base
    {
    public:
        using Base::f;
        using Base::g;
        void f( int ) { cout << "Derived::f" << endl; f( 'c' ); }
        void g( int ) { cout << "Derived::g" << endl; g( 'c' ); }
    };
    ```

    8\. **명시적 인스턴스화 지시자** : 이 책에서는 정의로 취급한다.
    ```c++
    // ODR_09.cpp
    template <typename T>
    void templateFunc( T value ) { cout << value << endl; }

    template void templateFunc<int>( int value );

    template <>
    void templateFunc( int value ) {} // error 이미 인스턴스화 되어 있음.
    ```
## 단정의 법칙 세부사항
### 프로그램당 한 번만 정의
- 다음 항목들은 **프로그램당 한 번** 정의돼야 한다.

    1\. 인라인이 아닌 함수와 인라인이 아닌 멤버 함수
    ```c++
    // TranslateUnit1.cpp
    int Add( int lhs, int rhs )
    {
        return lhs + rhs;
    }

    // TranslateUnit2.cpp
    int Add( int lhs, int rhs ) // error
    {
        return lhs + rhs;
    }
    ```
    
    2\. 외부 링크를 가지는 변수
    ```c++
    // TranslateUnit1.cpp
    int counter;

    // TranslateUnit2.cpp
    int counter;
    ```

    3\. 정적 데이터 멤버
    ```c++
    // OnePerProgram.h
    class GlobalCounter
    {
    private:
        static int m_counter;
    };

    // TranslateUnit1.cpp
    int GlobalCounter::m_counter = 0;

    // TranslateUnit2.cpp
    int GlobalCounter::m_counter = 0; // error
    ```
    
    4\. 인라인이 아닌 함수 템플릿, 인라인이 아닌 멤버 함수 템플릿과 인라인이 아닌 클래스 템플릿의 멤버가 export와 함께 선언됐을 경우
    ```c++
    // vs 2015 community 에서 실행
    // error C3348 : export 된 템플릿은 현재 c++ 표준이 아니라는 에러가 발생
    export
    template<typename T>
    T Add( T lhs, T rhs );

    ```
    
    5\. 클래스 템플릿의 정적 데이터 멤버가 export로 선언됐을 경우
    ```c++
    // vs 2015 community에서 실행
    // export된 템플릿은 현재 c++ 표준이 아니라는 에러가 발생 error C3348
    template <typename T>
    class ClassTemplate
    {
    private:
    	static int m_counter;
    };
    
    export template <typename T>
    int ClassTemplate<T>::m_counter = 0;
    ```

### 번역 단위당 한 번만 정의
- 어떤 엔티티도 번역 단위 내에서 두 번 이상 정의될 수 없다.
```c++
// ODR_13.cpp
inline void f( ) {}
inline void f( ) {} // error
```
- A라는 클래스형이 있다면 번역 단위에서 아래와 같이 사용되기 전에 먼저 정의돼야 한다.

    1\. A의 객체를 생성.
    > 해당 객체를 포함하는 객체가 생성되는 것과 같은 간접적인 생성도 포함된다.
    ```c++
    // ODR_14.cpp
    A a;
    ```

    2\. A에 대한 sizeof나 typeid의 적용
    ```c++
    // ODR_14.cpp
    sizeof( A );
    ```
    
    3\. 표현식을 어떤 변환을 사용해 A로 변환하거나 A에서 바뀌는 경우 또는 포인터나 참조자가 A를 가리키게 하거나 포인터나 참조자를 묵시적인 static_cast나 dynamic_cast를 통해 다른 것으로 바꿀 경우
    > (void*)로의 변환은 제외
    ```c++
    // ODR_14.cpp
    static_cast<A>( 1 + 2 );

	A* pa = nullptr;
	B* pb = dynamic_cast<A*>(pa);
    ```

    4\. A의 객체에 값을 할당
    ```c++
    // ODR_14.cpp
    A a = 1;
    ```
    
    5\. A의 인자를 갖거나 A를 반환하는 함수를 정의하거나 호출하는 경우. 다만 함수를 선언만 하는 것은 문제없다.
    ```c++
    // ODR_14.cpp
    A foo( ); // ok

    foo( ); // error;
    ```

- 인라인 함수는 해당 함수가 사용되는 모든 번역 단위에 정의돼야 한다. 다만 정의가 함수 호출 이후에 나올 수 있다.
```c++
inline void inlineFunc();

int main()
{
    inlineFunc(); // 유효하지만 아직 정의가 되지 않아 인라인이 되지 않을 수 있다.
}

void inlineFunc()
{
    cout << "Called\n";
}
```
### Cross-Translation Unit Equivalence Constraints ( 교차 번역 단위 동등 제약 )
- 한 번역 단위보다 더 많은 곳에 특정 실체를 정의할 수 있다면 서로 일치하지 않은 다중 정의가 생길 수 있다.
- 따라서 한 번역 단위보다 더 많은 곳에서 특정 실체를 정의할 수 있는 경우 모든 정의는 같은 의미를 가져야만 한다.
- 하지만 **C++ 표준은 다중 정의에서 차이점이 검출되거나 진단돼야 한다고 강제하지 않는다.**
- C++ 표준은 이러한 교차 번역 단위 동등 제약을 어겼다면 **정의되지 않은 동작이 발생하는 것을 허용**하였다.
- 교차 번역 단위 제약조건에 따르면 실체가 두 군데에서 정의되었을 때 정확히 같은 토큰(키워드, 연산자, 식별자 등등 전처리 후에도 남는 것들)의 순열을 가져야 한다
```c++
// ODR_15.h
void count1( );
void count2( );

void count_error1( );
void count_error2( );

// ODR_15_TR1.cpp
static int counter = 0;

inline void increase_counter( )
{
	++counter;
	std::cout << counter << std::endl;
}

inline void increase_counter1( )
{
	++counter;
	std::cout << counter << std::endl;
}

void count1( )
{
	increase_counter1( );
}

void count_error1( )
{
	increase_counter( );
}

// ODR_15_TR2.cpp
static int counter = 0;

// 번역 단위 1의 increase_counter와 정확히 같은 토큰을 가지고 있지만
// static int counter는 내부 연결을 갖는 서로 다른 실체이기 때문에 미정의 동작이 발생한다.
inline void increase_counter( )
{
	++counter;
	std::cout << counter << std::endl;
}

inline void increase_counter2( )
{
	++counter;
	std::cout << counter << std::endl;
}

void count2( )
{
	increase_counter2( );
}

void count_error2( )
{
	increase_counter( );
}
// main
int main( )
{
	count1( ); // 1이 출력
	count2( ); // 1이 출력

	count_error1( ); // 2가 출력
	count_error2( ); // 3이 출력 <- ???
                     // 다른 번역단위이지만 이상한 동작을 하게 된다.
}
```
- 교차 번역 단위 제약 조건은 선언 내 기본 인자에도 적용된다.
```c++
// ODR_16_TR1.cpp
namespace
{
	void unused( int a = 4 );
	void unused( int a )
	{
		std::cout << a << std::endl;
	}
}

void defaultArg1( )
{
	unused( );
}

// ODR_16_TR2.cpp
namespace
{
	void unused( int a = 3 );
	void unused( int a )
	{
		std::cout << a << std::endl;
	}
}

void defaultArg2( )
{
	unused( );
}

// ODR_16.cpp
defaultArg1( ); // 4가 출력
defaultArg2( ); // 3이 출력
```
- 묵시적으로 생성된 클래스의 기본 생성자가 두 번역 단위에서 다를 때 문제가 발생한다.
```c++
// // ODR_17_TR1.cpp
class X
{
public:
	X( int );
	X( int, int );
};

X::X( int = 0, int = 0 )
{
	std::cout << "X(int, int)" << std::endl;
}

class D : public X
{

};

D d1;

// // ODR_17_TR2.cpp
class X
{
public:
	X( int );
	X( int, int );
};

X::X( int = 0 )
{
	std::cout << "X(int)" << std::endl;
}

class D : public X
{

};

D d2;

// 출력 결과는 다음과 같으며 한 지역에 기본 인자를 제한하게 한다.
X(int, int)
X(int, int)
```
- 동일한 토큰이 같은 실체를 가리켜야 한다는 법칙에도 예외가 있다. 같은 토큰이 같은 값을 가지고 결과 표현식의 주소를 사용하지 않는 상수를 가리킨다면 두 토큰은 같은 것으로 간주한다.
```c++
// ODR_18.cpp
#ifndef _CROSSTRANSLATION_H
#define _CROSSTRANSLATION_H

// 두 번역 단위에 포함이 되면 const는 내부 연결을 가지므로 두 개의 다른 상수 변수가 생긴다.
// 하지만 이런 상수 변수는 컴파일 시 상수 값을 정의하지만 실시간에 특정 저장소를 가리키진 않는다.
// 변수의 주소를 가리킨다든지 저장소의 위치가 있어야 한다고 강요하지 않으면 두 상수가 같은 값을 갖는 것만으로 충분하다.
const int length = 10;

class MiniBuffer
{
	char m_buf[length];
};

#endif
```
- 템플릿의 경우 인스턴스화 시점에 바인드되는 이름들은 그 지점에 동일성 법칙이 적용돼야만 하고, 바인딩은 같아야만 한다.
```c++
// ODR_19.h
enum Color { red, green, blue };

void init( );

template<typename T> void highlight( T x )
{
	paint( x );
}

// ODR_19_TR1.cpp
namespace
{
    // 이름 없는 네임스페이스에 정의된 함수는 외부 링크를 갖지만 (c++11 전까지 http://en.cppreference.com/w/cpp/language/namespace 참고)
    // 다른 번역 단위의 이름 없는 네임스페이스에서 정의된 함수들과 다르다.
    // 즉 paint는 main의 paint 함수와 다른 함수이다.
	void paint( Color c )
	{
		std::cout << "paint - TraslationUnit1 : " << c << std::endl;
	}
}

void init( )
{
	highlight( blue );
}

// ODR_19.cpp
namespace
{
	void paint( Color c )
	{
		std::cout << "paint - main : " << c << std::endl;
	}
}

int main( )
{
	init( ); // "paint - main : 2" 출력
	highlight( red ); // "paint - main : 0" 출력
}
```
