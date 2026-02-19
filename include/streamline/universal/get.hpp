#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"


namespace sl::universal::impl {
	template<size_t I, traits::decayed<traits::is_raw_array> RawArrayT>
	constexpr auto&& get(RawArrayT&& a) noexcept {
		return forward_like<RawArrayT>(a[I]);
	}
}


namespace sl::universal {
	namespace impl {
		template<auto I>
		struct get_adl {
			template<typename Arg>
			constexpr decltype(auto) operator()(Arg&& arg) const
			noexcept(sl::traits::is_noexcept_gettable_v<Arg, I>) 
			requires(sl::traits::is_gettable_v<Arg, I>) {
				return get<I>(forward<Arg>(arg));
			}

			template<typename Arg>
			constexpr decltype(auto) operator()(Arg&& arg) const
			noexcept(sl::traits::is_noexcept_gettable_using_member_v<Arg, I>)
			requires(sl::traits::is_gettable_using_member_v<Arg, I> && !sl::traits::is_gettable_v<Arg, I>) {
				return forward<Arg>(arg).template get<I>();
			}
		};
	}

	template<auto I>
	inline constexpr impl::get_adl<I> get{};
}