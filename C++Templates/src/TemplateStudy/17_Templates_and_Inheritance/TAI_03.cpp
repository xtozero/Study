template <typename Base, typename Member>
class BaseMemberPair : private Base
{
private:
	Member member;
public:
	BaseMemberPair( const Base& b, const Member& m ) : Base( b ), member( m ) {}

	const Base& first( ) const
	{
		return ( const Base& )*this;
	}

	Base& first( ) const
	{
		return ( Base& )*this;
	}

	const Member& second( ) const
	{
		return this->member;
	}

	Member& second( ) const
	{
		return this->member;
	}
};

template <typename CustomClass>
class Optimizable
{
private:
	BaseMemberPair<CustomClass, void*> info_and_storage;
};