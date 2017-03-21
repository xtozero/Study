template <typename T>
void CallByValue( T param ) {}

class TypeDeduction
{
public:
	mutable int m_value;
};

int main( )
{
	int x = 27;
	int& rx = x;
	const int cx = x;
	const int& crx = x;

	// TÀÎ °æ¿ì
	CallByValue( x );		// T: int ParamType : int
	CallByValue( rx );		// T: int ParamType : int
	CallByValue( cx );		// T: int, ParamType : int
	CallByValue( crx );		// T: int, ParamType : int

	TypeDeduction t = { 0 };
	auto deducted = t.m_value; // T: int ParamType : int
}
