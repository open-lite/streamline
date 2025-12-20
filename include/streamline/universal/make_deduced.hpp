#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/in_place.hpp"


namespace sl::universal {
	namespace impl {
		template<template<size_t, typename...> typename T>
		struct make_deduced_adl {
			template<typename... Args>
			constexpr auto operator()(Args&&... args) const noexcept
			requires requires { {make_deduced<T>(forward<Args>(args)...)} noexcept; }  {
				return make_deduced<T>(forward<Args>(args)...);
			}

			template<typename... Args>
			constexpr auto operator()(Args&&... args) const noexcept requires ( 
				!requires { {make_deduced<T>(forward<Args>(args)...)} noexcept; } &&
				requires { {make_deduced<T>(forward<Args>(args)..., in_place_container_adl_tag<T>)} noexcept; }
			) {
				return make_deduced<T>(forward<Args>(args)..., in_place_container_adl_tag<T>);
			}
		};
	}

	template<template<size_t, typename...> typename T>
	inline constexpr impl::make_deduced_adl<T> make_deduced{};
}