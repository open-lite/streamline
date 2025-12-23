#pragma once
#include "streamline/algorithm/lookup_table_hash.hpp"
#include "streamline/functional/comparison.hpp"
#include "streamline/numeric/int.hpp"


namespace sl {
	template <size_t N, typename...>
	struct generic_lookup_table;
}

namespace sl {
	template <size_t N, typename Key, typename Value, typename Hash = algo::lookup_table_hash<Key>, typename KeyEqual = equal_functor>
	using lookup_table = generic_lookup_table<N, Key, Value, Hash, KeyEqual>;
}