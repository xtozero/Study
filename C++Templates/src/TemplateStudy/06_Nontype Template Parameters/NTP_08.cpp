#include <string>

// 실수형은 불가
template <double VAT>
double process( double v )
{
	return v * VAT;
}

// 클래스형 객체는 불가
template <std::string name>
class MyClass {};

int main( )
{
}