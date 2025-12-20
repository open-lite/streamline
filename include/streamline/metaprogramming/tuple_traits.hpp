#pragma once
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"

#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"
#include "streamline/metaprogramming/container_traits.hpp"
#include "streamline/numeric/int.hpp"


namespace sl {
	template<typename T, size_t N>
	struct tuple_traits<T[N]> : container_traits<T[N]> {
		constexpr static bool homogeneous = true;
		constexpr static bool unique = false;

		using common_type = T;
		

		template<size_t I>
		using type_of_element = T;

		template<typename U>
		using indices_of_type = index_sequence_of_length_type<traits::is_same_as_v<T, U> ? container_traits<T[N]>::size : 0>;
	};
}