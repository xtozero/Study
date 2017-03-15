class ClassA
{
public:
	char member;
};

ClassA errorClass;

template <char ClassA::*P>
class MemberPointer {};

int main()
{
	// 클래스 멤버 포인터일 경우
	MemberPointer<&ClassA::member> AddressofMember;
	MemberPointer<nullptr> nullPointer;
}