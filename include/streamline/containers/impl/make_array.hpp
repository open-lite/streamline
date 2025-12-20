#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/universal/get.hpp"


namespace sl::impl {
	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_value(T&& t, F&& func, index_sequence_type<Is...>) noexcept {
		return R{{forward<F>(func)(forward<T>(t), index_constant<Is>)...}};
	}

	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_container(T&& t, F&& func, index_sequence_type<Is...>) noexcept {
		if constexpr(traits::is_tuple_like_v<remove_cvref_t<T>>)
			return R{{{(forward<F>(func)(sl::universal::get<Is>(forward<T>(t)), index_constant<Is>))}...}};
		else if constexpr(traits::is_subscriptable_v<remove_cvref_t<T>>)
			return R{{{(forward<F>(func)(forward_like<T>(t[Is]), index_constant<Is>))}...}};
		else
			return R{{{(forward<F>(func)(forward_like<T>(*(t.begin() + Is)), index_constant<Is>))}...}};
	}

}