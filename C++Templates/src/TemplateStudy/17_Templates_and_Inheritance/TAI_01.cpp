#include <type_traits>

template <typename Base, int D>
class Discriminator : public Base
{
};

template <typename Setter1, typename Setter2,
		typename Setter3, typename Setter4>
class PolicySelector : public Discriminator<Setter1, 1>,
						public Discriminator<Setter2, 2>,
						public Discriminator<Setter3, 3>,
						public Discriminator<Setter4, 4>
{
};

class DefaultPolicy1 {};
class DefaultPolicy2 {};
class DefaultPolicy3 {};
class DefaultPolicy4 {};

class DefaultPolicies
{
public:
	using P1 = DefaultPolicy1;
	using P2 = DefaultPolicy2;
	using P3 = DefaultPolicy3;
	using P4 = DefaultPolicy4;
};

class DefaultPolicyArgs : virtual public DefaultPolicies
{
};

template <typename Policy>
class Policy1_is : virtual public DefaultPolicies
{
public:
	using P1 = Policy;
};

template <typename Policy>
class Policy2_is : virtual public DefaultPolicies
{
public:
	using P2 = Policy;
};

template <typename Policy>
class Policy3_is : virtual public DefaultPolicies
{
public:
	using P3 = Policy;
};

template <typename Policy>
class Policy4_is : virtual public DefaultPolicies
{
public:
	using P4 = Policy;
};

template <typename PolicySetter1 = DefaultPolicyArgs,
		typename PolicySetter2 = DefaultPolicyArgs,
		typename PolicySetter3 = DefaultPolicyArgs,
		typename PolicySetter4 = DefaultPolicyArgs>
class BreadSlicer
{
public:
	using Policies = PolicySelector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4>;
};

class CustomPolicy {};

int main()
{
	BreadSlicer<> default;
	BreadSlicer<Policy3_is<CustomPolicy>> costumPolicy;

	std::is_same<typename BreadSlicer<>::Policies::P3, DefaultPolicy3>::value;
	std::is_same<typename BreadSlicer<Policy3_is<CustomPolicy>>::Policies::P3, CustomPolicy>::value;
}