#pragma once

#include <type_traits>

template <typename T>
class IsPointerT : public std::false_type {};

template <typename T>
class IsPointerT<T*> : public std::true_type 
{
public:
	using BaseT = T;
};

template <typename T>
class IsLValueReferenceT : public std::false_type {};

template <typename T>
class IsLValueReferenceT<T&> : public std::true_type
{
public:
	using BaseT = T;
};

template <typename T>
class IsRValueReferenceT : public std::false_type {};

template <typename T>
class IsRValueReferenceT<T&&> : public std::true_type
{
public:
	using BaseT = T;
};

template <typename T>
class IsReferenceT : public std::conditional<IsLValueReferenceT<T>::value, IsLValueReferenceT<T>, IsRValueReferenceT<T>>::type
{
};

template <typename T>
class IsArrayT : public std::false_type {};

template <typename T, std::size_t N>
class IsArrayT<T[N]> : public std::true_type
{
public:
	using BaseT = T;
	static constexpr std::size_t size = N;
};

template <typename T>
class IsArrayT<T[]> : public std::true_type
{
public:
	using BaseT = T;
	static constexpr std::size_t size = 0;
};

template <typename T>
class IsPointerToMemberT : public std::false_type {};

template <typename T, typename C>
class IsPointerToMemberT<T C::*> : public std::true_type
{
public:
	using MemberT = T;
	using ClassT = C;
};
