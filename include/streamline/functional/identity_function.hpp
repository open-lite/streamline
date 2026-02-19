#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"


namespace sl {
	template<typename Arg, index_t I = npos>
	constexpr Arg&& identity_function(Arg&& arg, index_constant_type<I> = {}) noexcept {
		return sl::forward<Arg>(arg);
	}
}