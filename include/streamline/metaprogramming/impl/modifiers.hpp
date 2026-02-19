#pragma once
#include "streamline/metaprogramming/type_identity.hpp"
#include "streamline/numeric/int.hpp"


//... overload handles cv void or cv- or ref-qualified function types
namespace sl::impl {
    template<typename T> auto add_lvalue_reference(int) -> type_identity<T&>;
    template<typename T> auto add_lvalue_reference(...) -> type_identity<T>; 
 
    template<typename T>auto add_rvalue_reference(int) -> type_identity<T&&>;
    template<typename T>auto add_rvalue_reference(...) -> type_identity<T>;
}

//... overload handles cv- or ref-qualified function types
namespace sl::impl {
	template<typename T> struct remove_reference      : type_identity<T> {};
	template<typename T> struct remove_reference<T&>  : type_identity<T> {};
	template<typename T> struct remove_reference<T&&> : type_identity<T> {};

	template<typename T> auto add_pointer(int) -> type_identity<typename remove_reference<T>::type*>;
    template<typename T> auto add_pointer(...) -> type_identity<T>;
}

namespace sl::impl {
	template<bool Signed, sl::size_t N> struct integer_type_with_size;

	template<> struct integer_type_with_size<false, sizeof(sl::uint8_t) > : type_identity<sl::uint8_t > {};
	template<> struct integer_type_with_size<false, sizeof(sl::uint16_t)> : type_identity<sl::uint16_t> {};
	template<> struct integer_type_with_size<false, sizeof(sl::uint32_t)> : type_identity<sl::uint32_t> {};
	template<> struct integer_type_with_size<false, sizeof(sl::uint64_t)> : type_identity<sl::uint64_t> {};

	template<> struct integer_type_with_size<true, sizeof(sl::int8_t) > : type_identity<sl::int8_t > {};
	template<> struct integer_type_with_size<true, sizeof(sl::int16_t)> : type_identity<sl::int16_t> {};
	template<> struct integer_type_with_size<true, sizeof(sl::int32_t)> : type_identity<sl::int32_t> {};
	template<> struct integer_type_with_size<true, sizeof(sl::int64_t)> : type_identity<sl::int64_t> {};
}