#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"


namespace sl::universal {
	namespace impl {
		template<template<size_t, typename...> typename T>
		struct make_deduced_adl {
			template<typename... Args>
			constexpr decltype(auto) operator()(Args&&... args) const 
			noexcept(sl::traits::is_noexcept_deduced_makeable_from_v<T, Args...>) 
			requires(sl::traits::is_deduced_makeable_from_v<T, Args...>) {
				return make_deduced<T>(forward<Args>(args)...);
			}

			template<typename... Args>
			constexpr decltype(auto) operator()(Args&&... args) const 
			noexcept(sl::traits::is_noexcept_adl_deduced_makeable_from_v<T, Args...>) 
			requires(
				!sl::traits::is_deduced_makeable_from_v<T, Args...> && 
				sl::traits::is_adl_deduced_makeable_from_v<T, Args...>
			) {
				return make_deduced<T>(forward<Args>(args)..., in_place_container_adl_tag<T>);
			}
		};
	}

	template<template<size_t, typename...> typename T>
	inline constexpr impl::make_deduced_adl<T> make_deduced{};
}