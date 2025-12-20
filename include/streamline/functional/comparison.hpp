#pragma once
#include "streamline/metaprogramming/forward.hpp"

namespace sl {
	struct equal_functor {
		template<typename L, typename R>
		constexpr auto operator()(L&& lhs, R&& rhs) const 
		noexcept(noexcept(bool(forward<L>(lhs) == forward<R>(rhs)))) {
			return forward<L>(lhs) == forward<R>(rhs);
		}
	};
}

namespace sl {
	struct less_functor {
		template<typename L, typename R>
		constexpr auto operator()(L&& lhs, R&& rhs) const 
		noexcept(noexcept(bool(forward<L>(lhs) < forward<R>(rhs)))) {
			return forward<L>(lhs) < forward<R>(rhs);
		}
	};
}