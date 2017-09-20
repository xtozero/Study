template <int X, int N>
class Pow
{
public:
	enum { result = X * Pow<X, N - 1>::result };
};

template <int X>
class Pow<X, 0>
{
public:
	enum { result = 1 };
};

int main( )
{
	Pow<2, 3>::result;
}