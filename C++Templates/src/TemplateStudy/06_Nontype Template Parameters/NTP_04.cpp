template <char* P>
class PointerType {};

char g_c;
extern char g_ec;
constexpr char* pNull = nullptr;
//const char* pNull = nullptr;
constexpr char* gStringLiteral = "Hello";
char gArray[10] = {};

class ClassA
{
public:
	static char success;
	char error;
};

ClassA errorClass;

int main( )
{
	// ������ ���� ���
	PointerType<&g_c> globalChar;
	PointerType<&g_ec> externGlobalChar;
	PointerType<pNull> nullPointer;
	// PointerType<nullptr> nullptrValue; // gcc������ ����, vs2015 community �������� error

	// PointerType<gStringLiteral> stringLiteral;
	// PointerType<&gArray[0]> AddressofArray;

	// PointerType<&errorClass.error> AddressofNonStaticMember; // error
	// PointerType<&errorClass.success> AddressofStaticMember; // gcc���� error, vs2015 community �������� ����
	PointerType<&ClassA::success> AddressofStaticMember;
}