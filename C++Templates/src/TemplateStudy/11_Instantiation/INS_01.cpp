template <typename T> class C;	// ����

C<int>* p = 0;					// ok ���ǰ� �ʿ����� ����.

template <typename T>
class C
{
public:
	C( int );
	void f( );					// ��� ����
};								// ���ø� ����

void g( C<int>& c )				// Ŭ���� ���ø� ���� ����.
{
	// c.f( );						// Ŭ���� ���ø� ��� �Լ��� ���ǰ� ����.
}

void candidate( const C<double>& );	// #1
void candidate( int ) {}			// #2

int main( )
{
	// C<void>* cVoid = new C<void>;
	candidate( 42 );
}