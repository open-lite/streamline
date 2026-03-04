#pragma once
#include "streamline/containers/generic_container_template_args.def.hpp"
#include "streamline/numeric/int.hpp"

namespace sl::generic {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	struct version;
}

namespace sl {
	using version = generic::version<sl::uint32_t>;
}