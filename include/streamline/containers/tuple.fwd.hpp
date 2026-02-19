#pragma once
#include "streamline/metaprogramming/integer_sequence.hpp"

namespace sl {
	template<size_t, typename...>
	struct generic_tuple;
}

namespace sl {
	template<typename... Ts>
	using tuple = generic_tuple<sizeof...(Ts), index_sequence_for_pack_type<Ts...>, Ts...>;
}
