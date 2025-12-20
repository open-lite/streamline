#pragma once
#include "streamline/numeric/int.hpp"


namespace sl {
	template<size_t, typename...>
	struct generic_array;
}

namespace sl {
	template<size_t N, typename T>
	using array = generic_array<N, T>;
}
