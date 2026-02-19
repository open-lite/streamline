#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"


namespace sl::functor {
	struct identity {
	template<typename Arg, index_t I = npos>
		constexpr Arg&& operator()(Arg&& arg, index_constant_type<I> = {}) const noexcept {
			return sl::forward<Arg>(arg);
		};
	};
}