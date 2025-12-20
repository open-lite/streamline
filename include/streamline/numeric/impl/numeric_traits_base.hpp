#pragma once
#include <limits.h>

#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/numeric/int.hpp"

namespace sl::impl {
	template<typename T>
	struct numeric_traits_base {};
}

namespace sl::impl {
	template<traits::integral T>
	struct numeric_traits_base<T> {
		constexpr static size_t digits = CHAR_BIT * sizeof(T) - traits::is_signed_arithmetic_v<T>;
	};
}