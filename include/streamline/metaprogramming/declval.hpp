#pragma once
#include "streamline/metaprogramming/type_modifiers.hpp"


namespace sl {
	template<typename T>
	add_rvalue_reference_t<T> declval() noexcept {
	    static_assert(false, "declval not allowed in an evaluated context");
	}
}