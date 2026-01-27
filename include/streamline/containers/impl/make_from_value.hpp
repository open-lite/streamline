#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/universal/get.hpp"


namespace sl::impl {
	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_value(T&& t, F&& func, index_sequence_type<Is...>) noexcept {
		return R{{forward<F>(func)(forward_as_lvalue<T>(t), index_constant<Is>)...}};
	}
}