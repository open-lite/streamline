#pragma once
#include "streamline/containers/key_value_pair.fwd.hpp"

#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.fwd.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/containers/tuple.fwd.hpp"


namespace sl {
	template<size_t, typename...>
	struct generic_key_value_pair;

	template<size_t _UnusedN, typename KeyT, typename ValueT>
	struct generic_key_value_pair<_UnusedN, KeyT, ValueT> {
		using index_type = index_t;
	public:
		[[no_unique_address]] KeyT key;
		[[no_unique_address]] ValueT value;

	public:
		constexpr auto&& operator[](this auto&& self, index_constant_type<0>) noexcept;
		constexpr auto&& operator[](this auto&& self, index_constant_type<1>) noexcept;

	public:
		constexpr operator tuple<KeyT, ValueT>() const noexcept;
	};
}


namespace sl {
	template<typename KeyT, typename ValueT>
	struct container_traits<key_value_pair<KeyT, ValueT>> : container_traits<tuple<KeyT, ValueT>> {};

	template<typename KeyT, typename ValueT>
	struct tuple_traits<key_value_pair<KeyT, ValueT>> : tuple_traits<tuple<KeyT, ValueT>> {};
}


#include "streamline/containers/key_value_pair.inl"
#include "streamline/containers/key_value_pair.universal.inl"


namespace sl::test {
	constexpr tuple<int, long> ptot = key_value_pair<int, long>{1, 2};
	static_assert(ptot[sl::first_constant] == 1);
	static_assert(ptot[sl::second_constant] == 2);
}