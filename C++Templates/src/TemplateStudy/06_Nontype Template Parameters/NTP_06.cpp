template <int& N>
class LvalueReference {};

int Foo( ) { return 1; }
int gn = 0;

int main( )
{
	// lvalue 참조일 경우
	// LvalueReference<Foo( )> FunctionReturn;

	// int n;
	// LvalueReference<n> Nolinkage;
	LvalueReference<gn> linkage;
}