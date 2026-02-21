#pragma once
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/containers/generic_container_template_args.def.hpp"


namespace sl::generic {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	struct array;
}

namespace sl {
	template<size_t N, typename T>
	using array = generic::array<sl::size_constant_type<N>, T>;
}
