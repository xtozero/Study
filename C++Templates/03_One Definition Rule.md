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
    
    1\. 네임스페이스와 네임스페이스 별칭 : 네임스페이스와 네임스페이스의 별칭에 대한 선언은 항상 정의다. 다만 네임스페이스의 멤버 목록은 이후에 확장될 수 있다.
    
    2\. 클래스, 클래스 템플릿, 함수, 함수 템플릿, 멤버 함수, 멤버 함수 템플릿 : 선언이 중괄호{}로 묶인 내용을 가진 이름으로 이뤄졌으면 정의다.  
    > 공용체, 연산자, 멤버 연산자, 정적 멤버 함수, 생성자와 소멸자 그리고 이 들의 템플릿 버전에 대한 명시적 특수화에도 적용된다.

    3\. 열거형 : 중괄호{}로 묶인 열거자(enumerators)목록이 뒤따라오면 정의다.

    4\. 지역 변수와 정적이지 않은(nonstatic) 데이터 멤버 : 항상 정의로 취급된다.

    5\. 전역 변수 : extern이 붙지 않거나 초기화를 가지고 있다면 정의다.

    6\. 정적 데이터 멤버 : 자신이 속해 있는 클래스나 클래스 템플릿의 외부에서 선언되면 정의다.

    7\. typedef, using 선언과 using 지시자 : 정의가 아니다.

    8\. 명시적 인스턴스화 지시자 : 이 책에서는 정의로 취급한다.