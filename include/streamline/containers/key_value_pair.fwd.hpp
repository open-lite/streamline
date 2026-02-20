#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/containers/generic_container_template_args.def.hpp"

namespace sl {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	struct generic_key_value_pair;
}

namespace sl {
	template<typename LeftT, typename RightT>
	using key_value_pair = generic_key_value_pair<LeftT, RightT>;
}