#pragma once
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/universal/get.hpp"


namespace sl::impl {
	template<typename R, index_t... Is, typename... Args>
	constexpr R make_array_in_place(index_sequence_type<Is...>, Args&&... args) 
	noexcept(traits::is_noexcept_constructible_from_v<typename remove_cvref_t<R>::value_type, Args&&...>) {
		
		return R{{(static_cast<void>(Is), typename remove_cvref_t<R>::value_type{sl::forward<Args>(args)...})...}};
	}
}