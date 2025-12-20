#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/universal/make.hpp"
#include "streamline/universal/make_deduced.hpp"

#include "streamline/metaprogramming/impl/relationships.hpp"


namespace sl::traits {
	template<typename T, typename U>
	struct is_same_as : impl::is_same_as<T, U> {};

	template<template<size_t, typename...> typename ContainerT, template<size_t, typename...> typename ContainerU, size_t N, typename... Ts>
	struct is_same_container_as : is_same_as<ContainerT<N, Ts...>, ContainerU<N, Ts...>> {};


	template<typename T, typename... Us>
	struct are_all_same_as : bool_constant_type<(is_same_as<T, Us>::value && ...)> {};

	template<typename T>
	struct are_all_same_as<T> : true_constant_type {};

	template<typename T, typename... Us>
	struct are_all_not_same_as : bool_constant_type<(!is_same_as<T, Us>::value && ...)> {};

	template<typename T>
	struct are_all_not_same_as<T> : true_constant_type {};


	template<typename...>
	struct are_all_same : true_constant_type {};

	template<typename T0, typename... Tn>
	struct are_all_same<T0, Tn...> : are_all_same_as<T0, Tn...> {};


	template<typename...>
	struct are_all_unique : true_constant_type {};

	template<typename T0, typename... Tn>
	struct are_all_unique<T0, Tn...> : bool_constant_type<(!is_same_as<T0, Tn>::value && ...) && are_all_unique<Tn...>::value>{};



	template<typename From, typename To>
	struct is_convertible_to : bool_constant_type<__is_convertible(From, To)> {};

	template<typename From, typename To>
	struct is_noexcept_convertible_to : bool_constant_type<__is_nothrow_convertible(From, To)> {};


	template<typename To, typename From>
	struct is_convertible_from : bool_constant_type<__is_nothrow_convertible(From, To)> {};

	template<typename To, typename From>
	struct is_noexcept_convertible_from : bool_constant_type<__is_nothrow_convertible(From, To)> {};



	template<typename T, template<size_t, typename...> typename TemplateT>
	struct is_specialization_of : impl::is_specialization_of<remove_cvref_t<T>, TemplateT> {};



    template<typename T, typename... Args>
    struct is_makeable_from : bool_constant_type<requires (Args&&... args) {
		{ ::sl::universal::make<T>(forward<Args>(args)...) } noexcept;
	}> {};

    template<template<size_t, typename...> typename T, typename... Args>
    struct is_deduced_makeable_from : bool_constant_type<requires (Args&&... args) {
		{ ::sl::universal::make_deduced<T>(forward<Args>(args)...) } noexcept;
	}> {};
}


//helper variable templates
namespace sl::traits {
	template<typename T, typename U>
	constexpr bool is_same_as_v = is_same_as<T, U>::value;

	template<template<size_t, typename...> typename ContainerT, template<size_t, typename...> typename ContainerU, size_t N, typename... Ts>
	constexpr bool is_same_container_as_v = is_same_container_as<ContainerT, ContainerU, N, Ts...>::value;

	template<typename T, typename... Us>
	constexpr bool are_all_same_as_v = are_all_same_as<T, Us...>::value;
	template<typename T, typename... Us>
	constexpr bool are_all_not_same_as_v = are_all_not_same_as<T, Us...>::value;

	template<typename... Ts>
	constexpr bool are_all_same_v = are_all_same<Ts...>::value;

	template<typename... Ts>
	constexpr bool are_all_unique_v = are_all_unique<Ts...>::value;


	template<typename From, typename To>
	constexpr bool is_convertible_to_v = is_convertible_to<From, To>::value;
	template<typename From, typename To>
	constexpr bool is_noexcept_convertible_to_v = is_noexcept_convertible_to<From, To>::value;
	
	template<typename To, typename From>
	constexpr bool is_convertible_from_v = is_convertible_from<To, From>::value;
	template<typename To, typename From>
	constexpr bool is_noexcept_convertible_from_v = is_noexcept_convertible_from<To, From>::value;


    template<typename T, template<size_t, typename...> typename TemplateT>
	constexpr bool is_specialization_of_v = is_specialization_of<T, TemplateT>::value;


    template<typename T, typename... Args>
	constexpr bool is_makeable_from_v = is_makeable_from<T, Args...>::value;

    template<template<size_t, typename...> typename T, typename... Args>
	constexpr bool is_deduced_makeable_from_v = is_deduced_makeable_from<T, Args...>::value;
}

//concepts
namespace sl::traits {
	template<typename T, typename U>
	concept same_as = is_same_as_v<T, U>;

	template<template<size_t, typename...> typename ContainerT, template<size_t, typename...> typename ContainerU, size_t N, typename... Ts>
	concept same_container_as = is_same_container_as_v<ContainerT, ContainerU, N, Ts...>;

	template<typename T, typename... Us>
	concept all_same_as = are_all_same_as_v<T, Us...>;
	template<typename T, typename... Us>
	concept all_not_same_as = are_all_not_same_as_v<T, Us...>;

	template<typename... Ts>
	concept all_same = are_all_same_v<Ts...>;

	template<typename... Ts>
	concept all_unique = are_all_unique_v<Ts...>;


	template<typename From, typename To>
	concept convertible_to = is_convertible_to_v<From, To>;
	template<typename From, typename To>
	concept noexcept_convertible_to = is_noexcept_convertible_to_v<From, To>;
	
	template<typename To, typename From>
	concept convertible_from = is_convertible_to_v<To, From>;
	template<typename To, typename From>
	concept noexcept_convertible_from = is_noexcept_convertible_from_v<From, To>;


    template<typename T, template<size_t, typename...> typename TemplateT>
	concept specialization_of = is_specialization_of_v<T, TemplateT>;


    template<typename T, typename... Args>
	concept makeable_from = is_makeable_from_v<T, Args...>;

    template<template<size_t, typename...> typename T, typename... Args>
	concept deduced_makeable_from = is_deduced_makeable_from_v<T, Args...>;
}