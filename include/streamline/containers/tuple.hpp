#pragma once
#include "streamline/containers/tuple.fwd.hpp"

#include "streamline/metaprogramming/common_type.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.hpp"
#include "streamline/metaprogramming/type_of_pack_element.hpp"
#include "streamline/metaprogramming/empty_t.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"
#include "streamline/metaprogramming/pack_indices_of_type.hpp"
#include "streamline/containers/key_value_pair.fwd.hpp"

#include "streamline/containers/impl/tuple.hpp"

namespace sl {
	template<index_t... Is, typename... Ts>
	struct generic_tuple<index_sequence_type<Is...>, Ts...> : impl::tuple_element<Is, Ts>... {
		using index_type = index_t;
	public:
		using impl::tuple_element<Is, Ts>::operator[]...;
	public:
		constexpr operator generic_key_value_pair<Ts...>() const noexcept
		requires(sizeof...(Ts) == 2);
	};
}


namespace sl {
	template<typename... Ts>
	struct container_traits<tuple<Ts...>> {
		constexpr static size_t size = sizeof...(Ts);
		constexpr static size_t size_bytes = (sizeof(Ts) + ...);
	};

	template<typename... Ts>
	struct tuple_traits<tuple<Ts...>> : container_traits<tuple<Ts...>> {
		constexpr static bool homogeneous = traits::are_all_same_v<Ts...>;
		constexpr static bool unique = traits::are_all_unique_v<Ts...>;

		using common_type = common_or_empty_type_t<Ts...>;
		template<size_t I>
		using type_of_element = conditional_t<(container_traits<tuple<Ts...>>::size > 0), type_of_pack_element_t<I, Ts...>, empty_t>;


		template<typename U>
		using indices_of_type = pack_indices_of_type_t<U, Ts...>;
	};
}


#include "streamline/containers/tuple.inl"
#include "streamline/containers/tuple.universal.inl"


namespace sl::test {
	constexpr key_value_pair<int, long> ttop = tuple<int, long>{{1}, {2}};
	static_assert(ttop.key == 1);
	static_assert(ttop.value == 2);
}