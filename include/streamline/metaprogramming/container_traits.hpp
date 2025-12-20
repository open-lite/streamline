#pragma once
#include "streamline/metaprogramming/container_traits.fwd.hpp"

#include "streamline/numeric/int.hpp"


namespace sl {
	template<typename T, size_t N>
	struct container_traits<T[N]> {
		constexpr static size_t size = N;
		constexpr static size_t size_bytes = N * sizeof(T);
	};
}