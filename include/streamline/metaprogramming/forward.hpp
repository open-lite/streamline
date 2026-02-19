#pragma once
#include "streamline/metaprogramming/type_modifiers.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"
#include "streamline/metaprogramming/type_traits/extensions.hpp"


namespace sl {
	template<typename RealT> [[gnu::always_inline, nodiscard]]
	constexpr RealT&& forward(remove_reference_t<RealT>& t) noexcept {
		return static_cast<RealT&&>(t);
	}

	template<typename RealT> [[gnu::always_inline, nodiscard]]
	constexpr RealT&& forward(remove_reference_t<RealT>&& t) noexcept {
		static_assert(!traits::is_lvalue_reference_v<RealT>, "Can not forward a rvalue as a lvalue.");
		return static_cast<RealT&&>(t);
	}
}

namespace sl {
	template<typename LikeT, typename ArgT> [[gnu::always_inline, nodiscard]]
	constexpr copy_cvref_t<LikeT&&, ArgT> forward_like(ArgT&& arg) noexcept {
		return static_cast<copy_cvref_t<LikeT&&, ArgT>>(arg);
	}
}


namespace sl {
	template<typename RealT> [[gnu::always_inline, nodiscard]]
	constexpr auto&& forward_as_lvalue(remove_reference_t<RealT>& t) noexcept {
		if constexpr (!traits::is_lvalue_reference_v<RealT>)
			return static_cast<remove_cvref_t<RealT> const&>(t);
		else 
			return forward<RealT>(t);
	}

	template<typename RealT> [[gnu::always_inline, nodiscard]]
	constexpr auto&& forward_as_lvalue(remove_reference_t<RealT>&& t) noexcept {
		if constexpr (!traits::is_lvalue_reference_v<RealT>)
			return static_cast<remove_cvref_t<RealT> const&>(t);
		else {
			static_assert(traits::is_const_qualified_v<remove_reference_t<RealT>>, "Can not forward a rvalue as a non-const lvalue.");
			return forward<RealT>(t);
		}
	}
}