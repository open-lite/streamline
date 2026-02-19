#pragma once
#include "streamline/metaprogramming/constant.hpp"

namespace sl::functor {
	struct identity_index {
		template<typename T, index_t I = npos>
		consteval sl::index_t operator()(T&&, index_constant_type<I> = {}) const noexcept {
			return I;
		};
	};
}