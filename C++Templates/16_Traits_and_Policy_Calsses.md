# 특질과 정책 클래스
## 개요
- 템플릿은 다양한 데이터형에 대해 클래스와 함수를 파라미터화할 수 있게 한다.
- 템플릿이 최대한 많은 템플릿 파라미터에 대해 데이터형이나 알고리즘의 모든 측면을 맞출 수 있다면 매우 좋을 것이다. 하지만 실질적으로는 수십 개의 템플릿 파라미터를 도입하는 것은 그다지 좋지 않다. 클라이언트 코드에서 수십 개의 인자들을 지정하는 것은 지나치게 지루할 것이다.
- 다행히도 대부분의 추가적인 파라미터는 합리적인 기본값을 가지고 있으며 일부의 경우 추가 파라미터들은 중요 파라미터에 의해 완전히 결정되며 그럴 경우 추가 파라미터는 모두 생략할 수 있다.
- 정책(Policy)클래스와 특질(Trait)은 C++ 프로그래밍 장치로 실질적인 템플릿을 설계하는 단계에서 제안된 것으로 이들을 사용하면 추가 파라미터들을 쉽게 관리할 수 있다.

## 수열 더하기
- 특정 수열을 더하는 작업은 꽤 일반적인 계산 작업이다. 그렇지만 수열 덧셈은 정책 클래스와 특질이 다양한 수준에서 어떻게 도움이 되는지 알아보는데 도움이 된다.

### 고정 특질
- 배열에 저장된 값을 모두 더하는 코드를 생각해보자. 더할 첫 번째 요소와 마지막 요소의 다음을 가르키는 포인터가 있다면 다음과 같이 코드를 작성할 수 있다.
```c++
// TAPC_01.cpp
template <typename T>
inline T accum( const T* beg, const T* end )
{
	T total = T( );
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}
```
- 합을 계산할 때 적절한 시작 값을 어떻게 계산할 것인가는 사실 결정하기 어렵다. 이 코드에서는 T()라는 표현식을 사용해서 int와 float와 같은 내장 수치 데이터형에서도 올바른 값이 설정되도록 하였다.
- 첫 번째 특질 템플릿을 알아보기 위해 accum()을 사용하는 다음 코드를 살펴보자
```c++
// TAPC_01.cpp
int main( )
{
	int num[] = { 1, 2, 3, 4, 5 };

	std::cout << "평균값 :"
			<< accum( &num[0], &num[5] ) / 5
			<< std::endl;

	char name[] = "templates";
	int length = sizeof( name ) - 1;

	std::cout << "평균값 :"
			<< accum( &name[0], &name[length] ) / length
			<< std::endl;
}
```
- 이 프로그램은 전반부에서 다섯 개의 정숫값을 더하기 위해 accum()을 사용했다. 이 합을 배열에 있던 정숫값의 개수로 나누면 정숫값들의 평균을 쉽게 얻을 수 있다.
- 프로그램의 후반부는 templates라는 단어가 속한 모든 낱말을 합한 후 평균을 구했다. 이때 평균은 a와 z값 사이에 있을 거라 예상할 수 있다. 하지만 출력 값을 살펴보면 다음과 같다.
```
평균값 :3
평균값 :-5
```
- 이런 결과가 나온 이유는 이 **템플릿이 char형에 대해 인스턴스화됐으므로 수용할 수 있는 값의 범위가 매우 좁기 때문이다.** 변수 total에서 사용할 데이터형을 알리는 부가적인 템플릿 파라미터 AccT를 도입하면 이 문제를 해결할 수 있다. 
- 하지만 그럴 경우 이 템플릿을 사용하는 모든 사용자들은 템플릿을 사용할 때마다 데이터형을 더 명시해야 한다. AccT를 도입한다면 위 예제는 다음과 같이 바뀌어 호출돼야 한다.
```c++
accum<int>(&name[0], &name[length]);
```
- 이렇게 작성하는 것이 그렇게 어려운 일은 아니겠지만 인자를 덜 지정하는 편이 더욱 좋을 것이다.
- 추가 파라미터에 대한 대안으로는 accum()이 호출되는 각 데이터형 T와 축적된 합을 저장하는 데이터형 사이의 관계를 생성하는 방법이다. 이 관계는 데이터형 T의 특성으로 간주할 수 있으며 합이 계산될 때 이 데이터형은 때로 T의 특질이라고 불릴 것이다. 결국 이런 관계는 템플릿의 특수화를 통해 표현된다.
```c++
// TAPC_02.cpp
template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
};

template<>
class AccumulationTraits<short>
{
public:
	typedef int AccT;
};

template <>
class AccumulationTraits<int>
{
public:
	typedef long AccT;
};

template <>
class AccumulationTraits<unsigned int>
{
public:
	typedef unsigned long AccT;
};

template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
};
```
- 템플릿 AccumulationTraits는 파라미터형에 대한 특질을 가지고 있으므로 특질 템플릿이라 불린다. 이 템플릿의 일반적인 정의를 제공하지 않는다. 왜냐면 데이터형이 무엇인지 모를 때에는 합의 데이터형으로 무엇이 좋을지 알기 힘들기 때문이다.
- 특질 템플릿을 사용해서 accum() 템플릿을 다음과 같이 다시 작성할 수 있다.
```c++
// TAPC_02.cpp
template <typename T>
inline typename AccumulationTraits<T>::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AccumulationTraits<T>::AccT;
	AccT total = AccT( );
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}
```
- 프로그램의 출력 결과는 다음과 같이 원하는 대로 출력된다.
```
평균값 :3
평균값 :108
```
- 알고리즘을 데이터형에 맞출 수 있는 매우 유용한 매커니즘을 추가했는데 그다지 많은 것이 바뀌진 않았다. 더불어 새 데이터형에 대해 accum()을 사용하면 AccumulationTraits 템플릿에 추가로 명시적 특수화를 선언하는 것만으로 적절한 AccT를 데이터형에 연결할 수 있다. 이것은 기본 데이터형이나 다른 라이브러리 등에서 선언된 데이터형에도 동일하게 동작한다.

### 값 특질
- 이번에는 데이터형에 국한되지 않은 부가 정보에 대해 알아보자. 상수나 다른 종류의 값들도 데이터형에 연결될 수 있다.
```c++
```
- Acct()가 합 계산 루프를 시작하기에 좋은 값을 반환할 거라는 보장은 없으며 심지어 Acct형에 기본 생성자가 없을 수도 있다. 그래서 여기도 특질을 사용할 수 있다. AccumulationTrait에 대해 새로운 값 특질을 추가한 예제를 보자.
```c++
// TAPC_03.cpp
template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
	static const AccT zero = 0;
};

//...
template <typename T>
inline typename AccumulationTraits<T>::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AccumulationTraits<T>::AccT;
	AccT total = AccumulationTraits<T>::zero;
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}
```
- 이 코드에서 합을 저장하는 변수의 초기화는 직관적이다. 다만 이런 방식의 단점은 C++이 클래스 내 정적 상수 데이터 멤버 중 정수형이나 열거형 값에 대해서만 초기화를 허용한다는 점이다. 따라서 다음과 같은 특수화에서는 오류가 발생한다.
```c++
// TAPC_03.cpp
template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
	static const AccT zero = 0.0;
};
```
- 한 가지 대안은 클래스 내에 값 특질을 정의하지 않는 방법이 있다.
```c++
// TAPC_03.cpp
template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
	static const AccT zero;
};

const double AccumulationTraits<float>::zero = 0.0;
```
- 이 방식은 잘 동작하긴 하지만 컴파일러가 위 사실을 잘 모른다는 단점이 있다. 클라이언트 파일을 처리할 때 컴파일러는 일반적으로 다른 파일의 정의를 알지 못한다. 예를 들어 이번 경우에서 컴파일러는 zero라는 값이 실제로는 0.0이라는 사실을 알아차리지 못한다.
> 즉 인라인되기 어렵다.

- 정수가 아닐 수 있는 값 특질에 대해서는 인라인 멤버 함수를 사용해 구현하는 편이 낫다.
```c++
// TAPC_04.cpp
template<typename T>
class AccumulationTraits;

template<>
class AccumulationTraits<char>
{
public:
	typedef int AccT;
	static AccT zero( )
	{
		return 0;
	}
};
//...
template <typename T>
inline typename AccumulationTraits<T>::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AccumulationTraits<T>::AccT;
	AccT total = AccumulationTraits<T>::zero();
//...
```
- C++11 을 지원하는 컴파일러에서는 다른 대안이 있는데 constexpr를 사용하는 것이다. constexpr로 선언된 리터럴 타입의 static 멤버 데이터는 클래스 정의 내에서 상수 표현식으로 초기화될 수 있다. ([참고 page](http://en.cppreference.com/w/cpp/language/static))
```c++
template <>
class AccumulationTraits<float>
{
public:
	typedef double AccT;
	static constexpr AccT zero = 0.0;
};
```

### 파라미터화된 특질
- 이전에 알아본 accum()에서 특질 사용은 고정돼 있었다. 데이터형과 분리된 특질이 정의되면 알고리즘 내에서 덮어쓸 수 없기 때문이다. 하지만 덮어쓰고 싶을 때가 있다. 예를 들면 float 값들은 같은 데이터형의 변수에 안전하게 더할 수 있으며 그렇게 하는 편이 좀 더 효율적일 때가 있다.
- 이에 대한 해결책으로는 템플릿 파라미터를 추가하긴 하되 특질 템플릿으로 추가된 파라미터의 기본값을 정하는 방식을 들 수 있다. 이 방법을 사용하면 많은 사용자는 추가된 템플릿 인자를 생략할 수 있고 예외적인 경우에는 이미 설정된 합의 데이터형을 덮어쓸 수 있다. 여기서의 유일한 문제는 함수 템플릿은 기본 템플릿 인자를 가질 수 없다는 점이다.
> C++11 부터는 함수 템플릿도 기본 템플릿 인자를 가질 수 있다.

- 먼저 알고리즘을 클래스로 바꾸는 우회법을 살펴보자.
```c++
template <typename T, typename AT = AccumulationTraits<T>>
class Accum
{
public:
	static typename AT::AccT accum( const T* beg, const T* end )
	{
		using AccT = typename AT::AccT;
		AccT total = AT::zero( );
		while ( beg != end )
		{
			total += *beg;
			++beg;
		}

		return total;
	}
};

int main( )
{
	char name[] = "templates";
	int length = sizeof( name ) - 1;

	std::cout << "평균값 :"
		<< Accum<char>::accum( &name[0], &name[length] ) / length
		<< std::endl;
}
```
- 아마도 이 템플릿을 사용하는 대부분의 사용자는 거의 모든 데이터형에 대해 첫 번째 인자의 데이터형을 그대로 사용하면 되므로 두 번째 템플릿 인자를 명시적으로 제공하는 일이 없을 것이다.
- C++11 을 지원하는 컴파일러에서 사용 가능한 방법은 기본 템플릿 인자를 사용한 예제를 살펴보자
```c++
template <typename T, typename AT = AccumulationTraits<T>>
inline typename AT::AccT accum( const T* beg, const T* end )
{
	using AccT = typename AT::AccT;
	AccT total = AT::zero( );
	while ( beg != end )
	{
		total += *beg;
		++beg;
	}

	return total;
}

float num[] = { 1, 2, 3, 4, 5 };

std::cout << "평균값 :"
	<< accum<float, AccumulationTraits<int>>( &num[0], &num[5] ) / 5
	<< std::endl;
```
- 번거롭게 클래스를 작성하지 않아도 원하는 바를 이룰 수 있다.

### 정책과 정책 클래스
- 지금까지는 축적(accumulation)을 합(summation)으로 생각해서 사용했다. 하지만 다른 종류의 축적도 있다. 주어진 값의 수열을 곱하거나 값들이 문자열이라면 모두 연결할 수 있다. 수열에서 가장 큰 값을 찾는 것도 축적 문제로 볼 수 있다.
- 이런 모든 방식에서 accum() 연산 중 바꿔야 할 부분은 사실 += *beg 뿐이다. 이 연산은 축적 과정의 정책이라고 불린다. 그리고 정책 클래스는 알고리즘에 하나 이상의 정책을 적용하는 인터페이스를 제공하는 클래스다.
- accum() 함수에 이런 인터페이스를 추가하는 예제를 살펴보자
```c++
// TAPC_06.cpp
template <typename T,
		  typename Policy = SumPolicy,
		  typename Traits = AccumulationTraits<T>>
inline typename Traits::AccT accum( const T* beg, const T* end )
{
	using AccT = typename Traits::AccT;
	AccT total = Traits::zero( );
	while ( beg != end )
	{
		Policy::accumulate( total, *beg );
		++beg;
	}

	return total;
}
```
- SumPolicy는 다음과 같이 작성할 수 있다.
```c++
// TAPC_06.cpp
class SumPolicy
{
public:
	template<typename T1, typename T2>
	static void accumulate( T1& total, const T2& value )
	{
		total += value;
	}
};
```
- 값을 축적하는 방식에 다른 정책을 명시함으로써 다양한 계산이 가능하게 됐다. 예를 들어 값들의 곱을 결정하는 다음 프로그램을 살펴보자.
```c++
// TAPC_06.cpp
class MultPolicy
{
public:
	template <typename T1, typename T2>
	static void accumulate( T1& total, const T2& value )
	{
		total *= value;
	}
};

int main( )
{
	int num[] = { 1, 2, 3, 4, 5 };

	std::cout << "모든 값의 곱을 출력 :"
		<< accum<int, MultPolicy>( &num[0], &num[5] )
		<< std::endl;
}
```
- 하지만 이 프로그램의 출력은 원했던 값이 아니다.
```
모든 값의 곱을 출력 :0
```
- 여기서의 문제는 선택된 초깃값에 있다. 덧셈에서는 0으로 초기화돼야 했지만 곱셈에서는 0이어선 안된다. 다양한 특실과 정책이 상호 작용할 수 있으므로 템플릿 설계가 얼마나 중요한지 알 수 있다.
- 위의 경우에는 축적 루프의 초기화가 축적 정책의 일부라고 생각할 수 있다. 이 정책은 zero() 특질을 사용할 수도 있고 사용하지 않을 수도 있다. 모든 것을 특질과 정책으로만 해결해야 하는 건 아니다. 예를 들어 C++ 표준 라이브러리의 accumulate() 함수는 초깃값을 세번째 인자로 받는다.
```c++
template<class _InIt,
	class _Ty> inline
	_Ty accumulate(_InIt _First, _InIt _Last, _Ty _Val)
	{	// return sum of _Val and all in [_First, _Last)
	return (_STD accumulate(_First, _Last, _Val, plus<>()));
	}
```

### 특질과 정책의 차이점
- 정책은 특질의 특별한 사용법이라고 말할 수도 있다. 역으로 특질은 정책을 인코딩했을 뿐이라고 표현할 수도 있다.
- 정책은 특질과 여러모로 유사하지만 이들은 데이터형보다는 좀 더 행위에 초점을 맞춘다.
- 일반적으로 다음 정의가 사용된다.
	- 특질은 템플릿 파라미터에 자연스럽게 추가된 속성을 나타낸다.
	- 정책은 일반 함수와 데이터형에 따라 구성될 수 있는 행위를 나타낸다.
- 두 개념 사이의 차이점을 좀 더 알아보기 위해 특질과 관련된 관찰 사항을 나열하면 다음과 같다.
	- 특질 파라미터는 대부분 매우 자연스러운 기본값을 가진다.
	- 특질 파라미터는 하나 이상의 주요 파라미터와 긴밀히 종속돼 있곤 하다.
	- 특질은 멤버 함수보다는 데이터형이나 상수와 결합된다.
	- 특질은 특질 템플릿으로 모아지곤 한다.
- 정책 클래스의 경우 다음과 같은 경향을 살펴볼 수 있다.
	- 정책 클래스는 템플릿 파라미터로 전달되지 않을 경우 크게 기여하는 바가 없다.
	- 정책 파라미터는 기본값을 가질 필요가 없으며 일반적으로 외부에서 명시된다.
	- 정책 파라미터는 템플릿의 다른 파라미터와 크게 관련이 없다.
	- 정책 클래스는 대체로 멤버 함수와 결합한다.
	- 정책은 일반 클래스나 클래스 템플릿으로 모을 수 있다.
- 하지만 두 용어 사이의 경계선은 뚜렸하지 않다. 예를 들어 C++ 표준 라이브러리의 문자 특질은 비교, 이동 찾기 등과 같은 기능적 행위도 정의한다. 이런 특질을 치환함으로써 같은 문자 데이터형은 유지하면서 대소문자를 가리지 않는 문자열 클래스를 정의할 수 있다. 이들이 특질이라고 불리기는 하지만 정책과 관련된 속성을 갖는다.

### 멤버 템플릿과 템플릿 템플릿 파라미터
- 축적 정책을 구현하기 위해 SumPolicy와 MultPolicy를 멤버 템플릿을 갖는 일반 클래스로 표현했다. 이와 달리 클래스 템플릿을 사용해 정책 클래스 인터페이스를 설계해 템플릿 템플릿 인자를 사용하게 할 수도 있다.
> 특질 파라미터에도 같은 변환이 적용될 수 있다.

```c++
// TAPC_07.cpp
template <typename T1, typename T2>
class SumPolicy
{
public:
	static void accumulate( T1& total, const T2& value )
	{
		total += value;
	}
};

template <typename T,
	template<typename, typename> class Policy = SumPolicy,
	typename Traits = AccumulationTraits<T>>
	inline typename Traits::AccT accum( const T* beg, const T* end )
{
	using AccT = typename Traits::AccT;
	AccT total = Traits::zero( );
	while ( beg != end )
	{
		Policy<AccT, T>::accumulate( total, *beg );
		++beg;
	}

	return total;
}
```
- 정책 클래스를 템플릿 템플릿 파라미터로 접근하는 것에 따른 가장 큰 장점은 템플릿 파라미터에 종속된 데이터형을 갖는 상태 정보를 정책 클래스 내에 갖기 쉽다는 점이다.
> 첫 번째 접근 방식에서 정적 데이터 멤버는 멤버 클래스 템플릿 내에 내장돼야만 했다.

- 하지만 템플릿 템플릿 파라미터 접근 방식은 정책 클래스가 템플릿이므로 인터페이스에 따라 정확한 템플릿 파라미터를 갖도록 작성돼야 한다는 단점을 갖는다. 불행히도 이 경우에는 정책이 부가적인 템플릿 파라미터를 가질 수 없다. 
- 예를 들어 데이터형이 아닌 불리언 템플릿 파라미터를 SumPolicy에 추가해 더하기가 += 연산자로 이뤄질지 아니면 +만을 사용할지 선택하게 만들고 싶을 수 있다. 멤버 템플릿을 사용하는 프로그램에서는 SumPolicy를 템플릿으로 쉽게 재작성할 수 있다.
```c++
// TAPC_07.cpp
template <bool use_compound_op = true>
class SumPolicy
{
public:
	template <typename T1, typename T2>
	static void accumulate( T1& total, const T2& value )
	{
		total += value;
	}
};

template <>
class SumPolicy<false>
{
public:
	template <typename T1, typename T2>
	static void accumulate( T1& total, const T2& value )
	{
		total = total + value;
	}
};
```
- 템플릿 템플릿 파라미터를 사용해 accum을 구현하면 위와 같이 변경할 수 없다.

### 다양한 정책과 특질 결합
- 이제까지 특질과 정책을 사용한다 해도 여러 템플릿 파라미터를 가져야 하는 상황을 완전히 제거하지는 못했다. 하지만 이들을 사용함으로써 파라미터의 수를 사용자가 충분히 관리할 수 있을 정도로 줄일 수 있었다. 그러고 나면 여러 파라미터를 어떤 방식으로 나열할 것인가라는 문제가 발생한다.
- 간단하게 기본값이 선택될 확률에 따라 파라미터를 정렬할 수 있다. 일반적으로 특질 파라미터는 정책 파라미터 뒤를 따르게 될 것인데 정책 파라미터는 클라이언트 코드에서 좀 더 자주 덮어써지기 때문이다.
- 코드의 복잡도를 감수할 수 있다면 기본값이 없는 인자를 어떤 순서로든 명시할 수 있다.

### 일반 반복자를 통해 추적
- 특질과 정책에 대한 소개를 끝내기 전에 일반화된 반복자를 다룰 수 있는 능력을 추가해보자.
```c++
// TAPC_08.cpp
template <typename Iter>
inline typename std::iterator_traits<Iter>::value_type accum( Iter start, Iter end )
{
	using VT = typename std::iterator_traits<Iter>::value_type;

	VT total = VT( );
	while ( start != end )
	{
		total += *start;
		++start;
	}

	return total;
}
```
- iterator_traits 구조는 반복자의 관련 속성을 모두 캡슐화한다. 포인터를 위한 부분 특수화가 존재하므로 이런 특질은 어떤 일반 포인터에서도 쉽게 사용될 수 있다.
```c++
template<class _Ty>
	struct iterator_traits<_Ty *>
	{	// get traits from pointer
	typedef random_access_iterator_tag iterator_category;
	typedef _Ty value_type;
	typedef ptrdiff_t difference_type;

	typedef _Ty *pointer;
	typedef _Ty& reference;
	};
```
- 하지만 반복자가 참조하는 값의 축적을 위한 데이터형이 제시되어 있지 않으므로 자신만의 AccumulationTraits를 설계해야만 한다.

## 데이터형 상수
- C와 C++함수는 값 함수(value function)다. 이들은 특정 값을 파라미터로 받아서 또 다른 값을 결과로 반환한다. 하지만 템플릿을 사용하면 데이터형 함수를 정의할 수 있다. 데이터형 함수는 데이터형 인자를 받아 결과로 데이터형이나 상수를 생성한다.
- 가장 유용한 내장 데이터형 함수로는 sizeof를 들 수 있는데 이 함수는 주어진 데이터형 인자의 크기를 나타내는 상수 값을 반환한다.
- 클래스 템플릿을 이런 데이터형 함수로 사용할 수 있다. 템플릿 파라미터는 이런 데이터형 함수의 파라미터가 될 것이고 그 결과는 멤버 데이터형이나 멤버 상수에서 얻을 수 있다. 예를 들어 sizeof 연산자는 다음과 같은 인터페이스를 가질 수 있다.
```c++
// TAPC_09.cpp
#include <cstddef>
#include <iostream>

template <typename T>
class TypeSize
{
public:
	static const size_t value = sizeof( T );
};

int main( )
{
	std::cout << "TypeSize<int>::value = "
			  << TypeSize<int>::value << std::endl;
}
```
- 이런 방식의 특질 클래스로 사용될 수 있는 좀 더 일반적인 목적의 데이터형 함수를 살펴보자.

### 요소의 데이터형 결정
- vector\<T\>, list\<\>나 stack\<T\>과 같은 컨테이너 템플릿을 여러 개 가지고 있다고 가정해보자. 주어진 컨테이너형에서 요소의 데이터형을 생성하는 데이터형 함수를 원한다고 해보자. 이 테이터형 함수는 부분 특수화를 통해 구현될 수 있다.
```c++
// TAPC_10.cpp
#include <vector>
#include <list>
#include <stack>
#include <iostream>

template <typename T>
class ElementT;

template <typename T>
class ElementT<std::vector<T>>
{
public:
	using Type = T;
};

template <typename T>
class ElementT<std::list <T>>
{
public:
	using Type = T;
};

template <typename T>
class ElementT<std::stack<T>>
{
public:
	using Type = T;
};

template <typename T>
void print_element_type( const T& c )
{
	std::cout << "Container of "
			  << typeid( typename ElementT<T>::Type ).name( )
			  << " elements." << std::endl;
}

int main( )
{
	std::stack<bool> s;
	print_element_type( s );
}
```
- 부분 특수화를 사용함으로써 컨테이너형이 데이터형 함수를 알지 못하더라도 데이터형 함수를 구현할 수 있다. 하지만 대개 데이터형 함수를 적용된 데이터형과 함께 설계함으로써 데이터형 함수 구현을 간단하게 한다. 예를 들어 컨테이너 형이 value_type이라는 멤버형을 정의한다면 다음과 같이 작성할 수 있다.
```c++
// TAPC_10.cpp
template <typename C>
class ElementT
{
public:
	using Type = typename C::value_type;
};
```
- 위 멤버형은 기본 구현이 될 수 있으며 적절한 value_type라는 멤버형이 정의되지 않은 컨테이너형에 대한 특수화를 배제하지도 않는다. 그런데도 템플릿형 파라미터를 위해 데이터형 정의를 제공하는 편이 일반 코드에서 더 쉽게 접근할 수 있다.
- 데이터형 함수는 템플릿을 컨테이너형에 따라 파라미터화할 수 있게 하되 요소의 데이터형을 위한 파라미터나 다른 특징을 요구하지 않는다. 예를 들어 다음의 코드는 sum\_of\_element\<int>\(list)와 같은 문법을 사용해 요소의 데이터형을 명시하게 하였다. 그러나 다음 코드처럼 선언할 수 있다.
```c++
template <typename T, typename C>
T sum_of_elements( const C& c );

template <typename C>
typename ElementT<C>::Type sum_of_elements( const C& c );
```
- 요소의 데이터형이 데이터형 함수로 결정된다. 이 경우 주어진 데이터형 C의 특질에 접근하는 데 사용되기 때문에 ElementT형은 특질 클래스라 불린다. 따라서 특질 클래스는 컨테이너 파라미터만이 아니라 특정한 주요 파라미터의 특성을 설명하는 데 사용된다.
- 특질은 현존하는 데이터형에 대한 확장으로 구현될 수 있다. 따라서 기본형이나 닫힌 라이브러리의 데이터형에 대해서도 이런 데이터형 함수를 정의할 수 있다.

### 클래스형 결정
- 다음 데이터형 함수로 데이터형이 클래스형인지 결정할 수 있다.
```c++
// TAPC_11.cpp
template <typename T>
class IsClassT
{
private:
	using One = char;
	using Two = struct { char a[2]; };
	template <typename C> static One test( int C::* );
	template <typename C> static Two test( ... );
public:
	enum { Yes = sizeof( IsClassT<T>::test<T>( 0 ) ) == 1 };
	enum { No = !Yes };
};
```
- 이 템플릿은 SFINAE(substitution-failure-is-not-an-error) 법칙을 사용한다. 여기서 SFINAE를 활용할 때 중요한 것은 클래스형에서는 유효하지 않지만 다른 데이터형에서는 유효하거나 그 반대인 경우를 찾는 것이다. 다음 프로그램은 이 데이터형 함수를 사용해 특정 데이터형과 클래스형이 아닌지 알아본다.
```c++
// TAPC_11.cpp
class MyClass {};

struct MyStruct {};

union MyUnion {};

void myfunc( ) {}

enum E { e1 } e;

template <typename T>
void check( )
{
	if ( IsClassT<T>::Yes )
	{
		std::cout << " IsClassT " << std::endl;
	}
	else
	{
		std::cout << " !IsClassT " << std::endl;
	}
}

template <typename T>
void checkT( T )
{
	check<T>( );
}

int main()
{
	std::cout << "int: ";
	check<int>( );

	std::cout << "MyClass: ";
	check<MyClass>( );
	std::cout << "MyStruct: ";
	MyStruct s;
	checkT( s );

	std::cout << "MyUnion: ";
	check<MyUnion>( );

	std::cout << "enum: ";
	checkT( e );

	std::cout << "myfunc(): ";
	checkT( myfunc );
}
```
- 이 프로그램의 출력은 다음과 같다.
```
int:  !IsClassT
MyClass:  IsClassT
MyStruct:  IsClassT
MyUnion:  IsClassT
enum:  !IsClassT
myfunc():  !IsClassT
```

### 참조자와 한정자
- 먼저 다음과 같은 코드를 살펴보자.
```c++
// TAPC_12.cpp
#include <iostream>

template <typename T>
void apply( T& arg, void( *func )( T ) )
{
	func( arg );
}

void incr( int& a )
{
	++a;
}

void print( int a )
{
	std::cout << a << std::endl;
}

int main( )
{
	int x = 7;
	apply( x, print );
	apply( x, incr );
}
```
- apply( x, print ) 호출은 T를 int로 치환해 int&와 void(*)(int)로 대응되어 문제가 없다.
- apply( x, incr ) 는 문제가 되는데 두 번째 파라미터를 일치시키기 위해서는 T를 int&로 치환해야 하고 그러면 첫 번째 파라미터형은 int& & 이어야 하는데 이는 C++의 유효한 데이터형이 아니지만 템플릿이나 typedef에서 참조 붕괴(Reference collapsing)라고 하는 특별한 법칙이 적용된다. _rvalue 참조에 대한 rvalue 참조는 붕괴되어 rvalue 참조가 되며 다른 모든 조합은 lvalue 참조가 된다._ 다음 예제 코드를 살펴보자.
```c++
typedef int& lref;
typedef int&& rref;
int n;
lref& r1 = n;		// int&
lref&& r2 = n;		// int&
rref& r3 = n;		// int&
rref&& r4 = 1;		// int&
```
> 하지만 apply( x, incr )는 빌드가 되지 않는데 이는 첫 번째 인자의 T가 int나 int&로 치환될 수 있는 반면 두 번째 인자는 int&로만 치환될 수 있기 때문이다. 파라미터 쌍은 독립적으로 분석되고 끝에 가서 결과가 일치하지 않으면 추론이 실패하는데 이 경우가 그에 해당한다.

- 위 코드의 문제를 해결하기 위해서 주어진 데이터형이 참조자가 아닐 경우에만 참조 연산자를 적용하는 데이터형 함수를 생성해보자. 다음 일반 정의의 부분 특수화를 사용함으로써 const 한정자를 처리할 수 있다.
```c++
// TAPC_13.cpp
template <typename T>
class TypeOp
{
public:
	using ArgT = T;
	using BareT = T;
	using ConstT = const T;
	using RefT = T&;
	using RefBareT = T&;
	using RefConstT = const T&;
};
```
- const 데이터형을 알아내는 부분 특수화는 다음과 같다.
```c++
// TAPC_13.cpp
template <typename T>
class TypeOp<const T>
{
public:
	using ArgT = const T;
	using BareT = T;
	using ConstT = const T;
	using RefT = const T&;
	using RefBareT = T&;
	using RefConstT = const T&;
};
```
- 참조자 데이터형을 알아내는 부분 특수화는 const 데이터형에 대한 참조자도 잡아낸다. 또한, 필요하다면 실제 데이터형을 얻기 위해 TypeOp장치를 재귀적으로 적용한다.
- 또한, C++은 이미 const인 데이터형으로 치환된 템플릿 파라미터에 또다시 const 한정자를 적용하는 것을 허용하므로 이전 const 한정자를 제거해야 하는지 걱정할 필요가 없다.
```c++
// TAPC_13.cpp
template <typename T>
class TypeOp<T&>
{
public:
	using ArgT = const T&;
	using BareT = typename TypeOp<T>::BareT;
	using ConstT = const T;
	using RefT = T&;
	using RefBareT = typename TypeOp<T>::BareT&;
	using RefConstT = const T&;
};
```
- void 타입은 참조자가 허용되지 않기 때문에 완전 특수화를 통해 처리해준다.
```c++
// TAPC_13.cpp
template <>
class TypeOp<void>
{
public:
	using ArgT = void;
	using BareT = void;
	using ConstT = const void;
	using RefT = void;
	using RefBareT = void;
	using RefConstT = void;
};
```
- TypeOp을 이용하여 apply( ) 함수를 다음과 같이 바꿀 수 있다.
```c++
// TAPC_13.cpp
template <typename T>
void apply( typename TypeOp<T>::RefT arg, void( *func )( T ) )
{
	func( arg );
}
```
- 이제 의도대로 잘 동작한다. 첫 번째 인자의 T는 한정자 내에 나타나기 떄문에 추론될 수 없는 문맥이다. 따라서 T는 두 번째 인자에서만 추론되고 추론된 T로 첫 번째 인자의 데이터형을 결정하는 데 사용한다.

## 데이터형 승격 특질
- 지금까지는 한 데이터형의 데이터형 함수를 알아보았다. 하지만 일반적으로는 다양한 인자에 종속되는 데이터형 함수를 개발할 수 있다. 연산자 템플릿을 작성할 때 매우 유용하게 쓰이는 데이터형 승격 특질이라 불리는 연산자 템플릿을 살펴보자. 다음과 같이 두 std::array 컨테이너를 더하는 함수 템플릿을 생각해보자.
```c++
template <typename T1, typename T2>
std::array<???> operator+( const std::array<T1>&, const std::array<T2>& )
```
- 위와 같이 혼합된 데이터형을 연산한다면 반환형을 무엇으로 할 것인가라는 문제가 발생한다. 데이터형 승격 특질은 앞과 같은 문제의 답을 다음과 같이 제공한다.
```c++
// TAPC_14.cpp
template <typename T1, typename T2, int N>
std::array<typename Promotion<T1, T2>::ResultT, N>, std::array<T2, N>>::ResultT operator+( const std::array<T1, N>&, const std::array<T2, N>& )

// 혹은

template <typename T1, typename T2, int N>
typename Promotion<std::array<T1, N>, std::array<T2, N>>::ResultT operator+( const std::array<T1, N>&, const std::array<T2, N>& )
```
- 여기서의 아이디어는 템플릿 Promotion의 특수화를 다수 제공하여 원하는 데이터형 함수를 생성하자는 것이다. 이 템플릿에 대한 정말 안정적인 일반 정의는 없으므로 기본 클래스 템플릿은 정의하지 않는다.
```c++
// TAPC_14.cpp
template <typename T1, typename T2>
class Promotion;
```
- 적절한 반환형을 선택하기 위해 데이터형 중 하나가 다른 것보다 크다고 가정하고 더 큰 데이터형으로 데이터형을 승격하도록 해보자. 이 방식은 두 데이터형 파라미터 중 하나를 선택하기 위해 bool형의 값을 템플릿 파라미터로 받는 특별한 템플릿인 IfThenElse를 사용한다.
```c++
// TAPC_14.cpp
template <bool C, typename Ta, typename Tb>
class IfThenElse;

template <true, typename Ta, typename Tb>
class IfThenElse
{
public:
	using ResultT = Ta;
};

template <false, typename Ta, typename Tb>
class IfThenElse
{
public:
	using ResultT = Tb;
};
```
- IfThenElse를 사용하면 데이터형 승격이 필요한 데이터형들의 크기에 따라 T1, T2와 void 중 하나를 선택할 수 있다.
```c++
// TAPC_14.cpp
template <typename T1, typename T2>
class Promotion
{
public:
	using ResultT = typename IfThenElse<( sizeof( T1 ) > sizeof( T2 ) ),
										T1,
										typename IfThenElse<( sizeof( T1 ) < sizeof( T2 ) ), T2, void>::ResultT
										>::ResultT;
};
```
- 크기 기반 선택 방식은 어떤 때에는 잘 동작할 수 있지만 검사해볼 필요가 있다. 잘못된 데이터형을 선택했다면 적절한 특수화를 통해 이 선택 방식을 덮어쓸 필요가 있다.
- 두 데이터형이 같다면 해당 데이터형을 올바른 반환형으로 생각할 수 있다. 부분 특수화를 통해 이를 처리하면 다음과 같다.
```c++
// TAPC_14.cpp
template <typename T, typename T>
class Promotion
{
public:
	using ResultT = T;
};
```
- 기초 데이터형의 데이터형 승격을 기록하려면 많은 특수화가 필요하다. 매크로를 사용한다면 소스 코드의 크기를 어느 정도 줄일 수 있다.
```c++
// TAPC_14.cpp
#define MK_PROMOTION( T1, T2, Tr )			\
template <> class Promotion<T1, T2>			\
{											\
public:										\
	using ResultT = Tr;						\
};											\
											\
template <> class Promotion<T2, T1>			\
{											\
public:										\
	using ResultT = Tr;						\
};											\

MK_PROMOTION( bool, char, int )
MK_PROMOTION( bool, unsigned char, int )
MK_PROMOTION( bool, signed char, int )
```
- 이런 접근 방식은 직관적이지만 수많은 조합이 열거돼야 한다. 이외에도 다른 방식들을 사용할 수 있는데 type_trait 헤더의 데이터형 함수를 이용하여 정수형 혹은 부동소수점형을 위한 데이터형 승격을 정의할 수 있다.
- Promotion이 기초 데이터형에 대해 정의되면 다른 데이터형 승격 법칙은 부분 특수화를 통해 표현될 수 있다. std::array 예제를 통해 살펴보면 다음과 같이 작성할 수 있다.
```c++
template <typename T1, typename T2, int N>
class Promotion<std::array<T1, N>, std::array<T2, N>>
{
public:
	using ResultT = std::array<typename Promotion<T1, T2>::ResultT, N>;
};
```

## 정책 특질
- 지금까지의 특질 템플릿의 예는 템플릿 파라미터의 속성을 결정하기 위해 사용됐다. 데이터형의 종류는 무엇인지, 혼합된 데이터형 연산에서 어떤 데이터형으로 데이터형을 승격할지 등을 결정해야 했다. 이런 특질을 속성 특질( property trait )라고 부른다.
- 정책 특질( policy trait )은 특정 데이터형을 어떻게 취급해야 하는지를 정의한다. 이는 앞서 알아본 정책 클래스의 개념과 유사하다. 하지만 정책 특질은 템플릿 파라미터와 관련된 고유한 속성을 갖는 경향이 있다.
- 속성 특질은 데이터형 함수로 구현될 수 있는데 정책 특질은 일반적으로 멤버 함수 내에 정책으로 캡슐화된다.

### 읽기 전용 파라미터형
- C와 C++에서 함수 호출 인자는 기본적으로 **값으로** 전달된다. 따라서 큰 구조체를 인자로 전달하면 함수 호출 비용이 매우 비싸지기 때문에 const  참조자로 인자를 넘긴다.
- 작은 구조체라면 값으로 전달하는 것과 참조자로 전달하는 것 중 어떤 것이 더 나은지 명확하지 않다.
- 템플릿을 사용하면 좀 더 처리하기 까다로운데 템플릿 파라미터로 치환될 데이터형이 얼마나 클지 예상할 수 없기 때문이다. 이 문제는 데이터형 함수인 정책 특질 템플릿을 사용해 편리하게 해결할 수 있다.
```c++
// TAPC_15.cpp
template <typename T>
class RParam
{
public:
	using Type = typename std::conditional<sizeof( T ) <= 2 * sizeof( void* ), T, const T&>::type;
};
```
- 기본 템플릿은 void* 크기의 2배보다 크지 않은 데이터형은 값으로 넘기고 나머지는 const 참조자로 넘기게 하였다. 한편 sizeof가 작은 값을 반환하더라도 컨테이너형의 복사 비용은 매우 클 수 있다. 따라서 다음과 같은 부분 특수화가 필요하다.
```c++
// TAPC_15.cpp
template <typename T, int N>
class RParam<std::array<T, N>>
{
public:
	using Type = const T&;
};
```
- 이어서 RParam이 실제로 사용되는 예제를 살펴보자
```c++
// TAPC_15.cpp
class MyClass1
{
public:
	MyClass1( ) = default;
	MyClass1( const MyClass1& )
	{
		std::cout << "MyClass1 copy constructor called\n" << std::endl;
	}
};

class MyClass2
{
public:
	MyClass2( ) = default;
	MyClass2( const MyClass2& )
	{
		std::cout << "MyClass2 copy constructor called\n" << std::endl;
	}
};

template <>
class RParam<MyClass2>
{
public:
	using Type = MyClass2;
};

template <typename T1, typename T2>
void foo( typename RParam<T1>::Type p1, typename RParam<T2>::Type p2 )
{

}

int main( )
{
	MyClass1 m1;
	MyClass2 m2;
	foo<MyClass1, MyClass2>( m1, m2 );
}
```
- 안타깝게도 RParam에는 몇 가지 중요한 단점이 있다.
	1\. 함수 선언이 지저분해진다.
	2\. 템플릿 파라미터가 함수 파라미터의 한정자에만 나타나기 때문에 인자 추론을 사용할 수 없다.

- 이런 문제를 해결하기 위해 인라인 래퍼 함수 템플릿을 쓰는 방법도 있다.
```c++
// TAPC_15.cpp
template <typename T1, typename T2>
void foo_wrapper( T1 p1, T2 p2 )
{
	foo<T1, T2>( p1, p2 );
}

int main( )
{
	// ...
	foo_wrapper( m1, m2 );
}
```

### 복사, 교환과 이동
- 성능을 개선하기 위해 특정 데이터형의 요소를 복사, 교환, 이동하기 위한 최적의 연산을 선택하는 정책 특질 템플릿을 도입할 수 있다.
- 주어진 데이터형의 아이템을 대량으로 복사할 때에는 해당 데이터형의 생성자나 할당 연산자를 지속적으로 호출하는 것보다 더 효율적인 방법이 있을 수 있다.
> 이와 유사하게 특정 데이터형의 경우 고전적인 방식보다 더 효율적으로 교환하거나 이동할 방법이 있을 수 있다.

- 이 분야에 관련된 결정 사항들은 편의상 특질 템플릿에 모아놓는 편이 좋다. 코드를 통해 알아보자.
```c++
// TAPC_16.cpp
#include <type_traits>

template <typename T>
class RParam
{
public:
	using Type = typename std::conditional<sizeof( T ) <= 2 * sizeof( void* ), T, const T&>::type;
};

template <typename T, bool Bitwise>
class BitOrClassCSM;

template <typename T>
class BitOrClassCSM<T, false>
{
public:
	static void copy( typename RParam<T>::Type src, T* dat )
	{
		*dst = src;
	}

	static void copy_n( const T* src, T* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k)
			dst[k ) = src[k];
	}

	static void copy_init( typename RParam<T>::Type src, void* dst )
	{
		::new( dst ) T( *src );
	}

	static void copy_init_n( const T* src, void* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
			::new( (void*)((T*)dst+k) ) T( src[k] );
	}

	static void swap( T* a, T* b )
	{
		T tmp( *a );
		*a = *b;
		*b = tmp;
	}

	static void swap( T* a, T* b, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
		{
			T tmp( a[k] );
			a[k] = b[k];
			b[k] = tmp;
		}
	}

	static void move( T* src, T* dst )
	{
		*dst = *src;
		src->~T( );
	}

	static void move_n( T* src, T* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
		{
			dst[k] = src[k];
			src[k].~T( );
		}
	}

	static void move_init( T* src, T* dst )
	{
		::new( dst ) T( *src );
		src->~T( );
	}

	static void move_init_n( T* src, T* dst, size_t n )
	{
		for ( size_t k = 0; k < n; ++k )
		{
			::new( (void*)( (T*)dst + k ) ) T( src[k] );
			src[k].~T( );
		}
	}
};
```
- 정책 특질 템플릿의 멤버 함수는 모두 정적 함수다. 멤버 함수는 특질 클래스형의 객체가 아닌 파라미터형의 객체에 적용되기 때문에 거의 항상 정적 함수로 선언된다.
- 복사할 수 있는 비트 단위 데이터형을 위한 특질을 구현하는 부분 특수화를 살펴보자.
```c++
// TAPC_16.cpp
template <typename T>
class BitOrClassCSM<T, true> : public BitOrClassCSM<T, false>
{
public:
	static void copy_n( const T* src, T* dst, size_t n )
	{
		std::memcpy( (void*)dst, (void*)src, n * sizeof( T ) );
	}

	static void copy_init_n( const T* src, T* dst, size_t n )
	{
		std::memcpy( dst, (void*)src, n * sizeof( T ) );
	}

	static void move_n( T* src, T* dst, size_t n )
	{
		std::memcpy( (void*)dst, (void*)src, n * sizeof( T ) );
	}

	static void move_init_n( const T* src, T* dst, size_t n )
	{
		std::memcpy( dst, (void*)src, n * sizeof( T ) );
	}
};
```
- 복사할 수 있는 비트 단위 데이터형을 위한 특질의 구현을 간단하게 하려고 또 다른 수준의 상속을 추가했다. 이런 방식으로만 구현할 수 있는 것은 아니며 특정 플랫폼에서는 인라인 어셈블리를 도입하는 쪽이 더 나을 수 있다.
