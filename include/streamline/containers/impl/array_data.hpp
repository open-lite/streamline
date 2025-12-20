#pragma once
#include "streamline/diagnostics/unreachable.hpp"
#include "streamline/metaprogramming/empty_t.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/type_identity.hpp"


namespace sl::impl {
	template<size_t N, typename T>
	struct array_data {
		using type = T[N];
	};

	template<typename T>
	struct array_data<0, T> {
		struct type {
			consteval operator T*() const noexcept { return nullptr; }
		};
	};
}