#pragma once
#include "streamline/metaprogramming/conditional.hpp"
#include "streamline/metaprogramming/type_of_pack_element.hpp"
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/numeric/int.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.fwd.hpp"


namespace sl {
	template<typename T, T... Is>
	struct integer_sequence_type {
		using value_type = T;
		consteval static size_t size() noexcept { return sizeof...(Is); }
		consteval static size_t size_bytes() noexcept { return sizeof...(Is); }

		template<index_t I>
		consteval static T get() noexcept 
		requires (I < sizeof...(Is)){ 
			return type_of_pack_element_t<I, constant_type<T, Is>...>::value;
		}
	};


	template<index_t I, typename T, T... Is>
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
  	template<typename T, T N>
	using integer_sequence_of_length_type = __make_integer_seq<integer_sequence_type, T, N>;
	#else
  	template<typename T, T N>
	using integer_sequence_of_length_type = integer_sequence_type<T, __integer_pack(N)...>;
	#endif


  	template<index_t N>
	using index_sequence_of_length_type = integer_sequence_of_length_type<index_t, N>;

	template<typename... Ts>
	using index_sequence_for_pack_type = index_sequence_of_length_type<sizeof...(Ts)>;
}


namespace sl {
	template<typename T, T... Is>
	constexpr integer_sequence_type<T, Is...> integer_sequence{};


	template<index_t... Is>
	constexpr index_sequence_type<Is...> index_sequence{};
}

namespace sl{
  	template<typename T, T N>
	constexpr integer_sequence_of_length_type<T, N> integer_sequence_of_length{};
	

  	template<index_t N>
	constexpr index_sequence_of_length_type<N> index_sequence_of_length{};

	template<typename... Ts>
	constexpr index_sequence_for_pack_type<Ts...> index_sequence_for_pack{};
}


namespace sl{ 
	template<typename T, T... Is>
	struct container_traits<integer_sequence_type<T, Is...>> {
		constexpr static size_t size = integer_sequence_type<T, Is...>::size();
		constexpr static size_t size_bytes = integer_sequence_type<T, Is...>::size_bytes();
	};

	template<typename T, T... Is>
	struct tuple_traits<integer_sequence_type<T, Is...>> : public container_traits<integer_sequence_type<T, Is...>> {
		constexpr static bool homogeneous = true;
		constexpr static bool unique = false;
		
		using common_type = T;
		

		template<size_t I>
		using type_of_element = T;

		template<typename U> struct __seq_size : size_constant_type<0> {};
		template<> struct __seq_size<T> : size_constant_type<integer_sequence_type<T, Is...>::size()> {};

		template<typename U>
		using indices_of_type = index_sequence_of_length_type<__seq_size<U>::value>;
	};
}


namespace sl{
	namespace impl {
		template<typename, typename, auto Pred>
		struct make_filtered_sequence;

		template<typename T, T I, T... Is, T... Js, auto Pred>
		struct make_filtered_sequence<integer_sequence_type<T, I, Is...>, integer_sequence_type<T, Js...>, Pred> :
			make_filtered_sequence<integer_sequence_type<T, Is...>, conditional_t<Pred(constant<T, I>), integer_sequence_type<T, Js..., I>, integer_sequence_type<T, Js...>>, Pred> {};

		template<typename T, T... Js, auto Pred>
		struct make_filtered_sequence<integer_sequence_type<T>, integer_sequence_type<T, Js...>, Pred> : type_identity<integer_sequence_type<T, Js...>> {};
	}


	template<typename, auto Pred>
	struct filtered_sequence;

	template<typename T, T... Is, auto Pred>
	struct filtered_sequence<integer_sequence_type<T, Is...>, Pred> : public impl::make_filtered_sequence<integer_sequence_type<T, Is...>, integer_sequence_type<T>, Pred> {}; 


	template<typename Seq, auto Pred>
	using filtered_sequence_t = typename filtered_sequence<Seq, Pred>::type;
}