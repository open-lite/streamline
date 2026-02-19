#pragma once
#include "streamline/metaprogramming/constant.hpp"

namespace sl::functor {
	template<typename T>
	struct default_construct {
		template<typename Arg, index_t I = npos>
		constexpr T operator()(Arg&&, index_constant_type<I> = {}) const noexcept {
			return T{};
		};
	};
}