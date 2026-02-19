#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"
#include "streamline/metaprogramming/type_traits/relationships.hpp"
#include "streamline/metaprogramming/tuple_traits.fwd.hpp"
#include "streamline/metaprogramming/container_traits.fwd.hpp"

#include "streamline/metaprogramming/impl/compounded_categories.hpp"


//compund arithmetic categories
namespace sl::traits {
	template<typename T> struct is_integral : bool_constant_type<is_integer<T>::value || is_character<T>::value || is_same_as<T, bool>::value> {};
	//TODO: replace with incrementable
	template<typename T> struct is_integral_like : bool_constant_type<is_integral<T>::value || is_enumeration<T>::value> {};

	template<typename T> struct is_arithmetic : bool_constant_type<is_integral<T>::value || is_floating_point<T>::value> {};
	template<typename T> struct is_signed_arithmetic : impl::is_signed<T, is_arithmetic<T>::value>::type {};
	template<typename T> struct is_unsigned_arithmetic : impl::is_unsigned<T, is_arithmetic<T>::value>::type {};
}


//container categories
namespace sl::traits {
	template<typename T, typename IndexT = index_t> struct is_subscriptable : bool_constant_type<requires (T t, IndexT i){
		{t[i]} noexcept;
	}> {};

	template<typename T> struct is_container_like : bool_constant_type<requires (T container_ish){
		{container_traits<T>::size} noexcept -> same_as<size_t const&>;
		{container_traits<T>::size_bytes} noexcept -> same_as<size_t const&>;
		{container_ish.begin()} noexcept;
		{container_ish.end()} noexcept;
	}> {};

	template<typename T> struct is_span_like : bool_constant_type<requires (T span_ish, index_t i){
		requires is_container_like<T>::value;
		{span_ish[i]} noexcept;// -> same_as<typename T::const_reference_type>;
		{span_ish.data()} noexcept;// -> same_as<typename T::const_pointer_type>;
		{span_ish.size()} noexcept -> same_as<typename T::size_type>;
	}> {};

	template<typename T> struct is_tuple_like : bool_constant_type<requires (T tuple_ish){
		//{get<0>(tuple_ish)} noexcept; //-> same_as<typename tuple_traits<T>::template type_of_element<0>>;
		{tuple_traits<T>::size} noexcept -> same_as<size_t const&>;
		{tuple_traits<T>::size_bytes} noexcept -> same_as<size_t const&>;
		{tuple_traits<T>::homogeneous} noexcept -> same_as<bool const&>;
		{tuple_traits<T>::unique} noexcept -> same_as<bool const&>;
		typename tuple_traits<T>::common_type;
		typename tuple_traits<T>::template type_of_element<0>;
		typename tuple_traits<T>::template indices_of_type<void>;
	}> {};

	template<typename T> struct is_pair_like : bool_constant_type<is_tuple_like<T>::value && requires { requires tuple_traits<T>::size == 2; }> {};
	
	template<typename T> struct is_array_like : bool_constant_type<is_span_like<T>::value && is_tuple_like<T>::value> {};
}



//helper variables
namespace sl::traits {
	template<typename T>
	constexpr static bool is_integral_v = is_integral<T>::value;
	template<typename T>
	constexpr static bool is_integral_like_v = is_integral_like<T>::value;

	template<typename T>
	constexpr static bool is_arithmetic_v = is_arithmetic<T>::value;
	template<typename T>
	constexpr static bool is_signed_arithmetic_v = is_signed_arithmetic<T>::value;
	template<typename T>
	constexpr static bool is_unsigned_arithmetic_v = is_unsigned_arithmetic<T>::value;


	template<typename T, typename IndexT = index_t>
	constexpr static bool is_subscriptable_v = is_subscriptable<T, IndexT>::value;

	template<typename T>
	constexpr static bool is_container_like_v = is_container_like<T>::value;

	template<typename T>
	constexpr static bool is_span_like_v = is_span_like<T>::value;

	template<typename T>
	constexpr static bool is_tuple_like_v = is_tuple_like<T>::value;

	template<typename T>
	constexpr static bool is_pair_like_v = is_pair_like<T>::value;

	template<typename T>
	constexpr static bool is_array_like_v = is_array_like<T>::value;
}

//concepts
namespace sl::traits {
	template<typename T>
	concept integral = is_integral_v<T>;
	template<typename T>
	concept integral_like = is_integral_like_v<T>;

	template<typename T>
	concept arithmetic = is_arithmetic_v<T>;
	template<typename T>
	concept signed_arithmetic = is_signed_arithmetic_v<T>;
	template<typename T>
	concept unsigned_arithmetic = is_unsigned_arithmetic_v<T>;


	template<typename T, typename IndexT = index_t>
	concept subscriptable = is_subscriptable_v<T, IndexT>;

	template<typename T>
	concept container_like = is_container_like_v<T>;

	template<typename T>
	concept span_like = is_span_like_v<T>;

	template<typename T>
	concept tuple_like = is_tuple_like_v<T>;

	template<typename T>
	concept pair_like = is_pair_like_v<T>;

	template<typename T>
	concept array_like = is_array_like_v<T>;
}