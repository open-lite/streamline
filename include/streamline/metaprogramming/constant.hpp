#pragma once
#include "streamline/numeric/int.hpp"

namespace sl {
	template<typename T, T V>
	struct constant_type {
		constexpr static T value = V;
	public:
		using value_type = T;
		using type = constant_type<T, V>;
	public:
		consteval operator value_type() const noexcept { return value; }
    	consteval value_type operator()() const noexcept { return value; }
	};
}


namespace sl {
	template<index_t I>
	using index_constant_type = constant_type<index_t, I>;

	template<size_t N>
	using size_constant_type = constant_type<size_t, N>;
	
	template<bool B>
	using bool_constant_type = constant_type<bool, B>;
}

namespace sl {
	using true_constant_type = bool_constant_type<true>;
	using false_constant_type = bool_constant_type<false>;
}



namespace sl {
	template<typename T, T V>
	constexpr constant_type<T, V> constant{};
}

namespace sl {
	template<index_t I>
	constexpr index_constant_type<I> index_constant{};

	template<size_t N>
	constexpr size_constant_type<N> size_constant{};
	
	template<bool B>
	constexpr bool_constant_type<B> bool_constant{};
}

namespace sl {
	constexpr index_constant_type<0> first_constant{};
	constexpr index_constant_type<1> second_constant{};
	
	constexpr true_constant_type true_constant{};
	constexpr false_constant_type false_constant{};
}