template <typename T>
class Danger;

template <>
class Danger<void>
{
public:
	enum { max = 100 };
};

void clear( char* const buf )
{
	for ( int i = 0; i < Danger<void>::max; ++i )
	{
		buf[i] = '\0';
	}
}