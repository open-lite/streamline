#pragma once
#include "streamline/containers/tuple.hpp"
#include "streamline/containers/key_value_pair.hpp"


namespace sl {
	template<index_t... Is, typename... Ts>
	constexpr generic_tuple<index_sequence_type<Is...>, Ts...>::operator generic_key_value_pair<Ts...>() const noexcept
	requires(sizeof...(Ts) == 2) {
		return generic_key_value_pair<Ts...>{
			this->operator[](sl::first_constant), 
			this->operator[](sl::second_constant)
		};
	}
}