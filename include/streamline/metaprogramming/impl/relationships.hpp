#pragma once
#include "streamline/metaprogramming/declval.hpp"
#include "streamline/metaprogramming/integer_sequence.hpp"
#include "streamline/metaprogramming/constant.hpp"
#include "streamline/containers/generic_container_template_args.def.hpp"


namespace sl::impl {
	template<typename T, typename U>
	struct is_same_as : false_constant_type {};
 
	template<typename T>
	struct is_same_as<T, T> : true_constant_type {};
}

namespace sl::impl {
	template<typename, template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()> typename>
	struct is_specialization_of : false_constant_type {};
	
	template<template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()> typename TemplateT, typename... Args, template<SL_GENERIC_CONTAINER_TEMPLATE_ARGS()> typename TemplateU>
	struct is_specialization_of<TemplateT<Args...>, TemplateU> : is_same_as<TemplateT<Args...>, TemplateU<Args...>> {};
}