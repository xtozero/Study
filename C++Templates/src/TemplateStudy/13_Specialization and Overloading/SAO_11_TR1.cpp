template <typename T>
class Danger
{
public:
	enum { max = 10 };
};

char buffer[Danger<void>::max];

extern void clear( char* const );

int main( )
{
	clear( buffer );
}