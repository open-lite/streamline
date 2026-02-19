#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"

namespace sl {
	template<size_t, typename...>
	struct generic_key_value_pair;
}

namespace sl {
	template<typename LeftT, typename RightT>
	using key_value_pair = generic_key_value_pair<2, LeftT, RightT>;
}