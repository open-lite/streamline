#pragma once
#include "streamline/containers/tuple.hpp"
#include "streamline/containers/key_value_pair.hpp"



namespace sl::generic {

	template<index_t... Is, typename... Ts>
	template<index_t I>
	constexpr auto&& generic::tuple<index_sequence_type<Is...>, Ts...>::get(this auto&& self) noexcept {
		return forward_like<decltype(self)>(self.get(index_constant<I>));
	}

	template<index_t... Is, typename... Ts>
	template<typename T>
	constexpr auto&& generic::tuple<index_sequence_type<Is...>, Ts...>::get(this auto&& self) noexcept {
		return forward_like<decltype(self)>(self.get(type_identity<T>{}));
	}
}

namespace sl::generic {
	template<index_t... Is, typename... Ts>
	constexpr generic::tuple<index_sequence_type<Is...>, Ts...>::operator generic::key_value_pair<Ts...>() const noexcept
	requires(sizeof...(Ts) == 2) {
		return key_value_pair<Ts...>{
			this->operator[](sl::first_constant), 
			this->operator[](sl::second_constant)
		};
	}
}