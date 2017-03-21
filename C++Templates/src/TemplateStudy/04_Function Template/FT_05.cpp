template <typename T>
void CallByForwardReference( T&& param ) {}

int main( )
{
	int x = 27;
	int& rx = x;
	const int cx = x;
	const int& crx = x;

	// T&& ÀÎ °æ¿ì
	CallByForwardReference( x );		// T: int& ParamType : int&
	CallByForwardReference( rx );		// T: int& ParamType : int&
	CallByForwardReference( cx );		// T: const int&, ParamType : const int&
	CallByForwardReference( crx );		// T: const int&, ParamType : const int&
	CallByForwardReference( 27 );		// T: int, ParamType : int&&
}