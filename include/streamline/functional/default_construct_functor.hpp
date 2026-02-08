#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"

namespace sl{
	template<typename T>
	struct default_construct_functor {
		template<typename Arg, index_t I = npos>
		constexpr sl::index_t operator()(Arg&&, index_constant_type<I> = {}) const noexcept {
			return T{};
		};
	};
}