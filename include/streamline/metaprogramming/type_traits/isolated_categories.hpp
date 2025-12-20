#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/metaprogramming/type_modifiers.hpp"

#include "streamline/metaprogramming/impl/isolated_categories.hpp"


//arithmetic categories
namespace sl::traits {
	template<typename T> struct is_integer : impl::is_integer<remove_cv_t<T>> {};
	template<typename T> struct is_character : impl::is_character<remove_cv_t<T>> {};

	template<typename T> struct is_floating_point : impl::is_floating_point<remove_cv_t<T>> {};

	template<typename T> struct is_enumeration : bool_constant_type<__is_enum(T)> {};
}


//type categories
namespace sl::traits {
	template<typename T>            struct is_bounded_raw_array       : false_constant_type {};
	template<typename T, index_t N> struct is_bounded_raw_array<T[N]> : true_constant_type {};

	template<typename T> struct is_unbounded_raw_array      : false_constant_type {};
	template<typename T> struct is_unbounded_raw_array<T[]> : true_constant_type {};

	template<typename T> struct is_raw_array : bool_constant_type<is_bounded_raw_array<T>::value || is_unbounded_raw_array<T>::value> {};
}


//reference categories
namespace sl::traits {
	template<typename T> struct is_lvalue_reference     : false_constant_type {};
	template<typename T> struct is_lvalue_reference<T&> : true_constant_type {};

	template<typename T> struct is_rvalue_reference      : false_constant_type {};
	template<typename T> struct is_rvalue_reference<T&&> : true_constant_type {};
}

//qualifier categories 
namespace sl::traits {
	template<typename T> struct is_const_qualified          : false_constant_type {};
	template<typename T> struct is_const_qualified<const T> : true_constant_type {};

	template<typename T> struct is_volatile_qualified             : false_constant_type {};
	template<typename T> struct is_volatile_qualified<volatile T> : true_constant_type {};
}


//helper variables
namespace sl::traits {
	template<typename T>
	constexpr bool is_integer_v = is_integer<T>::value;
	template<typename T>
	constexpr bool is_character_v = is_character<T>::value;

	template<typename T>
	constexpr bool is_floating_point_v = is_floating_point<T>::value;

	template<typename T>
	constexpr bool is_enumeration_v = is_enumeration<T>::value;


	template<typename T>
	constexpr bool is_bounded_raw_array_v = is_bounded_raw_array<T>::value;

	template<typename T>
	constexpr bool is_unbounded_raw_array_v = is_unbounded_raw_array<T>::value;

	template<typename T>
	constexpr bool is_raw_array_v = is_raw_array<T>::value;


	template<typename T>
	constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

	template<typename T>
	constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;


	template<typename T>
	constexpr bool is_const_qualified_v = is_const_qualified<T>::value;

	template<typename T>
	constexpr bool is_volatile_qualified_v = is_volatile_qualified<T>::value;
}

//concepts
namespace sl::traits {
	template<typename T>
	concept integer = is_integer_v<T>;
	template<typename T>
	concept character = is_character_v<T>;

	template<typename T>
	concept floating_point = is_floating_point_v<T>;

	template<typename T>
	concept enumeration = is_enumeration_v<T>;


	template<typename T>
	concept bounded_raw_array = is_bounded_raw_array_v<T>;

	template<typename T>
	concept unbounded_raw_array = is_unbounded_raw_array_v<T>;

	template<typename T>
	concept raw_array = is_raw_array_v<T>;


	template<typename T>
	concept lvalue_reference = is_lvalue_reference_v<T>;

	template<typename T>
	concept rvalue_reference = is_rvalue_reference_v<T>;


	template<typename T>
	concept const_qualified = is_const_qualified_v<T>;
	
	template<typename T>
	concept volatile_qualified = is_volatile_qualified_v<T>;
}