#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/metaprogramming/type_traits/isolated_categories.hpp"


namespace sl::impl {
	template<typename T, typename U>
	struct is_same_as : false_constant_type {};
 
	template<typename T>
	struct is_same_as<T, T> : true_constant_type {};
}

namespace sl::impl {
	template<typename, template<size_t, typename...> typename>
	struct is_specialization_of : false_constant_type {};
	
	template<template<size_t, typename...> typename TemplateT, size_t N, typename... Args, template<size_t, typename...> typename TemplateU>
	struct is_specialization_of<TemplateT<N, Args...>, TemplateU> : is_same_as<TemplateT<N, Args...>, TemplateU<N, Args...>> {};
}