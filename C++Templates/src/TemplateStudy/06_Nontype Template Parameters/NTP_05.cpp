template <void( *P )()>
class FunctionPointerType {};

constexpr void( *globalNullFuncPtr )() = nullptr;
void normalFunc( ) {}

int main( )
{
	// �Լ� ������ ���� ���
	FunctionPointerType<globalNullFuncPtr> NullFuncPtr;
	FunctionPointerType<&normalFunc> AddressOfFunc;
}