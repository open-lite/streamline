#pragma once
#include "streamline/memory/unique_ptr.hpp"

#include "streamline/metaprogramming/type_traits/relationships.hpp"

namespace sl {
	template<
		traits::specialization_of<generic::unique_ptr> R,
		typename... Args
	> 
	requires(traits::is_constructible_from_v<typename remove_cvref_t<R>::value_type, Args&&...>)
	constexpr remove_cvref_t<R> make(in_place_tag_type, Args&&... args) {
		return remove_cvref_t<R>(new typename remove_cvref_t<R>::element_type(sl::forward<Args>(args)...));
	}

	template<
		traits::specialization_of<generic::unique_ptr> R,
		typename... Args
	> 
	requires(traits::is_constructible_from_v<typename remove_cvref_t<R>::value_type, Args&&...>)
	constexpr remove_cvref_t<R> make_default(in_place_tag_type) {
		return remove_cvref_t<R>(new typename remove_cvref_t<R>::element_type);
	}
}