#pragma once
#include "streamline/containers/array.hpp"
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/functional/invoke.hpp"
#include "streamline/universal/make_deduced.hpp"

namespace sl::functor {
	template<auto Func>
	struct invoke_each {
		template<typename T, sl::index_t... Is, typename... Args>
		constexpr decltype(auto) operator()(sl::integer_sequence_type<T, Is...>, Args&&... args) const noexcept {
			return (sl::invoke(Func, sl::forward<Args>(args)..., sl::integral_constant<T, Is>), ...);
		};
	};
}