#pragma once
#include "streamline/metaprogramming/forward.hpp"

namespace sl::functor {
	template<auto Func>
	struct generic_stateless {
		template<typename... Args>
		constexpr decltype(auto) operator()(Args&&... args) const noexcept {
			return Func(forward<Args>(args)...);
		};
	};
}