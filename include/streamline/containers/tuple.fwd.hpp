#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/containers/generic_container_template_args.def.hpp"

namespace sl::generic {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	struct tuple;
}

namespace sl {
	template<typename... Ts>
	using tuple = generic::tuple<index_sequence_for_pack_type<Ts...>, Ts...>;
}
