#pragma once
#include "streamline/metaprogramming/type_identity.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"

namespace sl::impl {
	template<typename T, bool>
	struct underlying_type {};
	
	template<typename T>
	struct underlying_type<T, true> : type_identity<__underlying_type(T)> {};
}

namespace sl {
	template<typename T>
	using underlying_type = impl::underlying_type<T, sl::traits::is_enumeration_v<T>>;
}

namespace sl {
	template<typename T>
	using underlying_type_t = typename underlying_type<T>::type;
}