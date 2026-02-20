#pragma once
#include "streamline/algorithm/lookup_table_hash.hpp"
#include "streamline/functional/functor/comparison.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/containers/generic_container_template_args.def.hpp"


namespace sl {
	template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()>
	struct generic_lookup_table;
}

namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash = algo::lookup_table_hash<Key>, typename KeyEqual = functor::equal>
	using lookup_table = generic_lookup_table<sl::size_constant_type<N>, Key, Value, Hash, KeyEqual>;
}