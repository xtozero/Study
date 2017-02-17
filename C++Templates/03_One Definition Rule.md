# 단정의 법칙
## 개요
- 단정의(單定義) 법칙 : 모든 파일에서 인라인이 아닌 함수는 단 한 번만 정의하고 클래스와 인라인 함수는 번역 단위 내에서 최대 한 번만 정의하도록 하여 모든 정의가 같도록 하는 법칙

## Translation Units
- 번역 단위( Translation Units ) : 전처리기가 할 일을 마친 후 컴파일러에게 전달한 코드 덩어리
- 전처리기는 컴파일 지시자 (#if, #ifdef etc...)에 의해 선택되지 않은 코드를 삭제, #include로 추가 된 파일들을 삽입하고 매크로를 확장한다.
```c++
// header.hpp
#ifdef DO_DEBUG
    #define debug(x) cout << x << endl
#else
    #define debug(x)
#endif

void debug_init() {}

// myprog.cpp
#include "header.hpp"

int main()
{
    debug_init();
    debug( "main()" );
}

// 위의 파일과 동일한 하나의 파일 버전
void debug_init() {}

int main()
{
    debug_init();
}
```
- [외부 연결](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/01_BasicTemplateTerminology.md#Linkage)을 갖는 선언( 전역 함수 혹은 extern으로 선언된 변수 )이나 내보내기 된 템플릿의 인자 종속 룩업을 통해서 변역 단위 경계를 넘는 연결을 생성할 수 있다.

## [Declarations 와 Definitions](https://github.com/xtozero/Study/blob/master/C%2B%2BTemplates/01_BasicTemplateTerminology.md#declarations-와-definitions)
- 선언은 프로그램에 이름을 도입하거나 재도입하는 C++ 생성 과정이다.
- 선언은 실체를 어떻게 도입할 것인가에 따라 정의가 될 수 있다.
- 선언과 정의의 분류
    
    1\. **네임스페이스와 네임스페이스 별칭** : 네임스페이스와 네임스페이스의 별칭에 대한 선언은 항상 정의다. 다만 네임스페이스의 멤버 목록은 이후에 확장될 수 있다.
    ```c++
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

        AB::Foo();
        A::B::Foo();
    }
    ```
    
    2\. **클래스, 클래스 템플릿, 함수, 함수 템플릿, 멤버 함수, 멤버 함수 템플릿** : 선언이 중괄호{}로 묶인 내용을 가진 이름으로 이뤄졌으면 정의다.  
    > 공용체, 연산자, 멤버 연산자, 정적 멤버 함수, 생성자와 소멸자 그리고 이 들의 템플릿 버전에 대한 명시적 특수화에도 적용된다.
    ```c++
    class Declaration; // 선언
    class Declaration; // ok
    struct Definition {}; // 정의
    struct Definition {}; // error ODR에 의해서 한번만 정의되야 함.
    ```

    3\. **열거형** : 중괄호{}로 묶인 열거자(enumerators)목록이 뒤따라오면 정의다.
    ```c++
    enum Declaration : int;
	enum Declaration : int; // ok 
	enum Declaration; //  error C3432: 'Declaration': 범위가 지정되지 않은 열거형의 정방향 선언에는 내부 형식이 있어야 합니다.
	enum Definitions {};
	enum Definitions {}; // error
    ```

    4\. **지역 변수와 정적이지 않은(nonstatic) 데이터 멤버** : 항상 정의로 취급된다.
    ```c++
    int Definitions;
	int Definitions; // error
    ```

    5\. **전역 변수** : extern이 붙지 않거나 extern이 붙은 전역 변수가 초기화를 가지고 있다면 정의다.
    ```c++
    extern int global;
    extern int global; // ok
    extern int global = 2;
    extern int global = 2; // error
    ```

    6\. **정적 데이터 멤버** : 자신이 속해 있는 클래스나 클래스 템플릿의 **외부에서 선언되면 정의**다.
    ```c++
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
    template <typename T>
    void templateFunc( T value ) { cout << value << endl; }

    template void templateFunc<int>( int value );

    template <>
    void templateFunc( int value ) {} // error 이미 인스턴스화 되어 있음.
    ```
## 단정의 법칙 세부사항
- 다음 항목들은 **프로그램당 한 번** 정의돼야 한다.

    1\. 인라인이 아닌 함수와 인라인이 아닌 멤버 함수
    2\. 외부 링크를 가지는 정적 데이터형 멤버
    3\. 인라인이 아닌 함수 템플릿, 인라인이 아닌 멤버 함수 템플릿과 인라인이 아닌 클래스 템플릿의 멤버가 export와 함께 선언됐을 경우
    4\. 클래스 템플릿의 정적 데이터 멤버가 export로 선언됐을 경우
- 어떤 엔티티도 번역 단위 내에서 한번 이상 정의될 수 없다.
- 클래스형은 번역 단위에서 아래와 같이 사용되기 전에 정의돼야 한다.