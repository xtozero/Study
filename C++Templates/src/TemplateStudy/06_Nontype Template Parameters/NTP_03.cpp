template <typename T, int N>
class IntegralArithmetic {};

int main( )
{
	// 정수이고 산술 타입인 경우
	IntegralArithmetic<int, 10> intLiteral;

	// int n = 10;
	// IntegralArithmetic<int, n> intVariable;

	const int cn = 10;
	IntegralArithmetic<int, cn> constInt;
}