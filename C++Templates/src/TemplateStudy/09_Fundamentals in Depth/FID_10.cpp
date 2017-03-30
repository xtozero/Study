template <typename T> class List
{
	// ...
};

typedef struct
{
	double x, y, z;
} Point;

typedef enum { red, green, blue } *ColorPtr;

template <typename T>
void clear( T p )
{
	*p = 0;
}

int main( )
{
	struct Association
	{
		int* p;
		int* q;
	};

	List<Association*> error1;	// error ���ø� ���ڰ� ���� ��������
	List<ColorPtr> error2;		// error ���ø� ���ڰ� �̸� ���� ��������
	List<Point> ok;				// ok �̸� ���� Ŭ�������� typedef�� �̸� ����

	int a;
	clear( a );					// error int�� ���� ������ *�� �������� �ʴ´�.
}