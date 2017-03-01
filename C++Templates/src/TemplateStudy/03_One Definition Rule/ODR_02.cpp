namespace A
{
	namespace B
	{
		void Foo( ) {}
	}
}

int main( )
{
	namespace AB = A::B;
	// namespace AB = A;

	AB::Foo( );
	A::B::Foo( );
}