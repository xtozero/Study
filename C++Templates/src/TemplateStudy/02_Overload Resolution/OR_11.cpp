#include <cstring>

class BadString
{
public:
	BadString( char const* str ) 
	{
		int len = std::strlen( str );
		m_pString = new char[len + 1];
		memcpy_s( m_pString, len, str, len );
		m_pString[len] = '\0';
	}
	~BadString( )
	{
		delete m_pString;
	}

	char& operator[] ( size_t idx ) { return m_pString[idx]; }
	char const& operator[] ( size_t idx ) const { return m_pString[idx]; }

	operator char* () { return m_pString; }

private:
	char* m_pString = nullptr;
};

int main( )
{
	const BadString str1( "template" );
	str1[5];

	BadString str2( "study" );
	str2[5];
}