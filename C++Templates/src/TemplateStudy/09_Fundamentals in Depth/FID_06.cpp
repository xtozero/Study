// template <typename T1 = char, typename T2, typename T3, typename T4, typename T5> // error 함수의 기본인자와 마찬가지이다.
// class Test;

template <typename T1, typename T2, typename T3, typename T4 = char, typename T5 = char>
class Quintuple;

template <typename T1, typename T2, typename T3 = char, typename T4, typename T5> // ok T4와 T5는 이미 기본값을 가지고 있다.
class Quintuple;

template <typename T1, typename T2 = void>
class Value;

template <typename T1, typename T2 = void> // error 하지만 기본 인자를 반복해서 선언할 순 없다.
class Value;

int main( )
{
}