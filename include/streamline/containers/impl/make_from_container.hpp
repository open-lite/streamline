#pragma once
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/universal/get.hpp"


namespace sl::impl {
	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_container(T&& t, F&& func, index_sequence_type<Is...>) noexcept {
		if constexpr(requires { forward<T>(t).begin(); })
			return R{{{(forward<F>(func)(*(forward_as_lvalue<T>(t).begin() + Is), index_constant<Is>))}...}};
		else if constexpr(traits::is_tuple_like_v<remove_cvref_t<T>>)
			return R{{{(forward<F>(func)(sl::universal::get<Is>(forward_as_lvalue<T>(t)), index_constant<Is>))}...}};
		else //if constexpr(traits::is_subscriptable_v<remove_cvref_t<T>>)
			return R{{{(forward<F>(func)(forward_like<T>(t[Is]), index_constant<Is>))}...}};
	}
}

namespace sl::impl {
	template<typename R, typename T, typename KF, typename VF, index_t... Is>
	constexpr R make_lookup_table_from_container(T&& t, KF&& key_func, VF&& value_func, index_sequence_type<Is...>) noexcept {
		if constexpr(requires { forward<T>(t).begin(); })
			return R{{{{(forward<KF>(key_func)(*(forward_as_lvalue<T>(t).begin() + Is), index_constant<Is>)), (forward<VF>(value_func)(*(forward_as_lvalue<T>(t).begin() + Is), index_constant<Is>))}...}}};
		else if constexpr(traits::is_tuple_like_v<remove_cvref_t<T>>)
			return R{{{{(forward<KF>(key_func)(sl::universal::get<Is>(forward_as_lvalue<T>(t)), index_constant<Is>)), (forward<VF>(value_func)(sl::universal::get<Is>(forward_as_lvalue<T>(t)), index_constant<Is>))}...}}};
		else //if constexpr(traits::is_subscriptable_v<remove_cvref_t<T>>)
			return R{{{{(forward<KF>(key_func)(forward_like<T>(t[Is]), index_constant<Is>)), (forward<VF>(value_func)(forward_like<T>(t[Is]), index_constant<Is>))}...}}};
	}
}