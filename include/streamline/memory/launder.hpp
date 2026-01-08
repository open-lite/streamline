#pragma once
#include "streamline/metaprogramming/type_modifiers.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"


namespace sl {
	template<typename T> [[nodiscard]] 
	constexpr T* launder(T* p) noexcept {
		static_assert(!sl::traits::is_function_v<T>, "Cannot launder a function pointer");
		static_assert(!sl::traits::is_same_as_v<sl::remove_cvref_t<T>, void>, "Cannot launder a (possibly cv-qualified) void pointer");
		return __builtin_launder(p);
	}
}