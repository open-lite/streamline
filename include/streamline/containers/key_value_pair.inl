#pragma once
#include "streamline/containers/key_value_pair.hpp"
#include "streamline/containers/tuple.hpp"


namespace sl::generic {
	template<typename KeyT, typename ValueT>
	constexpr auto&& key_value_pair<KeyT, ValueT>::operator[](this auto&& self, index_constant_type<0>) noexcept { 
		return forward_like<decltype(self)>(self.key);
	}

	template<typename KeyT, typename ValueT>
	constexpr auto&& key_value_pair<KeyT, ValueT>::operator[](this auto&& self, index_constant_type<1>) noexcept { 
		return forward_like<decltype(self)>(self.value);
	}
}

namespace sl::generic {
	template<typename KeyT, typename ValueT>
	template<index_t I>
	constexpr auto&& key_value_pair<KeyT, ValueT>::get(this auto&& self, index_constant_type<I>) noexcept { 
		return forward_like<decltype(self)>(self[index_constant<I>]);
	}
}


namespace sl::generic {
	template<typename KeyT, typename ValueT>
	constexpr key_value_pair<KeyT, ValueT>::operator ::sl::tuple<KeyT, ValueT>() const noexcept {
		return ::sl::tuple<KeyT, ValueT>{{key}, {value}};
	}
}