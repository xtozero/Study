#include <iostream>

// °£´ÜÇÑ CRTP
template <typename Derived>
class CuriousBase
{

};

class Curious : public CuriousBase<Curious>
{

};

template <typename CountedType>
class ObjectCounter
{
private:
	static size_t count;

protected:
	ObjectCounter( )
	{
		++count;
	}

	ObjectCounter( const ObjectCounter<CountedType>& )
	{
		++count;
	}

	ObjectCounter( ObjectCounter<CountedType>&& )
	{
		++count;
	}

	virtual ~ObjectCounter( )
	{
		--count;
	}

public:
	static size_t live( )
	{
		return count;
	}
};

template <typename CountedType>
size_t ObjectCounter<CountedType>::count = 0;

template <typename CharT>
class MyString : public ObjectCounter<MyString<CharT>>
{
};

int main( )
{
	MyString<char> s1, s2;
	MyString<wchar_t> ws;

	std::cout << "number of MyString<char>: " << MyString<char>::live() << std::endl;
	std::cout << "number of MyString<wchar_t>: " << MyString<wchar_t>::live() << std::endl;
}