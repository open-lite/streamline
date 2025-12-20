#pragma once
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"


namespace sl::impl {
	template <typename Sequence, typename Constant, typename T, typename... Ts>
	struct pack_indices;

	
	//0 types case
	template <typename T>
	struct pack_indices<index_sequence_type<>, index_constant_type<0>, T> {
		using type = index_sequence_type<>;
		constexpr static type value = index_sequence<>;
	};
	
	
	//1 type cases
	template <typename T, index_t... Is, index_t I>
	struct pack_indices<index_sequence_type<Is...>, index_constant_type<I>, T, T> {
		using type = index_sequence_type<Is..., I>;
		constexpr static type value = index_sequence<Is..., I>;
	};

	template <typename T, typename U, index_t... Is, index_t I>
	struct pack_indices<index_sequence_type<Is...>, index_constant_type<I>, T, U> {
		using type = index_sequence_type<Is...>;
		constexpr static type value = index_sequence<Is...>;
	};

	
	//more than 1 type cases
	template <typename T, typename... Ts, index_t... Is, index_t I>
	struct pack_indices<index_sequence_type<Is...>, index_constant_type<I>, T, T, Ts...> :
		pack_indices<index_sequence_type<Is..., I>, index_constant_type<I + 1>, T, Ts...> {};

	template <typename T, typename U, typename... Ts, index_t... Is, index_t I>
	struct pack_indices<index_sequence_type<Is...>, index_constant_type<I>, T, U, Ts...> :
		pack_indices<index_sequence_type<Is...>, index_constant_type<I + 1>, T, Ts...> {};


}


namespace sl {
	template <typename T, typename... Ts>
	using pack_indices_of_type = impl::pack_indices<index_sequence_type<>, index_constant_type<0>, T, Ts...>;
}

namespace sl {
	template <typename T, typename... Ts>
	using pack_indices_of_type_t = typename pack_indices_of_type<T, Ts...>::type;

	template <typename T, typename... Ts>
	constexpr pack_indices_of_type_t<T, Ts...> pack_indices_of_type_v = pack_indices_of_type<T, Ts...>::value;
}