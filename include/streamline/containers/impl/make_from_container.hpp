#pragma once
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/universal/get.hpp"


namespace sl::impl {
	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_container(T&& t, F&& func, index_sequence_type<Is...>) 
	noexcept(
		((traits::is_noexcept_invocable_r_v<R, F&&, copy_cvref_t<T, decltype(*(t.begin() + Is))>, index_constant_type<Is>>) && ...)
	)
	requires(
		traits::is_container_like_v<remove_cvref_t<T>>
	) {
		return R{{
			{(sl::forward<F>(func)(sl::forward_like<T>(*(t.begin() + Is)), index_constant<Is>))}...
		}};
	}


	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_container(T&& t, F&& func, index_sequence_type<Is...>) 
	noexcept(
		((traits::is_noexcept_invocable_r_v<R, F&&, copy_cvref_t<T, decltype(sl::universal::get<Is>(t))>, index_constant_type<Is>>) && ...)
	)
	requires(
		!traits::is_container_like_v<remove_cvref_t<T>> &&
		traits::is_tuple_like_v<remove_cvref_t<T>>
	) {
		return R{{
			{(sl::forward<F>(func)(sl::forward_like<T>(sl::universal::get<Is>(t)), index_constant<Is>))}...
		}};
	}

	
	template<typename R, typename T, typename F, index_t... Is>
	constexpr R make_array_from_container(T&& t, F&& func, index_sequence_type<Is...>) 
	noexcept(
		((traits::is_noexcept_invocable_r_v<R, F&&, copy_cvref_t<T, decltype(t[Is])>, index_constant_type<Is>>) && ...)
	) {
		return R{{
			{(sl::forward<F>(func)(sl::forward_like<T>(t[Is]), index_constant<Is>))}...
		}};
	}
}

namespace sl::impl {
	template<typename R, typename T, typename KF, typename VF, index_t... Is>
	constexpr R make_lookup_table_from_container(T&& t, KF&& key_func, VF&& value_func, index_sequence_type<Is...>)
	noexcept(
		((traits::is_noexcept_invocable_r_v<R, KF&&, copy_cvref_t<T, decltype(*(t.begin() + Is))>, index_constant_type<Is>>) && ...) &&
		((traits::is_noexcept_invocable_r_v<R, VF&&, copy_cvref_t<T, decltype(*(t.begin() + Is))>, index_constant_type<Is>>) && ...)
	)
	requires(
		traits::is_container_like_v<remove_cvref_t<T>>
	) {
		return R{{{
			{
				(sl::forward<KF>(key_func)(sl::forward_like<T>(*(t.begin() + Is)), index_constant<Is>)),
				(sl::forward<VF>(value_func)(sl::forward_like<T>(*(t.begin() + Is)), index_constant<Is>))
			}...
		}}};
	}


	template<typename R, typename T, typename KF, typename VF, index_t... Is>
	constexpr R make_lookup_table_from_container(T&& t, KF&& key_func, VF&& value_func, index_sequence_type<Is...>)
	noexcept(
		((traits::is_noexcept_invocable_r_v<R, KF&&, copy_cvref_t<T, decltype(sl::universal::get<Is>(t))>, index_constant_type<Is>>) && ...) &&
		((traits::is_noexcept_invocable_r_v<R, VF&&, copy_cvref_t<T, decltype(sl::universal::get<Is>(t))>, index_constant_type<Is>>) && ...)
	)
	requires(
		!traits::is_container_like_v<remove_cvref_t<T>> &&
		traits::is_tuple_like_v<remove_cvref_t<T>>
	) {
		return R{{{
			{
				(sl::forward<KF>(key_func)(sl::forward_like<T>(sl::universal::get<Is>(t)), index_constant<Is>)), 
				(sl::forward<VF>(value_func)(sl::forward_like<T>(sl::universal::get<Is>(t)), index_constant<Is>))
			}...
		}}};
	}

	
	template<typename R, typename T, typename KF, typename VF, index_t... Is>
	constexpr R make_lookup_table_from_container(T&& t, KF&& key_func, VF&& value_func, index_sequence_type<Is...>)
	noexcept(
		((traits::is_noexcept_invocable_r_v<R, KF&&, copy_cvref_t<T, decltype(t[Is])>, index_constant_type<Is>>) && ...) &&
		((traits::is_noexcept_invocable_r_v<R, VF&&, copy_cvref_t<T, decltype(t[Is])>, index_constant_type<Is>>) && ...)
	) {
		return R{{{
			{
				(sl::forward<KF>(key_func)(sl::forward_like<T>(t[Is]), index_constant<Is>)), 
				(sl::forward<VF>(value_func)(sl::forward_like<T>(t[Is]), index_constant<Is>))
			}...
		}}};
	}
}