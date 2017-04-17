template <typename T>
class Trap
{
public:
	enum { x }; // x는 데이터형이 아님
};

template <typename T>
class Victim
{
public:
	int y;
	void proof( )
	{
		Trap<T>::x* y; // 선언? 곱셈?
	}
};

template <>
class Trap<void>
{
public:
	typedef int x; // 여기서 x가 데이터형
};

void boom( Victim<void>& bomb )
{
	bomb.proof( );
}

int main( )
{
	Victim<void> bomb;
	boom( bomb );
}