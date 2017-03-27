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

	List<Association*> error1;	// error 템플릿 인자가 지역 데이터형
	List<ColorPtr> error2;		// error 템플릿 인자가 이름 없는 데이터형
	List<Point> ok;				// ok 이름 없는 클래스형을 typedef로 이름 붙임

	int a;
	clear( a );					// error int는 단항 연산자 *를 지원하지 않는다.
}