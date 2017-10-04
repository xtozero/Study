#pragma once

#include "Class.h"
#include "Compound.h"
#include "Enum.h"
#include "Functional.h"
#include "Fundamental.h"

template <typename T>
class IsEnumT
{
public:
	static constexpr bool value = !IsFundaT<T>::value &&
							      !IsPointerT<T>::value &&
							      !IsReferenceT<T>::value &&
							      !IsArrayT<T>::value &&
							      !IsPointerToMemberT<T>::value &&
							      !IsFunctionT<T>::value &&
							      !IsClassT<T>::value;
};