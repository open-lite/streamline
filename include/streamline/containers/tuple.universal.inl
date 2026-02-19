#pragma once
#include "streamline/containers/tuple.hpp"


namespace sl {
	template<index_t I, traits::specialization_of<generic_tuple> TupleT>
	constexpr auto&& get(TupleT&& a) noexcept {
		return forward_like<TupleT>(a[index_constant<I>]);
	}

	template<typename T, traits::specialization_of<generic_tuple> TupleT>
	constexpr auto&& get(TupleT&& a) noexcept {
		return forward_like<TupleT>(a[index_constant<get<0>(typename tuple_traits<remove_cvref_t<TupleT>>::template indices_of_type<T>{})>]);
	}
}
