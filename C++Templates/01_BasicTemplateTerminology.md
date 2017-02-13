# 기본 템플릿 용어
## Class template 혹은 Template class
- 구조체(struct), 클래스(class), 공용체(union)를 묶어서 클래스형(class types)이라고 한다.
- 클래스(class) 라는 말은 class나 struct로 시작되는 클래스형을 가리킨다.

    > '클래스형'은 공용체가 포함되지만, 클래스일 경우는 포함되지 않는다.
- 클래스 템플릿(class template)은 **템플릿인 클래스**를 말한다.
- 템플릿 클래스(template class)는 다음 상황에서 사용된다.
    1. 클래스 템플릿과 같은 의미
    2. **템플릿으로 생성된 클래스**
    3. **템플릿 식별자인 이름을 가지는 클래스**
    
    > 책에서는 템플릿 클래스에 대해서 설명하고 있지만 템플릿 클래스는 클래스 템플릿을 사람들이 오용하고 있는 용어라고 한다. ([관련 stackoverflow link]( http://stackoverflow.com/questions/879535/what-is-the-difference-between-a-template-class-and-a-class-template))

## Instantiation 와 Specialization
- 인스턴스화(Instantiation) : 템플릿에서 인자를 실제 값으로 치환하여 일반 클래스, 함수, 멤버 함수로 생성하는 과정
- 특수화(Specialization) : 인스턴스화 과정에서 생성된 실체
- 명시적 특수화(explicit specialization) : 템플릿 파라미터를 명시적으로 치환
```c++
template <typename T>
class BaseClass
{
    ...
};

template <>             // 명시적 특수화
class BaseClass<int>
{
    ...
};

template <typename T>
class BaseClass<T*>      // 부분 특수화 ( partial specialization )
{
    ...
};
```
## Declarations 와 Definitions
- 선언(declaration) : 이름을 C++영역에 도입하는 것
```c++
class C;
void f(int p);
extern int v;
template <typename T>
void func(T);
```
- 정의(definition) : 구조의 세부사항이 알려지거나 변수의 경우에는 저장 공간이 할당될 때를 의미
```c++
class C {};             // 선언이자 정의
void f(int p)
{
    std::cout << p << std::endl;
}
extern int v = 1;       // 초기화가 있으므로 v를 위한 정의
int w;                  // extern이 붙지 않은 전역 변수 선언이자 정의
template <typename T>
class BaseClass {};
```
## The One-Definition Rule
- 단정의 법칙(ODR, one-definition rule) : 재선언에 관한 몇 가지 제약사항

    > 인라인이 아닌 *함수, 멤버 함수, 전역 변수, 정적 데이터 멤버*는 **한 프로그램 내에서 단 한 번만 정의**
    > *클래스형, 인라인 함수*는 한 **번역 단위(translate unit)마다 한 번씩 정의, 모든 정의는 같아야 한다.**
- 번역 단위(translate unit) : 원본 파일을 전처리했을 때 나오는 결과물 #include 지시자가 가리킨 모든 내용물을 포함한 것

## Template Arguments 와 Template Parameters
- 템플릿 식별자(template id) : 꺾쇠( <> )에 둘러싸인 인자가 따라오는 템플릿 이름의 조합 ex) ArrayInClass<double, 10>
- 템플릿 파라미터(template parameters) : 템플릿 선언이나 정의에서 키워드 template 다음에 나열된 이름들이다. ex) template <typename T, typename N> 에서 T, N는 template parameters
- 템플릿 인자(template arguments) : 템플릿 파라미터의 자리에 대신 들어갈 아이템이다. ex) ArrayInClass<double, 10> 에서 double과 10
```c++
template <typename T, typename N>
class ArrayInClass
{
public:
    T array[N]
}

template <typename T>
class Dozen
{
public:
    ArrayInClass<T, 12> contents; // 여기서 T는 템플릿 파라미터이면서 템플릿 인자이다.
}
```
