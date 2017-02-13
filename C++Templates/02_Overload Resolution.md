# 오버로딩 해석
## 개요
- 오버로딩 해석(Overload Resolution) : 호출 표현식에 대해서 호출한 대상을 선택하는 과정.
```c++
void DisplayNum(int) {}
void DisplayNum(double) {}

int main()
{
    DisplayNum(1);
    DisplayNum(1.0);
}
```
## 오버로딩 시점
- 오버로딩 해석은 함수 호출 처리의 일부분이지만 아래와 같은 함수 호출에는 사용되지 않는다.

    > 함수 포인터, 멤버 함수 포인터를 통한 호출
    > 함수 유사 매크로
- 오버로딩 해석이 필요한 함수 호출은 다음과 같은 단계를 거쳐 호출된다.
    1. 이름을 룩업하여 초기 오버로딩 집합을 형성
    2. 템플릿 추론 등의 여러 가지 방법으로 집합을 재조정
    3. 후보 함수가 호출에 적합하지 않으면 오버로딩 집합에서 삭제하여 가용 함수 후보( viable function candidate )를 형성
    4. 가용 함수 후보 중 가장 잘 맞는 후보를 선택, 후보가 여러개 있다면 모호한 호출이 된다.
    5. 선택된 후보를 검사한다. ex) private 멤버라면 진단 메시지가 출력.

## 가용 함수의 정렬 방법
- 오버로딩 해석은 호출의 각 인자와 가용 함수 후보들의 파라미터 간 대응 정도에 따라 순위를 매긴다.
- 한 후보가 다른 후보보다 더 낫다고 판단되려면 모든 파라미터가 다른 후보들의 파라미터보다 덜 일치해서는 안 된다.
```c++
void Combine( int, double ) {}
void Combine( double, int ) {}

int main()
{
	Combine( 1, 2 ); // error C2666: 'Combine': 2개 오버로드에 비슷한 변환이 있습니다.
}
```

- 가용 후보의 파라미터가 주어진 인자에 대해서 얼마나 잘 일치하는지 아래와 같은 순서로 순위를 매길 수 있다.

1위 - **완벽한 일치** : 파라미터가 주어진 인자의 데이터형을 갖거나 참조자의 데이터형을 갖는 경우. ( const, volatile 한정자가 추가되었을 수 있다. )
```c++
void PerfectMatch( const int ) {} // #1
void PerfectMatch( double ) {} // #2

int main()
{
	PerfectMatch( 1 ); // #1 이 호출
}
```

2위 - **작은 수정을 통한 일치** : 배열을 첫 번째 요소에 대한 포인터로 변환시키거나 int\*\*의 인자를 int const\* const\*의 파라미터로 일치시키기 위해 const를 포함하여 호출.
```c++
void MinorAdjust( int* pArray ) { cout << "#1" << endl; } // #1
// void MinorAdjust( int** ptr ) { cout << "#2" << endl; } // #2
void MinorAdjust( int const* const* ptr ) { cout << "#3" << endl; } // #3

int main()
{
	int arr[5] = {};
	MinorAdjust( arr ); // 배열을 포인터로 변환 ( decay )

	int* pArr = arr;
	int** ppArr = &pArr;
	MinorAdjust( ppArr ); // #2의 주석을 풀면 완벽한 일치로 #2
                          // #2가 없으면 int** -> int const* const*로 수정하여 #3 호출
}
```

3위 - **데이터형 승격을 통한 일치** : 작은 정수형( bool, char, short, 열거형 )을 int, unsigned int, long, unsigned long으로 float를 double로 묵시적으로 변환하여 호출.
```c++
void Promotion(char) { cout << "#2" << endl; } // #1
void Promotion(int) { cout << "#3" << endl; } // #2

int main()
{
	Promotion( true ); // bool -> int 데이터형 승격으로 #2 호출
}
```

4위 - **표준 변환만을 사용한 일치** : 표준변환을 통해서 호출 생성자를 묵시적으로 호출하는 것은 포함하지 않음.
> 표준 변환은 다음과 같은 변환이 포함됩니다. <br>
\> 정수형 간의 변환 ex) bool -> char <br>
\> 실수형 간의 변환 ex) float, double -> long double <br>
\> 정수형과 실수형 간의 변환 <br>
\> 정수형, 실수형, 포인터형을 bool로 변환 <br>
\> 정수 0을 null pointer로 변환

```c++
void StandardConversion( char ) { cout << "#1" << endl; }
void StandardConversion( ... ) { cout << "#2" << endl; }

int main( )
{
	StandardConversion( true );
}
```

5위 - **사용자 정의 변환을 통한 일치** : 모든 종류의 묵시적 변환을 허용.
```c++
class Userdefined
{
public:
	Userdefined( int ) {}
};
void UserdefinedConversion( Userdefined ) { cout << "#1" << endl; }
void UserdefinedConversion( ... ) { cout << "#2" << endl; }

int main()
{
    UserdefinedConversion( 1 );
}
```

6위 - **생략을 통한 일치** : 생략된 파라미터는 거의 모든 데이터형에 일치한다. 다만 POD가 아닌 클래스형은 정의되지 않은 행동을 보인다.
```c++
void Ellipsis(...) { cout << "#1" << endl; }

int main()
{
    Ellipsis( 1 );
}
```
- 오버로딩 해석은 템플릿 인자 추론 이후에 일어나며 추론 자체는 어떤 종류의 변환으로도 간주하지 않는다.
```c++
template <typename T>
class Implicit
{
public:
	Implicit( T a ) { };
};

template <typename T>
void TemplateFunction( Implicit<T> ) {}

int main( )
{
	TemplateFunction<int>( 1 );	// ok
	TemplateFunction( 1 );		// error
}
```
## 멤버 함수를 위한 암시적 인자(*this)에 관한 오버로딩 동작