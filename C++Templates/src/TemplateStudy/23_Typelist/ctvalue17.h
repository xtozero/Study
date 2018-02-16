#pragma once

template <auto Value>
struct CTValue
{
	static constexpr auto value = Value;
};

template <auto... Values>
class Valuelist {};