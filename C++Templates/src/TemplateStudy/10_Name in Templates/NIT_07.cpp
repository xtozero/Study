template <bool B>
class Invert
{
public:
	static const bool result = !B;
};

void g( )
{
	bool test = Invert<(1>0)> ::result; // ��ȣ�� �ʿ�
}