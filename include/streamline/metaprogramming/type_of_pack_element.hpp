#pragma once
#include "streamline/metaprogramming/empty_t.hpp"
#include "streamline/metaprogramming/type_identity.hpp"
#include "streamline/numeric/int.hpp"

namespace sl {
	template<index_t I, typename... Ts>
	struct type_of_pack_element : type_identity<__type_pack_element<I, Ts...>> {};

	template<index_t I>
	struct type_of_pack_element<I> : type_identity<empty_t> {};
}

namespace sl {
	template<index_t I, typename... Ts>
	using type_of_pack_element_t = typename type_of_pack_element<I, Ts...>::type;
}