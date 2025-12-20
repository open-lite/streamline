#pragma once
#include "streamline/numeric/int.hpp"

namespace sl {
	struct in_place_tag_type { 
		constexpr explicit in_place_tag_type() = default;
	};


	template<size_t N>
	struct in_place_repeat_tag_type { 
		constexpr explicit in_place_repeat_tag_type() = default;
	};

	template<typename T>
	struct in_place_adl_tag_type { 
		constexpr explicit in_place_adl_tag_type() = default;
	};

	template<template<size_t, typename...> typename T>
	struct in_place_container_adl_tag_type { 
		constexpr explicit in_place_container_adl_tag_type() = default;
	};

	
	template<index_t I>
	struct in_place_index_type { 
		constexpr explicit in_place_index_type() = default;
	};

	template<typename T>
	struct in_place_type_type { 
		constexpr explicit in_place_type_type() = default;
	};

	template<template<size_t, typename...> typename T>
	struct in_place_container_type_type {
		constexpr explicit in_place_container_type_type() = default;
	};
}

namespace sl {
	inline constexpr in_place_tag_type in_place_tag{};


	template<size_t N>
	constexpr in_place_repeat_tag_type<N> in_place_repeat_tag{};

	template<typename T>
	constexpr in_place_adl_tag_type<T> in_place_adl_tag{};

	template<template<size_t, typename...> typename T>
	constexpr in_place_container_adl_tag_type<T> in_place_container_adl_tag{};


	template<index_t I>
	constexpr in_place_index_type<I> in_place_index{};

	template<typename T>
	constexpr in_place_type_type<T> in_place_type{};

	template<template<size_t, typename...> typename T>
	constexpr in_place_container_type_type<T> in_place_container_type{};
}