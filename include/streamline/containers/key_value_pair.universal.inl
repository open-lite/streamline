#pragma once
#include "streamline/containers/key_value_pair.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"


namespace sl {
	template<index_t I, traits::specialization_of<generic_key_value_pair> PairT>
	constexpr auto&& get(PairT&& a) noexcept {
		return forward_like<PairT>(a[index_constant<I>]);
	}

	template<typename T, traits::specialization_of<generic_key_value_pair> PairT>
	constexpr auto&& get(PairT&& a) noexcept {
		return forward_like<PairT>(a[index_constant<get<0>(typename tuple_traits<remove_cvref_t<PairT>>::template indices_of_type<T>{})>]);
	}
}
