template <typename T, int N>
class IntegralArithmetic {};

int main( )
{
	// �����̰� ��� Ÿ���� ���
	IntegralArithmetic<int, 10> intLiteral;

	// int n = 10;
	// IntegralArithmetic<int, n> intVariable;

	const int cn = 10;
	IntegralArithmetic<int, cn> constInt;
}