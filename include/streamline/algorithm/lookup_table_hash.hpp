#pragma once
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"


namespace sl::algo {
	template<typename T>
	struct lookup_table_hash;
}


namespace sl::algo {
	template <traits::integral_like T>
	struct lookup_table_hash<T> {
		constexpr size_t operator()(T const &value, size_t seed) const noexcept {
			//retrieved from "frozen/bits/elsa.h" as part of the "frozen" library
			size_t key = seed ^ static_cast<size_t>(value);
			key = (~key) + (key << 21); // key = (key << 21) - key - 1;
			key = key ^ (key >> 24);
			key = (key + (key << 3)) + (key << 8); // key * 265
			key = key ^ (key >> 14);
			key = (key + (key << 2)) + (key << 4); // key * 21
			key = key ^ (key >> 28);
			key = key + (key << 31);
			return key;
		}
	};
}