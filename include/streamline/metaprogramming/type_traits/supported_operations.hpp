#pragma once
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/universal/make.hpp"
#include "streamline/universal/make_deduced.hpp"

#include "streamline/metaprogramming/impl/relationships.hpp"


namespace sl::traits {
	template<typename T, typename... Args>
	struct is_constructible_from : bool_constant_type<__is_constructible(T, Args...)> {};

	template<typename T, typename... Args>
	struct is_trivially_constructible_from : bool_constant_type<__is_constructible(T, Args...)> {};

	template<typename T, typename... Args>
	struct is_noexcept_constructible_from : bool_constant_type<__is_constructible(T, Args...)> {};


	template<typename T, typename... Args>
	struct is_forwarded_constructible_from : bool_constant_type<__is_constructible(T, Args&&...)> {};

	template<typename T, typename... Args>
	struct is_forwarded_trivially_constructible_from : bool_constant_type<__is_constructible(T, Args&&...)> {};

	template<typename T, typename... Args>
	struct is_forwarded_noexcept_constructible_from : bool_constant_type<__is_constructible(T, Args&&...)> {};
}



//helper variables
namespace sl::traits {
	template<typename T, typename... Args>
	constexpr bool is_constructible_from_v           = is_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_trivially_constructible_from_v = is_trivially_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_noexcept_constructible_from_v  = is_noexcept_constructible_from<T, Args...>::value;

	template<typename T, typename... Args>
	constexpr bool is_forwarded_constructible_from_v           = is_forwarded_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_forwarded_trivially_constructible_from_v = is_forwarded_trivially_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_forwarded_noexcept_constructible_from_v  = is_forwarded_noexcept_constructible_from<T, Args...>::value;
}

//concepts
namespace sl::traits {
	template<typename T, typename... Args>
	concept constructible_from           = is_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept trivially_constructible_from = is_trivially_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept noexcept_constructible_from  = is_noexcept_constructible_from_v<T, Args...>;

	template<typename T, typename... Args>
	concept forwaded_constructible_from           = is_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept forwaded_trivially_constructible_from = is_trivially_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept forwaded_noexcept_constructible_from  = is_noexcept_constructible_from_v<T, Args...>;
}