#pragma once
#include "streamline/metaprogramming/common_type.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.hpp"
#include "streamline/metaprogramming/type_of_pack_element.hpp"
#include "streamline/metaprogramming/empty_t.hpp"
#include "streamline/metaprogramming/pack_indices_of_type.hpp"

#include "streamline/containers/impl/tuple.hpp"

namespace sl {
	template<size_t _UnusedN, typename... Ts>
	struct generic_tuple : impl::tuple<_UnusedN, index_sequence_for_pack_type<Ts...>, Ts...> {};
}

namespace sl {
	template<typename... Ts>
	using tuple = generic_tuple<sizeof...(Ts), Ts...>;
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

namespace sl {
	template<index_t I, traits::specialization_of<generic_tuple> TupleT>
	constexpr auto&& get(TupleT&& a) noexcept {
		return forward_like<TupleT>(a[index_constant<I>]);
	}
}
