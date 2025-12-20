#pragma once
#include "streamline/metaprogramming/forward.hpp"

namespace sl {
	template<auto Func>
	struct generic_stateless_functor {
		template<typename... Args>
		constexpr auto operator()(Args&&... args) const noexcept {
			return Func(forward<Args>(args)...);
		};
	};
}