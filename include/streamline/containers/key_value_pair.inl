#pragma once
#include "streamline/containers/key_value_pair.hpp"
#include "streamline/containers/tuple.hpp"


namespace sl {
	template<size_t _UnusedN, typename KeyT, typename ValueT>
	constexpr auto&& generic_key_value_pair<_UnusedN, KeyT, ValueT>::operator[](this auto&& self, index_constant_type<0>) noexcept { 
		return forward_like<decltype(self)>(self.key);
	}

	template<size_t _UnusedN, typename KeyT, typename ValueT>
	constexpr auto&& generic_key_value_pair<_UnusedN, KeyT, ValueT>::operator[](this auto&& self, index_constant_type<1>) noexcept { 
		return forward_like<decltype(self)>(self.value);
	}
}

namespace sl {
	template<size_t _UnusedN, typename KeyT, typename ValueT>
	constexpr generic_key_value_pair<_UnusedN, KeyT, ValueT>::operator tuple<KeyT, ValueT>() const noexcept {
		return tuple<KeyT, ValueT>{{key}, {value}};
	}
}