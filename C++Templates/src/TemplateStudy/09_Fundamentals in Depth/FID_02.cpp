template <typename T>
class Dynamic
{
public:
	virtual ~Dynamic( ) {} // ok Dynamic<T> �� �ϳ��� �Ҹ���
	template <typename T2>
	virtual void copy( const T2& ) {} // error Dynamic<T>�� �ν��Ͻ� ������ copy() �ν��Ͻ��� ���� ������ �� �����Ƿ�
};

int main( )
{

}