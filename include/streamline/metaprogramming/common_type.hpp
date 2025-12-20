#pragma once
#include "streamline/metaprogramming/empty_t.hpp"
#include "streamline/metaprogramming/type_identity.hpp"


namespace sl {
	template<typename... Ts>
	struct common_type;

	template<typename... Ts>
	struct common_or_empty_type;
}

namespace sl {
	template<typename... Ts>
	using common_type_t = typename common_type<Ts...>::type;

	template<typename... Ts>
	using common_or_empty_type_t = typename common_or_empty_type<Ts...>::type;
}


namespace sl {
	//TODO: add a non-builtin version for gcc
	template<typename... Ts>
	struct common_type : __builtin_common_type<common_type_t, type_identity, empty_t, Ts...> {};

	template<typename... Ts>
	struct common_or_empty_type : __builtin_common_type<common_or_empty_type_t, type_identity, type_identity<empty_t>, Ts...> {};
}