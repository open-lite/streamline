#pragma once
#include "streamline/metaprogramming/type_identity.hpp"


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