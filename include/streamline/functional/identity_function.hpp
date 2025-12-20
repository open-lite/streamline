#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"


namespace sl {
	template<typename Arg, index_t I = npos>
	constexpr decltype(auto) identity_function(Arg&& arg, index_constant_type<I> = {}) noexcept {
		return forward<Arg>(arg);
	}
}

namespace sl {
	struct identity_functor {
	template<typename Arg, index_t I = npos>
		constexpr decltype(auto) operator()(Arg&& arg, index_constant_type<I> = {}) const noexcept {
			return forward<Arg>(arg);
		};
	};
}