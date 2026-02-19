#pragma once
#include "streamline/metaprogramming/forward.hpp"

namespace sl::functor {
	struct equal {
		template<typename L, typename R>
		constexpr auto operator()(L&& lhs, R&& rhs) const 
		noexcept(noexcept(bool(forward<L>(lhs) == forward<R>(rhs)))) {
			return forward<L>(lhs) == forward<R>(rhs);
		}
	};
}

namespace sl::functor {
	struct less {
		template<typename L, typename R>
		constexpr auto operator()(L&& lhs, R&& rhs) const 
		noexcept(noexcept(bool(forward<L>(lhs) < forward<R>(rhs)))) {
			return forward<L>(lhs) < forward<R>(rhs);
		}
	};
}