#pragma once
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/metaprogramming/forward.hpp"

namespace sl::functor {
	template<typename T>
	struct forward_construct {
		template<typename Arg, index_t I = npos>
		constexpr T operator()(Arg&& arg, index_constant_type<I> = {}) const noexcept {
			return T{sl::forward<Arg>(arg)};
		};
	};
}