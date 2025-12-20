#pragma once
#include "streamline/metaprogramming/type_of_pack_element.hpp"
#include "streamline/metaprogramming/type_traits/compounded_categories.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"


namespace sl {
	template<traits::integral T, T... Is>
	struct integer_sequence_type {
		using value_type = T;
		consteval static size_t size() noexcept { return sizeof...(Is); }
		consteval static size_t size_bytes() noexcept { return sizeof...(Is); }

		template<index_t I>
		consteval static T get() noexcept 
		requires (I < sizeof...(Is)){ 
			return type_of_pack_element_t<I, integral_constant_type<T, Is>...>::value;
		}
	};


	template<index_t I, traits::integral T, T... Is>
	consteval T get(integer_sequence_type<T, Is...>) noexcept {
		return integer_sequence_type<T, Is...>::template get<I>();
	}
}

namespace sl {
	template<index_t... Is>
	using index_sequence_type = integer_sequence_type<index_t, Is...>;
}



namespace sl {
	#if __has_builtin(__make_integer_seq)
  	template<size_t N, traits::integral T>
	using integer_sequence_of_length_type = __make_integer_seq<integer_sequence_type, T, N>;
	#else
  	template<size_t N, traits::integral T>
	using integer_sequence_of_length_type = integer_sequence_type<T, __integer_pack(N)...>;
	#endif


  	template<size_t N>
	using index_sequence_of_length_type = integer_sequence_of_length_type<N, index_t>;

	template<typename... Ts>
	using index_sequence_for_pack_type = index_sequence_of_length_type<sizeof...(Ts)>;
}


namespace sl {
	template<traits::integral T, T... Is>
	constexpr integer_sequence_type<T, Is...> integer_sequence{};


	template<index_t... Is>
	constexpr index_sequence_type<Is...> index_sequence{};
}

namespace sl{
  	template<size_t N, traits::integral T>
	constexpr integer_sequence_of_length_type<N, T> integer_sequence_of_length{};
	

  	template<size_t N>
	constexpr index_sequence_of_length_type<N> index_sequence_of_length{};

	template<typename... Ts>
	constexpr index_sequence_for_pack_type<Ts...> index_sequence_for_pack{};
}


namespace sl{ 
	template<traits::integral T, T... Is>
	struct tuple_traits<integer_sequence_type<T, Is...>> {
		constexpr static size_t size = integer_sequence_type<T, Is...>::size();
		constexpr static size_t size_bytes = integer_sequence_type<T, Is...>::size_bytes();
		constexpr static bool homogeneous = true;
		constexpr static bool unique = false;
		
		using common_type = T;
		

		template<size_t I>
		using type_of_element = T;

		template<typename U>
		using indices_of_type = index_sequence_of_length_type<traits::is_same_as_v<T, U> ? size : 0>;
	};
}