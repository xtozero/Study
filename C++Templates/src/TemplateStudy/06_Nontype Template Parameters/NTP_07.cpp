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
	// Ŭ���� ��� �������� ���
	MemberPointer<&ClassA::member> AddressofMember;
	MemberPointer<nullptr> nullPointer;
}