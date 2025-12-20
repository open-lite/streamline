#pragma once
#include "streamline/metaprogramming/type_identity.hpp"

namespace sl {
	template<bool B, typename T, typename F>
	struct conditional : type_identity<T> {};
	
	template<typename T, typename F>
	struct conditional<false, T, F> : type_identity<F> {};
}

namespace sl {
	template<bool B, typename T, typename F>
	using conditional_t = typename conditional<B,T,F>::type;
}