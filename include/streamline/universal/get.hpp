#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/numeric/int.hpp"


namespace sl::universal::impl {
	template<size_t I, traits::decayed<traits::is_raw_array> RawArrayT>
	constexpr auto&& get(RawArrayT&& a) noexcept {
		return forward_like<RawArrayT>(a[I]);
	}
}


namespace sl::universal {
	namespace impl {
		template<index_t I>
		struct get_adl {
			template<typename Arg>
			constexpr auto&& operator()(Arg&& arg) const noexcept 
			requires requires { {get<I>(forward<Arg>(arg))} noexcept; } {
				return get<I>(forward<Arg>(arg));
			}
		};
	}

	template<index_t I>
	inline constexpr impl::get_adl<I> get{};
}