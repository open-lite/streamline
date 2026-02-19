#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/numeric/int.hpp"

namespace sl::functor {
	template<index_t J>
	struct subscript {
		template<typename T, index_t I = npos>
		constexpr auto&& operator()(T&& t, index_constant_type<I> = {}) const
		noexcept(noexcept(t[index_constant<J>] )) 
		requires(requires{t[index_constant<J>];}) {
			return sl::forward_like<T>(t[index_constant<J>]);
		};
	};
}