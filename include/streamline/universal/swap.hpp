#pragma once
#include "streamline/metaprogramming/forward.hpp"
#include "streamline/metaprogramming/move.hpp"
#include "streamline/metaprogramming/type_traits/supported_operations.hpp"
#include "streamline/numeric/int.hpp"


namespace sl::universal::impl {
	template<typename T, sl::size_t N>
	constexpr void swap(T (&a)[N], T (&b)[N])
	noexcept(sl::traits::is_noexcept_swappable_v<T>) 
	requires(sl::traits::is_swappable_v<T>) {
		for (sl::index_t i = 0; i < N; ++i)
    		swap(a[i], b[i]);
	}
}


namespace sl::universal {
	namespace impl {
		struct swap_adl {
			template<typename L, typename R>
			constexpr decltype(auto) operator()(L&& l, R&& r) const 
			noexcept(sl::traits::is_noexcept_swappable_with_v<L, R>) 
			requires(sl::traits::is_swappable_with_v<L, R>) {
				return swap(forward<L>(l), forward<R>(r));
			}

			template<typename L, typename R>
			constexpr decltype(auto) operator()(L&& l, R&& r) const 
			noexcept(sl::traits::is_noexcept_swapable_using_member_v<L, R>)
			requires(
				sl::traits::is_swapable_using_member_v<L, R> &&
				!sl::traits::is_swappable_with_v<L, R>
			) {
				return sl::forward<L>(l).swap(sl::forward<R>(r));
			}

			template<typename T>
			constexpr void operator()(T& l, T& r) const 
			noexcept(sl::traits::is_noexcept_fully_movable_v<T>)
			requires(
				sl::traits::is_fully_movable_v<T> &&
				!sl::traits::is_swapable_using_member_v<T, T> &&
				!sl::traits::is_swappable_with_v<T, T>
			) {
				T tmp(sl::move(l));
				l = sl::move(r);
				r = sl::move(tmp);
			}
		};
	}

	inline constexpr impl::swap_adl swap{};
}