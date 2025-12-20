#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/in_place.hpp"


namespace sl::universal {
	namespace impl {
		template<typename T>
		struct make_adl {
			template<typename... Args>
			constexpr decltype(auto) operator()(Args&&... args) const noexcept
			requires requires { {make<T>(forward<Args>(args)...)} noexcept; }  {
				return make<T>(forward<Args>(args)...);
			}

			template<typename... Args>
			constexpr decltype(auto) operator()(Args&&... args) const noexcept requires ( 
				!requires { {make<T>(forward<Args>(args)...)} noexcept; } &&
				requires { {make<T>(forward<Args>(args)..., in_place_adl_tag<T>)} noexcept; }
			) {
				return make<T>(forward<Args>(args)..., in_place_adl_tag<T>);
			}
		};
	}

	template<typename T>
	inline constexpr impl::make_adl<T> make{};
}