#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"


namespace sl::functor {
	struct address_of {
		template<typename Arg, index_t I = npos>
		constexpr decltype(auto) operator()(Arg&& arg, index_constant_type<I> = {}) const noexcept
		requires (sl::traits::span_like<sl::remove_cvref_t<Arg>>) {
			return sl::forward<Arg>(arg).data();
		};

		template<typename Arg, index_t I = npos>
		constexpr decltype(auto) operator()(Arg&& arg, index_constant_type<I> = {}) const noexcept
		requires (!sl::traits::span_like<sl::remove_cvref_t<Arg>>) {
			return &sl::forward<Arg>(arg);
		};
	};
}