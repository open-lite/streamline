#pragma once
#include "streamline/metaprogramming/type_modifiers.hpp"

namespace sl {
	template<typename T>
	constexpr remove_reference_t<T>&& move(T&& t) noexcept {
		return static_cast<typename remove_reference<T>::type&&>(t);
	}
}