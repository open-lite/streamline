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


namespace sl {
	template<index_t I>
	struct identity_tuple_functor {
		template<typename T, index_t J = npos>
		constexpr auto&& operator()(T&& t, index_constant_type<J> = {}) const noexcept {
			return forward<T>(t).operator[](index_constant<I>);
		};
	};
}