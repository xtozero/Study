#pragma once

template <typename T>
struct AddConstT
{
	using Type = const T;
};

template <typename T>
using AddConst = typename AddConstT<T>::Type;