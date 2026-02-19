#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/metaprogramming/invoke_result.hpp"
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



	template<typename FnT, typename... ArgTs> 
	struct is_invocable : bool_constant_type<requires { 
		typename invoke_result_t<FnT, ArgTs...>; 
	}>{};

	template<typename FnT, typename... ArgTs> 
	struct is_noexcept_invocable : bool_constant_type<is_invocable<FnT, ArgTs...>::value && requires { 
		requires invoke_result<FnT, ArgTs...>::__is_noexcept;
	}>{};


	template<typename R, typename FnT, typename... ArgTs> 
	struct is_invocable_r : bool_constant_type<is_invocable<FnT, ArgTs...>::value && requires { 
		requires is_convertible_to<invoke_result_t<FnT, ArgTs...>, R>::value || is_same_as<R, void>::value;
	}>{};

	template<typename R, typename FnT, typename... ArgTs>
	struct is_noexcept_invocable_r : bool_constant_type<is_noexcept_invocable<FnT, ArgTs...>::value && requires {
		requires is_noexcept_convertible_to<invoke_result_t<FnT, ArgTs...>, R>::value || is_same_as<R, void>::value;
	}>{};

	

	template<typename FnT, typename TupleLikeT> 
	struct is_invocable_each : bool_constant_type<requires { 
		typename invoke_each_result<FnT, TupleLikeT>::type; 
	}>{};

	template<typename FnT, typename TupleLikeT> 
	struct is_noexcept_invocable_each : bool_constant_type<is_invocable_each<FnT, TupleLikeT>::value && requires { 
		requires invoke_each_result<FnT, TupleLikeT>::__is_noexcept;
	}>{};


	template<typename R, typename FnT, typename TupleLikeT> 
	struct is_invocable_each_r : bool_constant_type<is_invocable_each<FnT, TupleLikeT>::value && requires { 
		requires is_convertible_to<invoke_each_result_t<FnT, TupleLikeT>, R>::value || is_same_as<R, void>::value;
	}>{};

	template<typename R, typename FnT, typename TupleLikeT> 
	struct is_noexcept_invocable_each_r : bool_constant_type<is_noexcept_invocable_each<FnT, TupleLikeT>::value && requires { 
		requires is_noexcept_convertible_to<invoke_each_result_t<FnT, TupleLikeT>, R>::value || is_same_as<R, void>::value;
	}>{};
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


	template<typename FnT, typename... ArgTs> 
	constexpr bool is_invocable_v = is_invocable<FnT, ArgTs...>::value;
	template<typename FnT, typename... ArgTs> 
	constexpr bool is_noexcept_invocable_v = is_noexcept_invocable<FnT, ArgTs...>::value;
	
	template<typename R, typename FnT, typename... ArgTs> 
	constexpr bool is_invocable_r_v = is_invocable_r<R, FnT, ArgTs...>::value;
	template<typename R, typename FnT, typename... ArgTs> 
	constexpr bool is_noexcept_invocable_r_v = is_noexcept_invocable_r<R, FnT, ArgTs...>::value;


	template<typename FnT, typename TupleLikeT> 
	constexpr bool is_invocable_each_v = is_invocable_each<FnT, TupleLikeT>::value;
	template<typename FnT, typename TupleLikeT> 
	constexpr bool is_noexcept_invocable_each_v = is_noexcept_invocable_each<FnT, TupleLikeT>::value;
	
	template<typename R, typename FnT, typename TupleLikeT> 
	constexpr bool is_invocable_each_r_v = is_invocable_each_r<R, FnT, TupleLikeT>::value;
	template<typename R, typename FnT, typename TupleLikeT> 
	constexpr bool is_noexcept_invocable_each_r_v = is_noexcept_invocable_each_r<R, FnT, TupleLikeT>::value;
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


	template<typename FnT, typename... ArgTs> 
	concept invocable = is_invocable<FnT, ArgTs...>::value;
	template<typename FnT, typename... ArgTs> 
	concept noexcept_invocable = is_noexcept_invocable<FnT, ArgTs...>::value;
	
	template<typename R, typename FnT, typename... ArgTs> 
	concept invocable_r = is_invocable_r<R, FnT, ArgTs...>::value;
	template<typename R, typename FnT, typename... ArgTs> 
	concept noexcept_invocable_r = is_noexcept_invocable_r<R, FnT, ArgTs...>::value;


	template<typename FnT, typename TupleLikeT> 
	concept invocable_each = is_invocable_each<FnT, TupleLikeT>::value;
	template<typename FnT, typename TupleLikeT> 
	concept noexcept_invocable_each = is_noexcept_invocable_each<FnT, TupleLikeT>::value;
	
	template<typename R, typename FnT, typename TupleLikeT> 
	concept invocable_each_r = is_invocable_each_r<R, FnT, TupleLikeT>::value;
	template<typename R, typename FnT, typename TupleLikeT> 
	concept noexcept_invocable_each_r = is_noexcept_invocable_each_r<R, FnT, TupleLikeT>::value;
}