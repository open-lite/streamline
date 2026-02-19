#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"


namespace sl::universal {
	namespace impl {
		template<typename T>
		struct make_adl {
			template<typename... Args>
			constexpr decltype(auto) operator()(Args&&... args) const 
			noexcept(sl::traits::is_noexcept_makeable_from_v<T, Args...>) 
			requires(sl::traits::is_makeable_from_v<T, Args...>) {
				return make<T>(sl::forward<Args>(args)...);
			}

			template<typename... Args>
			constexpr decltype(auto) operator()(Args&&... args) const 
			noexcept(sl::traits::is_noexcept_adl_makeable_from_v<T, Args...>) 
			requires(
				!sl::traits::is_makeable_from_v<T, Args...> && 
				sl::traits::is_adl_makeable_from_v<T, Args...>
			) {
				return make<T>(sl::forward<Args>(args)..., in_place_adl_tag<T>);
			}
		};
	}

	template<typename T>
	inline constexpr impl::make_adl<T> make{};
}