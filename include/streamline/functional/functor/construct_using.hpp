#pragma once
#include "streamline/metaprogramming/constant.hpp"

namespace sl::functor {
	template<typename T, auto... Values>
	struct construct_using {
		template<index_t I = npos>
		constexpr T operator()(auto&&, index_constant_type<I> = {}) const noexcept {
			return T{Values...};
		};
	};
}