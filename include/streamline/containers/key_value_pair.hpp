#pragma once
#include "streamline/containers/key_value_pair.fwd.hpp"

#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.fwd.hpp"
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/containers/tuple.fwd.hpp"


namespace sl::generic {
	template<typename KeyT, typename ValueT>
	struct key_value_pair<KeyT, ValueT> {
		using index_type = index_t;
	public:
		[[no_unique_address]] KeyT key;
		[[no_unique_address]] ValueT value;

	public:
		constexpr auto&& operator[](this auto&& self, index_constant_type<0>) noexcept;
		constexpr auto&& operator[](this auto&& self, index_constant_type<1>) noexcept;

		template<index_t I> 
		constexpr auto&& get(this auto&& self, index_constant_type<I> = {}) noexcept;

	public:
		constexpr operator ::sl::tuple<KeyT, ValueT>() const noexcept;
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

#include "streamline/metaprogramming/type_traits/supported_operations.hpp"
namespace sl::test {
	constexpr tuple<int, long> ptot = ::sl::key_value_pair<int, long>{1, 2};
	static_assert(ptot[sl::first_constant] == 1);
	static_assert(ptot[sl::second_constant] == 2);

	
	static_assert(::sl::key_value_pair<int, long>{1, 2}.template get<0>() == 1);
	static_assert(::sl::key_value_pair<int, long>{1, 2}.get(sl::index_constant<0>) == 1);
}