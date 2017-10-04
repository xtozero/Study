#pragma once

#include <type_traits>

template <typename... Elements>
class TypeList {};

template <typename T>
class IsFunctionT : public std::false_type {};

template <typename R, typename... Params>
class IsFunctionT<R( Params... )> : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = false;
};

template <typename R, typename... Params>
class IsFunctionT<R( Params..., ... )> : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = true;
};

template <typename R, typename... Params>
class IsFunctionT<R( Params... ) const>  : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = true;
};

template <typename R, typename... Params>
class IsFunctionT<R ( Params..., ...) volatile> : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = true;
};

template <typename R, typename... Params>
class IsFunctionT<R( Params..., ... ) const volatile> : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = true;
};

template <typename R, typename... Params>
class IsFunctionT<R ( Params..., ... ) &> : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = true;
};

template <typename R, typename... Params>
class IsFunctionT<R ( Params..., ... ) const&> : public std::true_type
{
public:
	using Type = R;
	using PraramsT = TypeList<Params...>;
	static constexpr bool variadic = true;
};