#pragma once
#include "streamline/metaprogramming/in_place.hpp"
#include "streamline/metaprogramming/integral_constant.hpp"
#include "streamline/metaprogramming/forward.hpp"

#include "streamline/metaprogramming/impl/relationships.hpp"
#include "streamline/metaprogramming/type_modifiers.hpp"


namespace sl::traits {
	template<typename T, typename... Args>
	struct is_constructible_from : bool_constant_type<__is_constructible(T, Args...)> {};

	template<typename T, typename... Args>
	struct is_trivially_constructible_from : bool_constant_type<__is_trivially_constructible(T, Args...)> {};

	template<typename T, typename... Args>
	struct is_noexcept_constructible_from : bool_constant_type<__is_nothrow_constructible(T, Args...)> {};


	template<typename T>
	struct is_default_constructible : bool_constant_type<__is_constructible(T)> {};

	template<typename T>
	struct is_trivially_default_constructible : bool_constant_type<__is_trivially_constructible(T)> {};

	template<typename T>
	struct is_noexcept_default_constructible : bool_constant_type<__is_nothrow_constructible(T)> {};


	template<typename T>
	struct is_copy_constructible : bool_constant_type<__is_constructible(T, add_lvalue_reference_t<const T>)> {};

	template<typename T>
	struct is_trivially_copy_constructible : bool_constant_type<__is_trivially_constructible(T, add_lvalue_reference_t<const T>)> {};

	template<typename T>
	struct is_noexcept_copy_constructible : bool_constant_type<__is_nothrow_constructible(T, add_lvalue_reference_t<const T>)> {};

	
	template<typename T>
	struct is_move_constructible : bool_constant_type<__is_constructible(T, add_rvalue_reference_t<T>)> {};

	template<typename T>
	struct is_trivially_move_constructible : bool_constant_type<__is_trivially_constructible(T, add_rvalue_reference_t<T>)> {};

	template<typename T>
	struct is_noexcept_move_constructible : bool_constant_type<__is_nothrow_constructible(T, add_rvalue_reference_t<T>)> {};


	template<typename T, typename... Args>
	struct is_forwarded_constructible_from : bool_constant_type<__is_constructible(T, Args&&...)> {};

	template<typename T, typename... Args>
	struct is_forwarded_trivially_constructible_from : bool_constant_type<__is_trivially_constructible(T, Args&&...)> {};

	template<typename T, typename... Args>
	struct is_forwarded_noexcept_constructible_from : bool_constant_type<__is_nothrow_constructible(T, Args&&...)> {};
}

namespace sl::traits {
	template<typename T, typename Arg>
	struct is_assignable_from : bool_constant_type<__is_assignable(add_lvalue_reference_t<T>, Arg)> {};

	template<typename T, typename Arg>
	struct is_trivially_assignable_from : bool_constant_type<__is_trivially_assignable(add_lvalue_reference_t<T>, Arg)> {};

	template<typename T, typename Arg>
	struct is_noexcept_assignable_from : bool_constant_type<__is_nothrow_assignable(add_lvalue_reference_t<T>, Arg)> {};


	template<typename T>
	struct is_copy_assignable : bool_constant_type<__is_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>)> {};

	template<typename T>
	struct is_trivially_copy_assignable : bool_constant_type<__is_trivially_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>)> {};

	template<typename T>
	struct is_noexcept_copy_assignable : bool_constant_type<__is_nothrow_assignable(add_lvalue_reference_t<T>, add_lvalue_reference_t<const T>)> {};


	template<typename T>
	struct is_move_assignable : bool_constant_type<__is_assignable(add_lvalue_reference_t<T>, add_rvalue_reference_t<T>)> {};

	template<typename T>
	struct is_trivially_move_assignable : bool_constant_type<__is_trivially_assignable(add_lvalue_reference_t<T>, add_rvalue_reference_t<T>)> {};

	template<typename T>
	struct is_noexcept_move_assignable : bool_constant_type<__is_nothrow_assignable(add_lvalue_reference_t<T>, add_rvalue_reference_t<T>)> {};


	template<typename T, typename Arg>
	struct is_forwarded_assignable_from : bool_constant_type<__is_assignable(add_lvalue_reference_t<T>, Arg&&)> {};

	template<typename T, typename Arg>
	struct is_forwarded_trivially_assignable_from : bool_constant_type<__is_trivially_assignable(add_lvalue_reference_t<T>, Arg&&)> {};

	template<typename T, typename Arg>
	struct is_forwarded_noexcept_assignable_from : bool_constant_type<__is_nothrow_assignable(add_lvalue_reference_t<T>, Arg&&)> {};
}

namespace sl::traits {
	template<typename T>
	struct is_fully_movable : bool_constant_type<is_move_constructible<T>::value && is_move_assignable<T>::value> {};

	template<typename T>
	struct is_trivially_fully_movable : bool_constant_type<is_trivially_move_constructible<T>::value && is_trivially_move_assignable<T>::value> {};

	template<typename T>
	struct is_noexcept_fully_movable : bool_constant_type<is_noexcept_move_constructible<T>::value && is_noexcept_move_assignable<T>::value> {};
}

namespace sl::traits {
	template<typename T>
	struct is_destructible : bool_constant_type<__is_destructible(T)> {};

	template<typename T>
	struct is_trivially_destructible : bool_constant_type<__is_trivially_destructible(T)> {};

	template<typename T>
	struct is_noexcept_destructible : bool_constant_type<__is_nothrow_destructible(T)> {};
}


namespace sl::traits {
	template<typename T, auto I>
	struct is_gettable : bool_constant_type<requires (T&& t) { {get<I>(sl::forward<T>(t))}; }> {};
	template<typename T, auto I>
	struct is_noexcept_gettable : bool_constant_type<requires (T&& t) { {get<I>(sl::forward<T>(t))} noexcept; }> {};

	template<typename T, auto I>
	struct is_gettable_using_member : bool_constant_type<requires (T&& t) { {sl::forward<T>(t).template get<I>()}; }> {};
	template<typename T, auto I>
	struct is_noexcept_gettable_using_member : bool_constant_type<requires (T&& t) { {sl::forward<T>(t).template get<I>()} noexcept; }> {};
   

    template<template<size_t, typename...> typename T, typename... Args>
    struct is_deduced_makeable_from : bool_constant_type<requires (Args&&... args) {
		{ make_deduced<T>(sl::forward<Args>(args)...) };
	}> {};
    template<template<size_t, typename...> typename T, typename... Args>
    struct is_noexcept_deduced_makeable_from : bool_constant_type<requires (Args&&... args) {
		{ make_deduced<T>(sl::forward<Args>(args)...) } noexcept;
	}> {};

	template<template<size_t, typename...> typename T, typename... Args>
    struct is_adl_deduced_makeable_from : bool_constant_type<requires (Args&&... args) {
		{ make_deduced<T>(sl::forward<Args>(args)..., in_place_container_adl_tag<T>) };
	}> {};
    template<template<size_t, typename...> typename T, typename... Args>
    struct is_noexcept_adl_deduced_makeable_from : bool_constant_type<requires (Args&&... args) {
		{ make_deduced<T>(sl::forward<Args>(args)..., in_place_container_adl_tag<T>) } noexcept;
	}> {};


	template<typename T, typename... Args>
    struct is_makeable_from : bool_constant_type<requires (Args&&... args) {
		{make<T>(sl::forward<Args>(args)...) };
	}> {};
	template<typename T, typename... Args>
    struct is_noexcept_makeable_from : bool_constant_type<requires (Args&&... args) {
		{make<T>(sl::forward<Args>(args)...) } noexcept;
	}> {};

	template<typename T, typename... Args>
    struct is_adl_makeable_from : bool_constant_type<requires (Args&&... args) {
		{make<T>(sl::forward<Args>(args)..., in_place_adl_tag<T>) };
	}> {};
	template<typename T, typename... Args>
    struct is_noexcept_adl_makeable_from : bool_constant_type<requires (Args&&... args) {
		{make<T>(sl::forward<Args>(args)..., in_place_adl_tag<T>) } noexcept;
	}> {};


	template<typename T, typename U>
    struct is_swappable_with : bool_constant_type<requires (T&& t, U&& u) {
		{swap(sl::forward<T>(t), sl::forward<U>(u)) };
	}> {};
	template<typename T, typename U>
    struct is_noexcept_swappable_with : bool_constant_type<requires (T&& t, U&& u) {
		{swap(sl::forward<T>(t), sl::forward<U>(u)) } noexcept;
	}> {};

	template<typename T>
    struct is_swappable : bool_constant_type<is_swappable_with<sl::add_lvalue_reference_t<T>, sl::add_lvalue_reference_t<T>>::value> {};
	template<typename T>
    struct is_noexcept_swappable : bool_constant_type<is_noexcept_swappable_with<sl::add_lvalue_reference_t<T>, sl::add_lvalue_reference_t<T>>::value> {};

	template<typename T, typename U>
	struct is_swapable_using_member : bool_constant_type<requires (T&& t, U&& u) { {sl::forward<T>(t).swap(sl::forward<U>(u))}; }> {};
	template<typename T, typename U>
	struct is_noexcept_swapable_using_member : bool_constant_type<requires (T&& t, U&& u) { {sl::forward<T>(t).swap(sl::forward<U>(u))} noexcept; }> {};
}



//helper variables
namespace sl::traits {
	template<typename T, typename... Args>
	constexpr bool is_constructible_from_v           = is_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_trivially_constructible_from_v = is_trivially_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_noexcept_constructible_from_v  = is_noexcept_constructible_from<T, Args...>::value;

	template<typename T>
	constexpr bool is_default_constructible_v           = is_default_constructible<T>::value;
	template<typename T>
	constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;
	template<typename T>
	constexpr bool is_noexcept_default_constructible_v  = is_noexcept_default_constructible<T>::value;

	template<typename T>
	constexpr bool is_copy_constructible_v           = is_copy_constructible<T>::value;
	template<typename T>
	constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;
	template<typename T>
	constexpr bool is_noexcept_copy_constructible_v  = is_noexcept_copy_constructible<T>::value;

	template<typename T>
	constexpr bool is_move_constructible_v           = is_move_constructible<T>::value;
	template<typename T>
	constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;
	template<typename T>
	constexpr bool is_noexcept_move_constructible_v  = is_noexcept_move_constructible<T>::value;

	template<typename T, typename... Args>
	constexpr bool is_forwarded_constructible_from_v           = is_forwarded_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_forwarded_trivially_constructible_from_v = is_forwarded_trivially_constructible_from<T, Args...>::value;
	template<typename T, typename... Args>
	constexpr bool is_forwarded_noexcept_constructible_from_v  = is_forwarded_noexcept_constructible_from<T, Args...>::value;
}

namespace sl::traits {
	template<typename T, typename Arg>
	constexpr bool is_assignable_from_v           = is_assignable_from<T, Arg>::value;
	template<typename T, typename Arg>
	constexpr bool is_trivially_assignable_from_v = is_trivially_assignable_from<T, Arg>::value;
	template<typename T, typename Arg>
	constexpr bool is_noexcept_assignable_from_v  = is_noexcept_assignable_from<T, Arg>::value;

	template<typename T>
	constexpr bool is_copy_assignable_v           = is_copy_assignable<T>::value;
	template<typename T>
	constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;
	template<typename T>
	constexpr bool is_noexcept_copy_assignable_v  = is_noexcept_copy_assignable<T>::value;

	template<typename T>
	constexpr bool is_move_assignable_v           = is_move_assignable<T>::value;
	template<typename T>
	constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;
	template<typename T>
	constexpr bool is_noexcept_move_assignable_v  = is_noexcept_move_assignable<T>::value;

	template<typename T, typename Arg>
	constexpr bool is_forwarded_assignable_from_v           = is_forwarded_assignable_from<T, Arg>::value;
	template<typename T, typename Arg>
	constexpr bool is_forwarded_trivially_assignable_from_v = is_forwarded_trivially_assignable_from<T, Arg>::value;
	template<typename T, typename Arg>
	constexpr bool is_forwarded_noexcept_assignable_from_v  = is_forwarded_noexcept_assignable_from<T, Arg>::value;
}

namespace sl::traits {
	template<typename T>
	constexpr bool is_fully_movable_v           = is_fully_movable<T>::value;
	template<typename T>
	constexpr bool is_trivially_fully_movable_v = is_trivially_fully_movable<T>::value;
	template<typename T>
	constexpr bool is_noexcept_fully_movable_v  = is_noexcept_fully_movable<T>::value;
}


namespace sl::traits {
	template<typename T>
	constexpr bool is_destructible_v           = is_destructible<T>::value;
	template<typename T>
	constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;
	template<typename T>
	constexpr bool is_noexcept_destructible_v  = is_noexcept_destructible<T>::value;
}


namespace sl::traits {
	template<typename T, auto I>
	constexpr bool is_gettable_v = is_gettable<T, I>::value;
	template<typename T, auto I>
	constexpr bool is_noexcept_gettable_v = is_noexcept_gettable<T, I>::value;
	template<typename T, auto I>
	constexpr bool is_gettable_using_member_v = is_gettable_using_member<T, I>::value;
	template<typename T, auto I>
	constexpr bool is_noexcept_gettable_using_member_v = is_noexcept_gettable_using_member<T, I>::value;

	
    template<template<size_t, typename...> typename T, typename... Args>
    constexpr bool is_deduced_makeable_from_v = is_deduced_makeable_from<T, Args...>::value;
    template<template<size_t, typename...> typename T, typename... Args>
    constexpr bool is_noexcept_deduced_makeable_from_v = is_noexcept_deduced_makeable_from<T, Args...>::value;
    template<template<size_t, typename...> typename T, typename... Args>
    constexpr bool is_adl_deduced_makeable_from_v = is_adl_deduced_makeable_from<T, Args...>::value;
    template<template<size_t, typename...> typename T, typename... Args>
    constexpr bool is_noexcept_adl_deduced_makeable_from_v = is_noexcept_adl_deduced_makeable_from<T, Args...>::value;

	template<typename T, typename... Args>
    constexpr bool is_makeable_from_v = is_makeable_from<T, Args...>::value;
	template<typename T, typename... Args>
    constexpr bool is_noexcept_makeable_from_v = is_noexcept_makeable_from<T, Args...>::value;
	template<typename T, typename... Args>
    constexpr bool is_adl_makeable_from_v = is_makeable_from<T, Args...>::value;
	template<typename T, typename... Args>
    constexpr bool is_noexcept_adl_makeable_from_v = is_noexcept_makeable_from<T, Args...>::value;

	template<typename T, typename U>
    constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;
	template<typename T, typename U>
    constexpr bool is_noexcept_swappable_with_v = is_noexcept_swappable_with<T, U>::value;
	template<typename T>
    constexpr bool is_swappable_v = is_swappable<T>::value;
	template<typename T>
    constexpr bool is_noexcept_swappable_v = is_noexcept_swappable<T>::value;
	template<typename T, typename U>
	constexpr bool is_swapable_using_member_v = is_swapable_using_member<T, U>::value;
	template<typename T, typename U>
	constexpr bool is_noexcept_swapable_using_member_v = is_noexcept_swapable_using_member<T, U>::value;
}


//concepts
namespace sl::traits {
	template<typename T, typename... Args>
	concept constructible_from           = is_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept trivially_constructible_from = is_trivially_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept noexcept_constructible_from  = is_noexcept_constructible_from_v<T, Args...>;

	template<typename T>
	concept default_constructible           = is_default_constructible_v<T>;
	template<typename T>
	concept trivially_default_constructible = is_trivially_default_constructible_v<T>;
	template<typename T>
	concept noexcept_default_constructible  = is_noexcept_default_constructible_v<T>;

	template<typename T>
	concept copy_constructible           = is_copy_constructible_v<T>;
	template<typename T>
	concept trivially_copy_constructible = is_trivially_copy_constructible_v<T>;
	template<typename T>
	concept noexcept_copy_constructible  = is_noexcept_copy_constructible_v<T>;

	template<typename T>
	concept move_constructible           = is_move_constructible_v<T>;
	template<typename T>
	concept trivially_move_constructible = is_trivially_move_constructible_v<T>;
	template<typename T>
	concept noexcept_move_constructible  = is_noexcept_move_constructible_v<T>;

	template<typename T, typename... Args>
	concept forwaded_constructible_from           = is_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept forwaded_trivially_constructible_from = is_trivially_constructible_from_v<T, Args...>;
	template<typename T, typename... Args>
	concept forwaded_noexcept_constructible_from  = is_noexcept_constructible_from_v<T, Args...>;
}

namespace sl::traits {
	template<typename T, typename Arg>
	concept assignable_from           = is_assignable_from_v<T, Arg>;
	template<typename T, typename Arg>
	concept trivially_assignable_from = is_trivially_assignable_from_v<T, Arg>;
	template<typename T, typename Arg>
	concept noexcept_assignable_from  = is_noexcept_assignable_from_v<T, Arg>;

	template<typename T>
	concept copy_assignable           = is_copy_assignable_v<T>;
	template<typename T>
	concept trivially_copy_assignable = is_trivially_copy_assignable_v<T>;
	template<typename T>
	concept noexcept_copy_assignable  = is_noexcept_copy_assignable_v<T>;

	template<typename T>
	concept move_assignable           = is_move_assignable_v<T>;
	template<typename T>
	concept trivially_move_assignable = is_trivially_move_assignable_v<T>;
	template<typename T>
	concept noexcept_move_assignable  = is_noexcept_move_assignable_v<T>;

	template<typename T, typename Arg>
	concept forwaded_assignable_from           = is_assignable_from_v<T, Arg>;
	template<typename T, typename Arg>
	concept forwaded_trivially_assignable_from = is_trivially_assignable_from_v<T, Arg>;
	template<typename T, typename Arg>
	concept forwaded_noexcept_assignable_from  = is_noexcept_assignable_from_v<T, Arg>;
}

namespace sl::traits {
	template<typename T>
	concept fully_movable           = is_fully_movable_v<T>;
	template<typename T>
	concept trivially_fully_movable = is_trivially_fully_movable_v<T>;
	template<typename T>
	concept noexcept_fully_movable  = is_noexcept_fully_movable_v<T>;
}

namespace sl::traits {
	template<typename T>
	concept destructible           = is_destructible_v<T>;
	template<typename T>
	concept trivially_destructible = is_trivially_destructible_v<T>;
	template<typename T>
	concept noexcept_destructible  = is_noexcept_destructible_v<T>;
}


namespace sl::traits {
	template<typename T, auto I>
	concept gettable = is_gettable<T, I>::value;
	template<typename T, auto I>
	concept noexcept_gettable = is_noexcept_gettable_v<T, I>;
	template<typename T, auto I>
	concept gettable_using_member = is_gettable_using_member<T, I>::value;
	template<typename T, auto I>
	concept noexcept_gettable_using_member = is_noexcept_gettable_using_member<T, I>::value;

    template<template<size_t, typename...> typename T, typename... Args>
    concept deduced_makeable_from = is_deduced_makeable_from_v<T, Args...>;
    template<template<size_t, typename...> typename T, typename... Args>
    concept noexcept_deduced_makeable_from = is_noexcept_deduced_makeable_from_v<T, Args...>;
    template<template<size_t, typename...> typename T, typename... Args>
    concept adl_deduced_makeable_from = is_adl_deduced_makeable_from_v<T, Args...>;
    template<template<size_t, typename...> typename T, typename... Args>
    concept noexcept_adl_deduced_makeable_from = is_noexcept_adl_deduced_makeable_from_v<T, Args...>;

	template<typename T, typename... Args>
    concept makeable_from = is_makeable_from_v<T, Args...>;
	template<typename T, typename... Args>
    concept noexcept_makeable_from = is_noexcept_makeable_from_v<T, Args...>;
	template<typename T, typename... Args>
    concept adl_makeable_from = is_adl_makeable_from_v<T, Args...>;
	template<typename T, typename... Args>
    concept noexcept_adl_makeable_from = is_noexcept_adl_makeable_from_v<T, Args...>;

	template<typename T, typename U>
    concept swappable_with = is_swappable_with_v<T, U>;
	template<typename T, typename U>
    concept noexcept_swappable_with = is_noexcept_swappable_with_v<T, U>;
	template<typename T>
    concept swappable = is_swappable_v<T>;
	template<typename T>
    concept noexcept_swappable = is_noexcept_swappable_v<T>;
	template<typename T, typename U>
	concept swapable_using_member = is_swapable_using_member<T, U>::value;
	template<typename T, typename U>
	concept noexcept_swapable_using_member = is_noexcept_swapable_using_member<T, U>::value;
}
