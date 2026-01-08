#pragma once
#include "streamline/numeric/int.hpp"

namespace sl {
	template<typename T>
	constexpr T aligned_to(T value, sl::size_t align) noexcept 
	requires requires(T t) { value + align; value > t; t = value; } {
		T aligned_value = (value + align - 1) & ~(align - 1);
		//Check for overflow
		if (value > aligned_value) aligned_value = value;
		return aligned_value;
	}
}