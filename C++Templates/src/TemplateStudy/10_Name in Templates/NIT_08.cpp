template <typename T>
class Trap
{
public:
	enum { x }; // x�� ���������� �ƴ�
};

template <typename T>
class Victim
{
public:
	int y;
	void proof( )
	{
		Trap<T>::x* y; // ����? ����?
	}
};

template <>
class Trap<void>
{
public:
	typedef int x; // ���⼭ x�� ��������
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