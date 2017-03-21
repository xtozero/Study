template <typename T>
void CallByReference( T& param ) {}

int main( )
{
	int x = 27;
	int& rx = x;
	const int cx = x;
	const int& crx = x;

	CallByReference( x );		// T: int ParamType : int&
	CallByReference( rx );		// T: int ParamType : int&
	CallByReference( cx );		// T: const int, ParamType : const int&
	CallByReference( crx );		// T: const int, ParamType : const int&
}