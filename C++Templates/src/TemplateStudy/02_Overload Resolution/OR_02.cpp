void Ambiguous( long ) {}
void Ambiguous( double ) {}

int main( )
{
	Ambiguous( 1 ); // error 후보가 여러개 있어 모호한 호출
}