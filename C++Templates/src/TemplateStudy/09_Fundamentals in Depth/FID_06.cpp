// template <typename T1 = char, typename T2, typename T3, typename T4, typename T5> // error �Լ��� �⺻���ڿ� ���������̴�.
// class Test;

template <typename T1, typename T2, typename T3, typename T4 = char, typename T5 = char>
class Quintuple;

template <typename T1, typename T2, typename T3 = char, typename T4, typename T5> // ok T4�� T5�� �̹� �⺻���� ������ �ִ�.
class Quintuple;

template <typename T1, typename T2 = void>
class Value;

template <typename T1, typename T2 = void> // error ������ �⺻ ���ڸ� �ݺ��ؼ� ������ �� ����.
class Value;

int main( )
{
}