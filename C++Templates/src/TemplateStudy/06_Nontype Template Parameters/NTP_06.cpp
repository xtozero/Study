template <int& N>
class LvalueReference {};

int Foo( ) { return 1; }
int gn = 0;

int main( )
{
	// lvalue ������ ���
	// LvalueReference<Foo( )> FunctionReturn;

	// int n;
	// LvalueReference<n> Nolinkage;
	LvalueReference<gn> linkage;
}