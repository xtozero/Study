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
	// 포인터 형일 경우
	PointerType<&g_c> globalChar;
	PointerType<&g_ec> externGlobalChar;
	PointerType<pNull> nullPointer;
	// PointerType<nullptr> nullptrValue; // gcc에서는 성공, vs2015 community 버전에서 error

	// PointerType<gStringLiteral> stringLiteral;
	// PointerType<&gArray[0]> AddressofArray;

	// PointerType<&errorClass.error> AddressofNonStaticMember; // error
	// PointerType<&errorClass.success> AddressofStaticMember; // gcc에서 error, vs2015 community 버전에서 성공
	PointerType<&ClassA::success> AddressofStaticMember;
}