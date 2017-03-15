template <void( *P )()>
class FunctionPointerType {};

constexpr void( *globalNullFuncPtr )() = nullptr;
void normalFunc( ) {}

int main( )
{
	// 함수 포인터 형일 경우
	FunctionPointerType<globalNullFuncPtr> NullFuncPtr;
	FunctionPointerType<&normalFunc> AddressOfFunc;
}