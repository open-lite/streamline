#pragma once
#include "streamline/containers/generic_container_template_args.def.hpp"


namespace sl::generic {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	struct reference_ptr;
}

namespace sl {
	template<typename T>
	using reference_ptr = generic::reference_ptr<T>;
}
